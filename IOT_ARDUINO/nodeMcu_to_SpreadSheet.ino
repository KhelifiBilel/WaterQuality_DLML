#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <Wire.h> 


String readString;

//POUR SE CONNECTER AU RÉSEAU
const char* ssid = "IEEE";
const char* password = "insat2021";

const char* host = "script.google.com";
const int httpsPort = 443;
String text= "";String volt1= "";

String quality="";
WiFiClientSecure client;

double volt; float voltt;
float ntu;
 int sensorPin = A0;

String GAS_ID = "AKfycbxQGS4CKsWxPr1qFI246eRjz_S29ccaauSvOBnoOdLssnmkSqjEOy_M4Ol4TC-dQchW"; 
 
//https://script.google.com/macros/s/AKfycbxQGS4CKsWxPr1qFI246eRjz_S29ccaauSvOBnoOdLssnmkSqjEOy_M4Ol4TC-dQchW/exec?turbidity=10&volt=2&label=ok
void setup()
{             pinMode (sensorPin, INPUT); 
              Serial.begin(9600);
           
              WiFi.mode(WIFI_STA);
              WiFi.begin(ssid, password);
             
                              while (WiFi.status() != WL_CONNECTED) {
                                delay(500);
                                Serial.print(".");
                              }
          
}

void loop()
{
  int button=  digitalRead(D3);
  while(button==1){button = digitalRead(D3);delay(50);} // continuer après cliquer sur le bouton poussoir

    volt = 0;
    for(int i=0; i<100; i++)
    { volt += ((double)analogRead(sensorPin)/1023)*4.2; }       // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V)

    Serial.print(volt);

  //volt= map(volt, 0, 500,  0, 420);

   volt=(double)volt/100;
 // Serial.print(volt);
    volt = round_to_dp(volt,3);
  
    if(volt < 2.5){
      ntu = 3000;
    }else{
       ntu = -1120.4*volt*volt+5742.3*volt-4352.9;      //convertir la valeur du voltage à ntu
    }
  
    text = (String)ntu;
    volt1=(String)volt;

    if (ntu<150) { quality="very_Low_Turbidity";}
  
      else if (ntu<400) {  quality="Low_Turbidity";}
      else if (ntu<700) {  quality="Medium_Turbidity";}
      else {  quality="High_Turbidity";}

    
      sendData((int)ntu,quality,volt1);     //ENVOYER LES DONNÉES A GOOGLE SPREADSHEET
      
      Serial.print("    "+volt1+":"+ntu+":"+quality+"     ");

      delay(3000);
      
  }



     
 float round_to_dp( float in_value, int decimal_place )
{
  float multiplier = powf( 10.0f, decimal_place );
  in_value = roundf( in_value * multiplier ) / multiplier;
  return in_value;
}




//send to google spread sheet 

void sendData(int x, String y,String v)  
{
  client.setInsecure();
 // Serial.print("connecting to ");
//  Serial.println(host);
  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;}
  
  String string_x     =  String(x, DEC);
//  String string_v     =  String(v, DEC);
  String url = "/macros/s/" + GAS_ID + "/exec?turbidity=" + string_x + "&volt=" + v+"&label=" + y;
  Serial.print("requesting URL: ");
 b Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
         "Host: " + host + "\r\n" +
         "User-Agent: BuildFailureDetectorESP8266\r\n" +
         "Connection: close\r\n\r\n");

  Serial.println("request sent");
  while (client.connected()) {
  String line = client.readStringUntil('\n');
  if (line == "\r") {
    Serial.println("headers received");
    break;
  }
  }
  String line = client.readStringUntil('\n');
  if (line.startsWith("{\"state\":\"success\"")) {
  Serial.println("esp8266/Arduino CI successfull!");
  } else {
  Serial.println("esp8266/Arduino CI has failed");
  }
  Serial.println("reply was:");
  Serial.println("==========");
  Serial.println(line);
  Serial.println("==========");
  Serial.println("closing connection");
}

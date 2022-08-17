# WaterQuality_DLML
Partie DeepLearning:

Les dossiers:
original_denoised: contient le nouveau dataset après rehaussement, 			train: 70%
	validation, test:15%
results: pour chaque architecture DL, on sauvegarde quelques exécutions dans les dossiers correspondants selon le modèle DL
Note: Pour chaque exécution, il existe 3 images qui ont le même numéro (dans le nom), 2 courbes pour l’accuracy et le loss et une 3ème image pour l’architecture du modèle, exemple: 2.png et 2_.png et 22.png sont pour la même exécution.
RESULTS_DENOISED_DATASET: l’équivalent du dossier résultats, mais pour le dataset augmenté.

Les notebooks google colab:

Data_preprocess: Fait quelques modifications sur le dataset original et corrections des noms: pour organisation.
Split_Dataset: contient une fonction pour partitionner les fichiers en 3 directories: train, validation et test selon des coefficients à entrer dans les paramètres.
EAD_Training: permet de visualiser quelques échantillons, ImageDataGenerator et propose des modèles CNN pour comparer les résultats.
Les meilleurs résultats sont pour Resnet18. 
DL_Models_augmentedD: commence par faire un rehaussement et augmentation du dataset, et propose 5 modèles CNN: 3 Resnet+ Aquasight_modifié+ ex nihilo qui a donné la meilleure performance.

Partie IOT et Mobile:

Dossier IOT_ARDUINO: contient un seul fichier : nodeMcu _to_ SpreadSheet.ino pour
calculer la valeur de la turbidité et envoyer les données à une feuille de calcul Google SpreadSheet.

Lien pour 2 videos pour la partie iot et mobile réalisés fin Mars 2022: lien_drive

Lien googleSpreadSheet: lien
Lien github du code de la partie mobile (flutter): lien
Pour installer l’application mobile à partir du code, on installe tout d’abord les packages nécessaires avec la commande:  flutter pub get
et on compile avec la commande flutter run
Note: L’application mobile est connectée à google firestore.
	Pour suivre le chargement des données au cloud, on se connecte à ce compte Google:   mail: pfa.turbidity@gmail.com
		     mot de passe: pfaturbidity01

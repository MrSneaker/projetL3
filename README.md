# **Gestion intelligente de parkings dans un centre urbain**

Projet LIFPROJET - Gestion intelligente de parkings dans un centre urbain (SA4)

# Installation
Les installation nécessaire pour lancer l'application (sous linux uniquement):
    - sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev
    - sudo apt-get install libgnuplot-iostream-dev

# Lancement des exécutables et utilisation

## Application
Pour lancer l'application, vous devez la compiler en utilisant la commande make dans le répertoire contenant le Makefile. Vous obtiendrez deux exécutables, bin/test et bin/app.

Pour lancer l'application, tapper bin/app dans la console. Ensuite, vous accéder à un menu avec 3 choix possibles : Start, Exit, et un bouton pour les paramètres de la simulation en  bas à droite. Pour lancer la simulation avec les paramètres par défaut, appuyer directement sur Start. 

Si vous voulez tester une condiguration spécifique, paramètrez d'abord l'application en validant vos réglages avec OK, puis lancez là avec start.

Une fois dans l'application, vous pouvez utilisez les fonctionnalités suivantes :
### Quand la simulation n'est pas en pause
- Vous pouvez mettre la simulation en pause avec le bouton pause (situé dans la barre de menu en bas de l'écran, le bouton le plus à gauche).
- Vous pouvez accélérer la simulation avec le bouton situé à coté du bouton pause. Notez que l'accélération n'est pas réinitialisée si vous stoper/relancer la simulation avec le bouton pause.

### Quand la simulation est mise en pause
- Vous pouvez relancer la simulation en appuyant à nouveau sur le bouton pause.
- Vous pouvez cliquer sur n'importe quel voiture pour afficher les informations de l'utilisateur de celle-ci, dont les suivantes :
    - id utilisateur.
    - Noms, prénoms, âges (chaque utilisateur est un mix d'informations tirées au hasard dans des banques de données de noms et prénoms).
    - Temps de stationnement (en secondes).
    - Prix maximum que l'utilisateur est prêt à payer (en euros).
- Vous pouvez voir la fiche d'informations de chaque parkings, en cliquant sur la petite fiche en bas à droite de chacun des parkings. Les informations affichées sont l'id du parking, le prix minimum accepté et le prix de départ pour ses négociations.
- Vous pouvez afficher le menu des graphiques en appuyant sur la flèche situé en haut de l'écran au centre.
## Les graphiques
Vous avez la possibilité d'afficher 4 graphiques différents, en déroulant le menu des graphiques :
- L'évolution du profit de chaque parking au cour du temps.
- L'évolution des prix de départs de chaque parking au cour du temps.
- L'évolution du nombre de place occupé de chaque parking au cour du temps
- Le succès moyen au cour du temps (moyenne du succès de chaque parking).

Pour afficher le graphique voulu, vous n'avez qu'à cliquer sur le nom de celui-ci dans le menu déroulant.





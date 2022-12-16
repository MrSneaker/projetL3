# **Gestion intelligente de parkings dans un centre urbain**

Projet LIFPROJET - Gestion intelligente de parkings dans un centre urbain (SA4).

Réalisé par FERRER Raphael (p1908300), BOULET Benjamin (p2006010), MUNOZ Matéo (p2002495).

# Installation
Les installation nécessaire pour lancer l'application (sous linux uniquement):
>sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev

>sudo apt-get install libgnuplot-iostream-dev

# Objectif

L'objectif de cette application est de simuler la gestion d'un ou plusieurs parkings en utilisant des intelligences artificielles (IA) pour négocier le prix des places de parking avec les véhicules (elles aussi dotées d'IA). Le but est que les véhicules puissent choisir la meilleure offre et que les parkings s'adaptent pour atteindre un rendement optimal. En plus, l'application permet de paramétrer chaque simulation de manière détaillée et de visualiser clairement les données récoltées.
# Lancement des exécutables et utilisation

## Application
Pour lancer l'application, vous devez la compiler en utilisant la commande make dans le répertoire contenant le Makefile.
>make

Vous obtiendrez deux exécutables, bin/test et bin/app.

L'executable bin/test execute tous les tests de régressions. Pour le lancer, tappez bin/test dans la console (dans le répertoire de l'application)
>bin/test

Pour lancer l'application, tappez bin/app dans la console (toujours dans le répertoire de l'application).
>bin/app

Ensuite, vous accéder à un menu avec 3 choix possibles : Start, Exit, et un bouton pour les paramètres de la simulation. Pour lancer la simulation avec les paramètres par défaut, appuyer directement sur Start. 

Si vous voulez tester une condiguration spécifique, paramètrez d'abord l'application en validant vos réglages avec OK, puis lancez là avec start. Pour plus de détails sur les paramètres modifiables, allez à la section "Paramètres modifiables de la simulation" de ce readMe.

Une fois dans l'application, vous pouvez utilisez les fonctionnalités suivantes :
### Quand la simulation n'est pas en pause
- Vous pouvez mettre la simulation en pause avec le bouton pause (situé dans la barre de menu en bas de l'écran, le bouton le plus à gauche).
- Vous pouvez accélérer la simulation (le temps passe 5 fois plus vite) avec le bouton situé à coté du bouton pause. Notez que l'accélération n'est pas réinitialisée si vous stoper/relancer la simulation avec le bouton pause.

### Quand la simulation est mise en pause
- Vous pouvez relancer la simulation en appuyant à nouveau sur le bouton pause.
- Vous pouvez cliquer sur n'importe quel voiture pour afficher les informations de l'utilisateur de celle-ci, dont les suivantes :
    - id utilisateur.
    - Noms, prénoms, âges (chaque utilisateur est un mix d'informations tirées au hasard dans des banques de données de noms et prénoms).
    - Temps de stationnement (en minutes).
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
Sur l'interface du graphique, vous avez la possibilité de l'exporter dans différent format (en utilisant le bouton le plus à gauche de la barre d'outils).

***ATTENTION***, il est normal de recevoir l'avertissement suivant à l'ouverture d'un graphique : 
>qt.qpa.plugin: Could not find the Qt platform plugin "wayland" in ""

La librairie utilisée pour générer les graphiques (gnuplot-iostream) cherche à utiliser un plugin qui n'est pas présent dans cette application (et pas nécessaire).

## Paramètres modifiable de la simulation
Vous pouvez modifier plusieurs paramètres avant de lancer la simulation depuis le menu, dont les suivants (dans l'ordre) :
- Les prix de départs des différents parkings (en euros).

    *Notez que le prix minimum n'est pas réglable car il est calculé en fonction du prix de départ.*
- Le temps d'apparition d'une voiture (en secondes).
- Le prix maximum attribuable à un utilisateur (en euros).
- Le prix minimum attribuable à un utilisateur (en euros).
- Un bouton "clear", qui permet de supprimer le fichier "User.txt" qui contient toutes les données des utilisateurs. 

    **Conseil :** si vous voulez modifier les prix utilisateurs, il vaut mieux utiliser le bouton clear. En effet, cela permettra de regénérer les utilisateurs avec les nouvelles données choisies.

## Données récoltées
L'application récolte plusieurs données pour analyser la simulation, dont : 
- Les données utilisées pour constituer les graphiques (prix de départs des parkings, nombre de places occupées, profit et succès moyen). Elles sont stockées sous forme de fichier texte dans le répertoire "data" de l'application.
- Chaque parking stocke aussi les données dont il a besoin sur les utilisateurs de la simulation. Ces données sont stockées sous forme de fichier texte dans le répertoire data de l'application.
- Enfin, vous pouvez visualiser l'historique des conversations réalisées dans la simulations en cours ou de celle que vous venez de quitter. Toutes les données sont stockées sous forme de fichier texte, et sont nommées de la façon suivante:
    >Conversation U5P0_104.txt

    Ici, ce fichier désigne la Conversation entre l'utilisateur à l'ID 5 (U5) et le parking à l'ID 0 (P0) et fait partie de la 104ème conversation (104).

# Documentation du code
Pour accéder à la documentation du code, vous devez tapper dans la console (dans le répertoire du projet) la commande suivante (remplacer unNavigateur par le nom du navigateur que vous utilisez) :
>unNavigateur doc/html/index.html

Par exemple, avec firefox la commande est la suivante:
>firefox doc/html/index.html

Vous avez accès à un diagramme de classe du projet dans le répertoire "doc".

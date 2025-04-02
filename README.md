# Projet de Fin d'Année en Langage C

Ce projet implémente un jeu de **Tic-Tac-Toe (morpion)** en utilisant la bibliothèque **ncurses** pour l'interface graphique, ainsi que d'autres bibliothèques standards en C.

##  Bibliothèques utilisées

- **ncurses** : Pour la gestion de l'interface graphique en mode texte.
- **stdlib.h** : Pour les fonctions générales (comme `exit()`).
- **time.h** : Pour la gestion du temps (délais et initialisation de la graine aléatoire).
- **unistd.h** : Pour la fonction `usleep()` permettant d'ajouter des pauses dans le jeu.

##  Commandes du jeu

- **Déplacement** : Utilisez les flèches **haut** et **bas** pour naviguer dans le menu ou déplacer le curseur sur le plateau.
- **Sélection** : Appuyez sur la touche **Entrée** pour sélectionner un mode de jeu dans le menu.
- **Poser un X** : Appuyez sur la touche **Espace** pour placer un **X** sur le plateau.
- **Fin de la partie** : Une fois la partie terminée, vous pouvez appuyer sur **Espace** ou **Entrée** pour revenir au menu principal.
- **Mode Replay** : Sélectionnez l'option **"Replay"** pour rejouer la dernière partie effectuée.

##  Fonctionnalité 

- **Joueur vs Joueur** : Deux joueurs humains jouent à tour de rôle.
- **Joueur vs IA** : Un joueur humain contre une IA.
- **IA vs IA** : Deux IA s'affrontent entre elles.
- **Replay** : Revivez la dernière partie jouée.
- **Quitter** : Quitte le jeu.

## Igel Ärgern
## Description
### board.c et board.h
Ces fichiers gèrent la structure du plateau elle-même, ainsi que les fonctions la manipulant, permettant dans les autres fichiers de coder en ignorant le plus possible les spécificités de la structure.

### input.c et input.h
Ces fichiers servent à demander des entrées à l'utilisateur de manière sécurisée, pour éviter que le code plante sur une mauvaise entrée.

### main.c
Ce fichier contient la boucle de jeu, et constitue donc la colle qui réunit le reste.


## Extensions
### Le hérisson dopé
Pour l'activer, mettre un d dans le second argument.
Cette extension permet de ne pas compter le premier héisson à atteindre son objectif, car il était évidemment dopé. Le joueur à qui il appartenait est donc obligé d'utiliser l'entièreté de ses hérissons restants pour pouvoir gagner. Ceci permet d'ajouter un peu de complexité à la stratégie.

### Les sandwichs
Pour l'activer, mettre un s dans le seconde argument.
Cette extension permet de donner plus de puissance à un joueur qui possède plusieurs hérissons sur une case (dont celui du haut). Il peut en effet, dans ce cas, déplacer toute la section entre le hérisson du haut et le prochain hérisson lui appartenant (inclus) en partant du haut si il le choisit. Il ne peut donc pas déplacer plus de 2 hérissons lui appartenant à la fois.

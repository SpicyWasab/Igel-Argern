#Membres:
Nicolas-Zuang Lalung (TEMPS PASSE), Laure-Élise Tousch (temps passé : ~12h)
http://www.gamecabinet.com/rules/IgelArgernVariants.html
##Introduction

Nous avons implémenté le jeu Igel Ärgern, un jeu de stratégie à plusieurs joueurs, et deux extensions. Nous avons ainsi découpé le projet en 3 fichiers c, gérant chacun un aspect différent du jeu, pour une organisation plus claire.

##Description

###board.c et board.h
Ces fichiers gèrent la structure du plateau elle-même, ainsi que les fonctions la manipulant, permettant dans les autres fichiers de coder en ignorant le plus possible les spécificités de la structure.

###input.c et input.h
Ces fichiers servent à demander des entrées à l'utilisateur de manière sécurisée, pour éviter que le code plante sur une mauvaise entrée.

###main.c
Ce fichier contient la boucle de jeu, et constitue donc la colle qui réunit le reste.


##Extensions

###Le hérisson dopé
COMMANDE POUR LACTIVER
Cette extension permet de ne pas compter le premier héisson à atteindre son objectif, car il était évidemment dopé. Le joueur à qui il appartenait est donc obligé d'utiliser l'entièreté de ses hérissons restants pour pouvoir gagner. Ceci permet d'ajouter un peu de complexité à la stratégie.
DESCRIPTION IMPLEM VU QUE TU LAS FAIT

###Les sandwichs
COMMANDE POUR LACTIVER
Cette extension permet de donner plus de puissance à un joueur qui possède plusieurs hérissons sur une case (dont celui du haut). Il peut en effet, dans ce cas, déplacer toute la section entre le hérisson du haut et le prochain hérisson lui appartenant (inclus) en partant du haut si il le choisit. Il ne peut donc pas déplacer plus de 2 hérissons lui appartenant à la fois.
DESCRIPRION IMPLEM

##Synthèse
Nous avons observé que la plus grande difficulté ici était le travail en équipe et la communication. En effet, Chaque membre de l'équipe doit comprendre exactement ce qu'il doit faire dans le cadre du travail, mais aussi du fait que quelqu'un d'autre travaille au même projet.

##Bibliographie

http://www.gamecabinet.com/rules/IgelArgernVariants.html

TON LIEN(JE LAI PAS SUR MON LINUX)
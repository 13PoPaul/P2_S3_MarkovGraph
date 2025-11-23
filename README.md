# P2_S3_MarkovGraph
Study of Markov Graphs
The Git Hub Link : https://github.com/13PoPaul/P2_S3_MarkovGraph.git

Procedure for Installation :
Don't get the code from version control dosn't work !
Instead you want to use the file provied en the Zip or download it from the git Hub.
Then you should be able to run the programme but it would failed.
To correct the error you must do the following :
at the top right go to edit configurations. Then in working directory you want to click on the folder and select MarkovGraphTest
Here you go !


This is the conversation we had with Gemini 3.1 to do Part 3 :

 j'ai fais part3.c et H voici les consignes

 C'est parti pour la Partie 3 : Probabilités et Matrices.

Cette partie est mathématique mais très logique. Nous allons manipuler des matrices de transition pour simuler l'évolution du système (la météo, etc.) dans le temps.

Voici les fichiers matrix.h et matrix.c complets, incluant les Steps 1, 2 et le Bonus (Step 3).

1. Fichier d'en-tête : matrix.h
Ce fichier définit la structure t_matrix et les prototypes.

2. Fichier source : matrix.c
J'ai implémenté toutes les fonctions demandées, y compris le challenge du code "Bonus" que j'ai adapté et commenté.

3. Fichier de validation : main.c (Complet Step 1, 2, 3)
Voici comment tester tout ça (validation du fichier météo, convergence, et périodicité).

Tu auras besoin du fichier exemple_meteo.txt (les valeurs de la matrice M du PDF) :

pour le main tu peux me sortir le code que je dois rajouter en plus dans celui ci

Voici le code complet pour ton main.c.J'ai ajouté toute la logique de la Partie 3 à la suite de ton code existant. Cela inclut :La conversion du graphe en matrice.Le test de convergence (calcul de $M^n$ jusqu'à stabilisation).L'analyse par classe (Sous-matrice + Périodicité).Note importante : Assure-toi d'avoir bien inclus #include "matrix.h" (ou part3.h si tu l'as renommé ainsi, mais mes fichiers précédents s'appelaient matrix).

dans part 3.c ton include matrix marche pas il le reconnait pas qu'est ce que tu voulais faire ?

C'est ma faute, je t'ai donné des fichiers nommés matrix.h et matrix.c parce que le PDF mentionnait ces noms, mais ton projet suit la logique part1, part2... donc il est beaucoup plus logique d'appeler ça part3.h et part3.c.

Le problème est que dans le fichier .c, j'ai écrit #include "matrix.h", alors que ton fichier s'appelle probablement part3.h.

Voici les fichiers corrigés et renommés pour que tout fonctionne ensemble. Copie-colle simplement ces contenus.

1. Fichier part3.h
(Remplace tout le contenu de ton fichier actuel)

2. Fichier part3.c
(C'est ici que j'ai corrigé l'include pour appeler part3.h)

3. Mise à jour du main.c
Assure-toi que ton main.c inclut bien part3.h et non matrix.h.

je lui ai copié collé le terminal et il a confirmé le résultat nous avons ensuite demandé de noux epliquer tout ce qu'il avait fait

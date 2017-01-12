VERSCHAEVE Théo & CANDA Antoine
---------------------------------------------------------------------------------------------------------------------
Commande : 
---------------------------------------------------------------------------------------------------------------------

Pour compiler dans le repertoire source utiliser :	make. 
Pour nettoyer :	 make clean.

---------------------------------------------------------------------------------------------------------------------

Pour lancer : 

./display_stack  pour afficher la pile d'execution.
./try_mul pour la multiplication. Resultat quand utilise Ctrl + D
./ping_pong pour la version sans interruption via l'horloge
./ping_pong_bis pour la version du ping pong avec interruption du systeme
./philosophe pour l'utilisation des semaphores dans le cas de l'exemple des philosophes. 
./prodcons pour l'utilisation des semaphores dans le cas du producteur/consommateur.

---------------------------------------------------------------------------------------------------------------------


#TP1 : Ordennancement.

Tutoriel pour utiliser les fonctions :
	make compile les fichiers c.
	./display_stack affiche la pile d'éxecution.
	./try_mul va ensuite demander une liste d'entiers, et en faire la multiplication après un Ctrl+D ou qu'une des valeurs soit 0.
	
	On a ici vu les fonctions try et threw avec l'assembleur necessaire a la lecture / ecriture des registres ebp et esp. 

---------------------------------------------------------------------------------------------------------------------
	
#TP2 : Ordennancement (suite).

Pour ce TP, make crée en plus un fichier ping pong.
On peut le lancer avec ./ping_pong.
Ce fichier éxécute les fonctions ping et pong en séquence, ce qui cause d'afficher des chaines de "A1B2C1A2B1C2" à l'infini.
Pensez à arrêter le programme avec Ctrl + C.

	On a ici enrichi notre fonction init_ctx en create_ctx et creer la fonction switch_to. 
---------------------------------------------------------------------------------------------------------------------

#TP3 : Ordonnancement sur interruption

On lance avec ./ping_pong_bis

Pour ce TP, on a crée la fonction yield() et on a intégré le principe d'interruption selon un TIMER tout les X tips d'horloge. 
On a enrichi notre structure contexte, switch_to. 

Ajout de ping_pong_bis.c 

---------------------------------------------------------------------------------------------------------------------

#TP4: Semaphore 

On lance avec ./prodcons et ./philosophe

Pour ce TP,on a crée les sémaphores (sem.h et sem.c), le fichier prodcons.c reprenant le principe de producteur/consommateur pour une utilisation des semaphores dans le cadre de 
l'attente d'une ressource et la limitation en memoire du nombre de ressource (exemple ici 100).
Il y a egalement le fichier philosophe.c reprenant l'example vu en cours avec l'utilisation du semaphore dans le principe d'exclusion mutuelle (initialise a 1).

---------------------------------------------------------------------------------------------------------------------
Bilan

On a pu durant ces TP découvrir tester et enrichir un ordonnanceur étape par étape. 
On a pu commencer par une interruption quand le contexte souhaité rendre la main à une interruption sur top d'horloge (ordonnanceur preomptif).
On a pu découvrir un peu d'assembleur et l'utilisation qui peut être fait de semaphores (exclusion mutuelle sur une ressource partagee, attente d'une ressource..) et comment les
incorporer dans l'ordonnanceur. 
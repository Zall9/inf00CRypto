Makefile pour Linux : Il faut renommer le fichier Makefile_linux en Makefile.

N'oubliez pas de faire un make clean && make avant de tester.

Question 1 =================================================================
    test    : ./tp1 ABCDEFGHIJKLMNOPQRSTUVWXYZ 5 hash Salut
    test 2  : ./tp1 ABCDEFGHIJKLMNOPQRSTUVWXYZ 5 hash Bob

Question 2 =================================================================
    test    : ./tp1 abcdefghijklmnopqrstuvwxyz 4 calcul_n

Question 3 =================================================================
    test    : ./tp1 help

Question 4 =================================================================
    test    : ./tp1 abcdefghijklmnopqrstuvwxyz 4 i2c 1234

Question 5 =================================================================
    Recherche exhaustive :
        Temps : Afin de trouver une correspondance lors d'une recherche exhaustive, il serait nécessaire de parcourir toutes les entrées possibles,
        ce qui représente un nombre élevé d'opérations dans le pire des scénarios.
        Espace : Aucun espace supplémentaire n'est utilisé pour le précalcul,
        cependant cela implique des calculs répétitifs pour chaque vérification effectuée.

    Précalcul complet :
        Temps : Pour créer la table, il est nécessaire de précalculer toutes les empreintes, ce qui implique hauteur opérations pour chaque ligne.
        Espace : La table finale stocke toutes les empreintes de hauteur et les colonnes de largeur, ce qui demande un espace de hauteur * largeur.

    Comparaison des complexités :
        Recherche exhaustive : Temps = O(hauteur), Espace = 0
        Précalcul complet : Temps = O(hauteur * largeur), Espace = O(hauteur * largeur)
        Méthode de compromis temps-mémoire : Temps = O(k * log(hauteur)), Espace = O(hauteur)

    La méthode de compromis temps-mémoire offre une réduction de l'espace par rapport au précalcul complet,
    tout en maintenant une complexité de recherche raisonnable.
    Néanmoins, elle requiert des calculs supplémentaires pour chaque recherche par rapport à l'approche exhaustive.

Question 6 =================================================================
    test    : ./tp1 abcdefghijklmnopqrstuvwxyz 5 h2i oups 1

Question 7 =================================================================
    test    : ./tp1 abcdefghijklmnopqrstuvwxyz 5 i2i 1 1
    test 2  : ./tp1 abcdefghijklmnopqrstuvwxyz 5 i2i 1 10
    test 3  : ./tp1 abcdefghijklmnopqrstuvwxyz 5 i2i 1 100
    test 4  : ./tp1 abcdefghijklmnopqrstuvwxyz 5 i2i 1 1000

Question 8 =================================================================

Le fait d'ajouter le paramètre t dans la fonction h2i permets d'introduire un décalage supplémentaire lors du calcul de la fonction de hachage.
Ce décalage genère des indices distincts pour des empreintes identiques, ce qui augmente la couverture de la table.
Il est alors possible de différencier des textes clairs qui produiraient normalement la même empreinte.

Question 9 =================================================================
    test    : ./tp1 abcdefghijklmnopqrstuvwxyz 5 creer_table 10 10

Question 10 =================================================================
    test    : ./tp1 ABCDEFGHIJKLMNOPQRSTUVWXYZ 4 sauve_table 1000 1000 test.txt
    test 2  : ./tp1 abcdefghijklmnopqrstuvwxyz 4 info test.txt

Question 11 =================================================================

En reprenant le fichier generer par le premier test de la question 10, on est censé récupérer le mot CODE.

    test    : ./tp1 ABCDEFGHIJKLMNOPQRSTUVWXYZ 4 inverse test.txt 16de25af888480da1af57a71855f3e8c515dcb61

Question 12 =================================================================



Question 13 =================================================================

Question 14 =================================================================

Question 15 =================================================================

Question 16 =================================================================

Question 17 =================================================================

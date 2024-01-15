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

    test    : ./tp1 ABCDEFGHIJKLMNOPQRSTUVWXYZ 4 inverse test.txt 16de25af888480da1af57a71855f3e8c515dcb61 0

Question 12 =================================================================


La complexité de la fonction de recherche dichotomique est logarithmique en le nombre d’éléments composant le tableau dans lequel s’effectue la recherche.
Dans son pire cas, la compléxité de cette fonction est : O(log(n)) où n est la hauteur.

Question 13 =================================================================
    test    : ./tp1 abcdefghijklmnopqrstuvwxyz 4 stats 200 200

Question 14 =================================================================
    test 1 :
        ./tp1 ABCDEFGHIJKLMNOPQRSTUVWXYZ 4 sauve_table 1000 1000 test.txt
        ./tp1 ABCDEFGHIJKLMNOPQRSTUVWXYZ 4 inverse test.txt 16de25af888480da1af57a71855f3e8c515dcb61 0

    test 2 :
        ./tp1 "abcdefghijklmnopqrstuvwxyz0123456789,;:$." 5 sauve_table 1000 1000 test.txt
        ./tp1 "abcdefghijklmnopqrstuvwxyz0123456789,;:$." 5 inverse test.txt dafaa5e15a30ecd52c2d1dc6d1a3d8a0633e67e2 0

Question 15 =================================================================

La taille de la table arc-en-ciel serait très grande.
En effet, il y aurait environ 2,18 x 10^14 mots de passe possibles avec ces paramètres. 
Si chaque mot de passe est stocké dans la table avec son hachage correspondant, la taille de la table serait d’environ 1,6 x 10^21 octets.

Question 16 =================================================================
    test 1 :
        ./tp1 ABCDEFGHIJKLMNOPQRSTUVWXYZ 4 sauve_table 1000 1000 test.txt
        ./tp1 ABCDEFGHIJKLMNOPQRSTUVWXYZ 4 inverse test.txt 16de25af888480da1af57a71855f3e8c515dcb61 1
        pour une table de largeur 5000 et hauteur 500        
        Configuration :
        - Alphabet : ABCDEFGHIJKLMNOPQRSTUVWXYZ
        - Taille des textes clairs : 4
        - Nombre de textes clairs valides (N) : 456976
        Commande : inverse
        dCandidat correct trouvé : CODE , nombre de candidats : 2833
        Inverse trouvé : CODE
        Temps d'exécution : 2.883851 secondes

        pour une table de largeur 10000 et hauteur 750:
        Configuration :
            - Alphabet : ABCDEFGHIJKLMNOPQRSTUVWXYZ
            - Taille des textes clairs : 4
            - Nombre de textes clairs valides (N) : 456976
            Commande : inverse
            Candidat correct trouvé : CODE , nombre de candidats : 40701
            Inverse trouvé : CODE
            Temps d'exécution : 56.592038 secondes
        Test pour un mot de taille 5
        ./main "abcdefghijklmnopqrstuvwxyz0123456789,;:$." 5 sauve_table 10000 1000 test.txt && ./main "abcdefghijklmnopqrstuvwxyz0123456789,;:$." 5 inverse test.txt dafaa5e15a30ecd52c2d1dc6d1a3d8a0633e67e2 0
        Configuration :
            - Alphabet : abcdefghijklmnopqrstuvwxyz0123456789,;:$.
            - Taille des textes clairs : 5
            - Nombre de textes clairs valides (N) : 115856201
            Commande : inverse
        Candidat correct trouvé : n00b. , nombre de candidats : 64
        Inverse trouvé : n00b.
        Temps d'exécution : 2.012933 secondes
        Configuration :
            - Alphabet : abcdefghijklmnopqrstuvwxyz0123456789,;:$.
            - Taille des textes clairs : 5
            - Nombre de textes clairs valides (N) : 115856201

Question 17 =================================================================

Le sel est une chaîne de caractères aléatoires qui est ajoutée au mot de passe avant le hachage. Cette opération rend chaque hachage unique,
    même pour des mots de passe identiques.
Ainsi, même si un attaquant a accès à une table arc-en-ciel, il ne peut pas l’utiliser pour décrypter les mots de passe salés.
Il doit plutôt effectuer une attaque par force brute, qui est beaucoup plus lente et plus difficile à réaliser.
En conséquence, l’utilisation de sel pour les mots de passe est une technique efficace pour renforcer la sécurité des mots de passe et 
    empêcher les attaques par tables arc-en-ciel.
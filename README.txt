

Question 5:
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


#include <openssl/sha.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>

// ABCDEFGHIJKLMNOPQRSTUVWXYZ
typedef unsigned char byte;
struct Config {
    char *alphabet;
    int tailleAlphabet;
    int taille;
    unsigned long long N;
    char* TEXTE_CLAIR;
    byte EMPREINTE[SHA_DIGEST_LENGTH];
};


// Configuration globale
struct Config globalConfig;

struct Header {
    char *alphabet;
    int taille;
    int largeur;
    int hauteur;
};


void i2c(unsigned long long n, const char *alphabet, int taille, char *texteClair) {
    int i;
    for (i = taille - 1; i >= 0; --i) {
        texteClair[i] = alphabet[n % strlen(alphabet)];
        n /= strlen(alphabet);
    }
    texteClair[taille] = '\0';
}



void hash_SHA1(const char* s, byte* empreinte)
{
    SHA1((unsigned char*)s, strlen(s), empreinte);
}

uint64_t h2i(unsigned char *y, int t) {
    uint64_t empreinte = *((uint64_t *)y); // Convertir les 8 premiers octets en uint64_t
    return (empreinte + t) % globalConfig.N;
}

uint64_t i2i (int indice, int t) 
{
    // i2c
    i2c(indice, globalConfig.alphabet, globalConfig.taille, globalConfig.TEXTE_CLAIR);
    // printf("%d --i2c--> %s", indice, globalConfig.TEXTE_CLAIR);

    // H
    hash_SHA1(globalConfig.TEXTE_CLAIR, globalConfig.EMPREINTE);
    // printf("--h--> "); print_hexa(globalConfig.EMPREINTE);
    
    // empreinte
    uint64_t i = h2i(globalConfig.EMPREINTE, t);
    // printf(" --h2i(%d)--> %llu\n", t, i);
    return i;
}

int recherche(uint64_t **table, int hauteur, uint64_t idx, int *a, int *b) {
    int debut = 0;
    int fin = hauteur - 1;
    int trouve = 0;

    while (debut <= fin && !trouve) {
        int milieu = (debut + fin) / 2;

        if (table[milieu][1] == idx) {
            trouve = 1;
            *a = *b = milieu;

            // Recherche vers le haut
            while (*a > 0 && table[*a - 1][1] == idx) {
                (*a)--;
            }

            // Recherche vers le bas
            while (*b < hauteur - 1 && table[*b + 1][1] == idx) {
                (*b)++;
            }
        } else if (table[milieu][1] < idx) {
            debut = milieu + 1;
        } else {
            fin = milieu - 1;
        }
    }

    return trouve;
}

// Vérifie si un candidat est correct
int verifie_candidat(byte *h, int t, uint64_t idx, char *clair) {
    for (int i = t - 1; i >= 0; i--) {
        idx = i2i(idx, i);
    }

    i2c(idx, globalConfig.alphabet, globalConfig.taille, clair);
    byte h2[SHA_DIGEST_LENGTH];
    hash_SHA1(clair, h2);

    return memcmp(h2, h, SHA_DIGEST_LENGTH) == 0;
}

// Fonction d'inversion
int inverse(uint64_t **table, int hauteur, int largeur, byte *h, char *clair) {
    int trouve = 0;

    for (int t = largeur - 1; t > 0; t--) {
        uint64_t idx = h2i(h, t);
        int a, b;

        if (recherche(table, hauteur, idx, &a, &b)) {
            for (int i = a; i <= b; i++) {
                if (verifie_candidat(h, t, table[i][1], clair)) {
                    trouve = 1;
                    printf("Candidat correct trouvé : %s\n", clair);
                    break;
                }
            }
        }
        if (trouve) {
            break;
        }
    }

    if (trouve) {
        printf("Inverse trouvé : %s\n", clair);
        return 1;
    } else {
        printf("Aucun candidat correct trouvé. Nombre de candidats : %d\n");
        return 0;
    }
}


void sauve_table_ascii(char *filename, int largeur, int hauteur, uint64_t **table) {

    FILE *file = fopen(filename, "w");

    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    // Writer header
    struct Header w = { globalConfig.alphabet, globalConfig.taille, largeur, hauteur };
    fprintf(file, "%s\n", w.alphabet);
    fprintf(file, "%d\n", w.taille);
    fprintf(file, "%d\n", w.largeur);
    fprintf(file, "%d\n", w.hauteur);
    
    // Write table data
    for (int h = 0; h < hauteur; h++) {
        fprintf(file, "%lu %lu\n", table[h][0], table[h][1]);
    }
    fclose(file);
}

uint64_t** ouvre_table_ascii(char *filename, int *largeur, int *hauteur) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }

    struct Header h;
    char tempAlphabet[256];  // Assuming a maximum length for the alphabet

    // Read the alphabet dynamically
    if (fscanf(file, "%255s %d %d %d\n", tempAlphabet, &h.taille, &h.largeur, &h.hauteur) != 4) {
        perror("Error reading header");
        exit(1);
    }

    printf("alphabet = %s, taille = %d, largeur = %d, hauteur = %d\n", tempAlphabet, h.taille, h.largeur, h.hauteur);
    h.alphabet = malloc(strlen(tempAlphabet) + 1);
    strcpy(h.alphabet, tempAlphabet);

    *largeur = h.largeur;
    *hauteur = h.hauteur;

    uint64_t** table = (uint64_t**)malloc(*hauteur * sizeof(uint64_t*));
    for (int i = 0; i < *hauteur; i++) {
        table[i] = (uint64_t*)malloc(2 * sizeof(uint64_t));
        if (fscanf(file, "%lu %lu\n", &table[i][0], &table[i][1]) != 2) {
            perror("Error reading table entry");
            exit(1);
        }
    }

    fclose(file);

    return table;
}


void affiche_table(char* filename)
{
    int largeur, hauteur;
    uint64_t** table = ouvre_table_ascii(filename, &largeur, &hauteur);
    
     for (int h = 0; h < hauteur; h++) {
         printf("%lu %lu\n", table[h][0], table[h][1]);
     }
}

void help(char* name) {
    printf("Usage: %s <ALPHABET> <TAILLE> <COMMANDE> [ARGUMENTS]\n", name);
    printf("\n");
    printf("Available commands:\n");

    printf("  hash <STRING>\n"
           "            Compute the hash of the given string\n");

    printf("  i2c <NUMBER>\n"
           "            Convert the given number to a clear text\n");

    printf("  h2c <8_BYTE_HASH> <t> <N>\n"
           "            Process the given hash and values to retrieve a clear text\n");

    printf("\n");
    printf("Options:\n");
    printf("  <ALPHABET> <TAILLE>   Define alphabet and size of clear text\n");
    printf("  <COMMANDE>            Choose from the available commands\n");
    printf("  [ARGUMENTS]           Additional arguments required by specific commands\n");
}

int compare(const void *a, const void *b) {
    return (*((uint64_t **)a))[1] - (*((uint64_t **)b))[1];
}



void print_hexa(byte* empreinte)
{
    for (int i = 0; i < SHA_DIGEST_LENGTH; i++) {
        printf("%02x", empreinte[i]);
    }
}

// Fonction pour calculer N en fonction de alphabet et taille
void setUpConfig(char *alphabet, int taille) {
    globalConfig.alphabet = alphabet;
    globalConfig.taille = taille;
    globalConfig.tailleAlphabet = strlen(alphabet);
    globalConfig.TEXTE_CLAIR = malloc(taille);
    globalConfig.N = pow(globalConfig.tailleAlphabet, taille);
}

// Vérifier si la valeur de N est correcte
int estValeurCorrecte(unsigned long long N) {
    return N <= ULLONG_MAX;
}

uint64_t nouvelle_chaine(uint64_t idx1, int largeur)
{
    uint64_t indice = idx1;
    for( int t = 1; t < largeur; t++) {
        indice = i2i(indice, t);
    }
    return indice;
}

uint64_t index_aleatoire(){
    unsigned long n1 = rand();
    unsigned long n2 = rand();
    uint64_t n = ( (uint64_t) n2 ) + ( ( (uint64_t) n1 ) << 32 );
    uint64_t N = globalConfig.N;
    return n % N;
}

void creer_table(int largeur, int hauteur, uint64_t **table) {
    for (int i = 0; i < hauteur; i++) {
        table[i] = (uint64_t *)malloc(2 * sizeof(uint64_t));
    }

    for (int h = 0; h < hauteur; h++) {
        uint64_t idx = index_aleatoire();
        uint64_t last_idx = nouvelle_chaine(idx, largeur);
        table[h][0] = idx;
        table[h][1] = last_idx;
    }

    // Print the unsorted table
    for (int i = 0; i < hauteur; i++) {
        printf("%lu %lu\n", table[i][0], table[i][1]);
    }

    // Sort the table by the second column
    qsort(table, hauteur, sizeof(uint64_t *), compare);
    
    // Print the sorted table
    printf("\nSorted Table:\n");
    for (int i = 0; i < hauteur; i++) {
        printf("%lu %lu\n", table[i][0], table[i][1]);
    }
}

void hexstr_to_bytes(const char *hexstr, byte *bytes) {
    while (*hexstr && hexstr[1]) {
        sscanf(hexstr, "%2hhx", bytes++);
        hexstr += 2;
    }
}



int main(int argc, char *argv[]) {
    srand(time(NULL));
    
    if (argc < 4) {
        printf("Usage: %s <ALPHABET> <TAILLE> <COMMANDE> [ARGUMENTS]\n", argv[0]);
        return 1;
    }

    // for (int i = 0; i < argc; i++) {
    //         printf("argv[%d]: %s\n", i, argv[i]);
    // }

    char *commande = argv[3];
    setUpConfig(argv[1], atoi(argv[2]));

    if (!estValeurCorrecte(globalConfig.N)) {
        printf("Erreur : la valeur de N n'est pas correcte.\n");
        return 1;
    }

    printf("Commande : %s\n", commande);
    if (strcmp(commande, "hash") == 0) {
       printf("Commande : hash\n");

       if (argc < 5) {
              printf("Usage: %s hash <STRING>\n", argv[0]);
              return 1;
       }
       byte empreinte[SHA_DIGEST_LENGTH];
       hash_SHA1(argv[4], empreinte);
       printf("Hash de '%s': ", argv[4]);
       for (int i = 0; i < SHA_DIGEST_LENGTH; ++i) {
              printf("%02x", empreinte[i]);
       }
       printf("\n");       
    }
    else if (strcmp(commande, "i2c") == 0) {
       printf("Commande : i2c\n");
       if (argc < 5) {
              printf("Usage: %s i2c <NUMBER>\n", argv[0]);
              return 1;
       }
       unsigned long long nombre = strtoull(argv[4], NULL, 10);
       char texteClair[globalConfig.taille + 1];
       i2c(nombre, globalConfig.alphabet, globalConfig.taille, texteClair);
       printf("i2c(%llu) = \"%s\"\n", nombre, texteClair);
    }
    else if (strcmp(commande, "h2i") == 0) {
        // ./main abcdefghijklmnopqrstuvwxyz 5 h2i oups 1
       if (argc < 6) {
         printf("Usage: %s <ALPHABET> <TAILLE> h2i <WORD_TO_HASH> <t>\n", argv[0]);
         return 1;
       }
       
       // Calcul du hash 
       char* word = argv[4];
       byte hash[SHA_DIGEST_LENGTH];
       hash_SHA1(word, hash);
       
       // Recupere t, N
       int t = atoi(argv[5]);
       uint64_t N = globalConfig.N;
       
       // Calcul h2i
       uint64_t indice = h2i(hash, t);
       
       printf("alphabet: %s\n", globalConfig.alphabet);
       printf("taille: %d\n", globalConfig.taille);
       printf("N: %llu\n", N);
       printf("hash(\"%s\") = ", word);print_hexa(hash);       
       printf("h2i(hash(%s), %d) = %llu\n", word, t, indice);
       
    } 
    else if (strcmp(commande, "i2i") == 0) {
        // ./main abcdefghijklmnopqrstuvwxyz 5 i2i
        if (argc < 5) {
            printf("Usage: %s <ALPHABET> <TAILLE> i2i <t> <LARGEUR>\n", argv[0]);
            return 1;
        }
         // Recupere t, N
        int t = atoi(argv[4]);
        int largeur = atoi(argv[5]);
        
        // Calcul i2i
        uint64_t last_indice = nouvelle_chaine(t, largeur);

        printf("alphabet: %s\n", globalConfig.alphabet);
        printf("taille: %d\n", globalConfig.taille);
        printf("N: %llu\n\n", globalConfig.N);
        printf("chain of length %d: 1 ... %llu\n", largeur, last_indice);

    }
    else if (strcmp(commande, "creer_table") == 0) {
        // ./main abcdefghijklmnopqrstuvwxyz 5 creer_table 200 100
        if (argc < 5) {
            printf("Usage: %s <ALPHABET> <TAILLE> creer_table <LARGEUR> <HAUTEUR>\n", argv[0]);
            return 1;
        }

        int largeur = atoi(argv[4]);
        int hauteur = atoi(argv[5]);

        uint64_t table[hauteur][2];
        creer_table(largeur, hauteur, table);
    }
    else if (strcmp(commande, "sauve_table") == 0) {
        // ./main abcdefghijklmnopqrstuvwxyz 5 sauve_table 200 100 test.txt
        if (argc < 6) {
            printf("Usage: %s <ALPHABET> <TAILLE> sauve_table <LARGEUR> <HAUTEUR> <FILENAME>\n", argv[0]);
            return 1;
        }

        int largeur = atoi(argv[4]);
        int hauteur = atoi(argv[5]);
        
        uint64_t table[hauteur][2];
        creer_table(largeur, hauteur, table);

        sauve_table_ascii(argv[6], largeur, hauteur, table);
    }
    else if (strcmp(commande, "info") == 0) {
        // ./main abcdefghijklmnopqrstuvwxyz 5 info test.txt
        if (argc < 5) {
            printf("Usage: %s <ALPHABET> <TAILLE> info <FILENAME>\n", argv[0]);
            return 1;
        }

        affiche_table(argv[4]);
    }
    else if (strcmp(commande, "inverse") == 0){
        printf("TEST:%s, %s, %s", argv[5], argv[6], argv[7]);
        if (argc < 5) {
                printf("Usage: %s <ALPHABET> <TAILLE> inverse <hauteur> <largeur> <8_BYTE_HASH>\n", argv[0]);
                return 1;
            }

            int hauteur = atoi(argv[4]);
            int largeur = atoi(argv[5]);
            byte hash   = atoi(argv[6]);
            uint64_t **table = (uint64_t **)malloc(hauteur * sizeof(uint64_t *));
            for (int i = 0; i < hauteur; i++) {
                table[i] = (uint64_t *)malloc(2 * sizeof(uint64_t));
            }

            // Création de la table
            creer_table(largeur, hauteur, table);

            char clair[globalConfig.taille + 1];

            hexstr_to_bytes(argv[4], &hash);

            if (inverse(table, hauteur, largeur, &hash, clair)) {
                printf("Inverse trouvé : %s\n", clair);
            } else {
                printf("Aucun candidat correct trouvé.\n");
            }
    }
    else {
        printf("Erreur : commande non reconnue.\n");
    }

    printf("\n\nConfiguration :\n");
    printf(" - Alphabet : %s\n", globalConfig.alphabet);
    printf(" - Taille des textes clairs : %d\n", globalConfig.taille);
    printf(" - Nombre de textes clairs valides (N) : %llu\n", globalConfig.N);

    return 0;
}

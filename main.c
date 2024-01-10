#include <openssl/sha.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <limits.h> // Inclure pour ULLONG_MAX
void help(char* name)
{
    printf("usage: %s <CMD> [OPTIONS] [ARGS]\n", name);
    printf("\n");
    printf("Available commands:\n");

    printf("  create <height> <width> [start] [end] [step] <TEMPLATE>\n"
           "            create the corresponding rainbow tables\n");
    printf("  info <FILENAME> [LIMIT]\n"
           "            display some information about the table from given file\n");

    printf("  stats <height> <width> [n] [N]\n"
           "            compute some information about rainbow tables without computing them\n"
           "            (N=number of hash to compute to estimate\n"
           "            time of single hash, default 1000000)\n");

    printf("  crack <H> <FILENAMES> ...\n"
           "            crack the given hash with the rainbow tables\n");

    printf("  bruteforce <H>\n"
           "            brute force the given hash\n");

    printf("  test ...\n"
           "            development tests (run \"%s test list\" for available tests)\n",
        name);

    printf("\n");
    printf("Available options:\n");
    printf("  --sha1                  use sha1 hash function (default)\n");
    printf("  --md5                   use md5 hash function\n");
    printf("  --LM                    use LAN manager hash function\n");

    printf("  --alphabet <s>          allowed characters for clear text\n");
    printf("  -A <N> / --abc <N>      choose standard alphabet:\n");
    printf("         N=26               abcdefghijklmnopqrstuvwxyz (default)\n");
    printf("         N=26A              ABCDEFGHIJKLMNOPQRSTUVWXYZ\n");
    printf("         N=36               abcdefghijklmnopqrstuvwxyz0123456789\n");
    printf("         N=40               "
           "abcdefghijklmnopqrstuvwxyz0123456789,;:$\n");
    printf("         N=52               "
           "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz\n");
    printf("         N=62               "
           "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
           "\n");
    printf("         N=66               "
           "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz,;:"
           "$\n");

    printf("  --min-size <n> / -m <n> minimum size of clear text (default: 5)\n");
    printf("  --max-size <n> / -M <n> maximum size of clear text (default: 5)\n");
    printf("  -s <n> / --size <n>     exact size of clear text (default: 5)\n");

    printf("  -d <n> / --delay <n>    delay (seconds) between log messages (default 5)\n");

    printf("  -help / -h              this message\n");
}

typedef unsigned char byte;
void hash_SHA1(const char* s, byte* empreinte)
{
    SHA1((unsigned char*)s, strlen(s), empreinte);
}

struct Config {
    char *alphabet;
    int taille;
    unsigned long long N;
};

// Configuration globale
struct Config globalConfig;

// Fonction pour calculer N en fonction de alphabet et taille
void calculerN(char *alphabet, int taille) {
    globalConfig.alphabet = alphabet;
    globalConfig.taille = taille;

    int tailleAlphabet = strlen(alphabet);
    globalConfig.N = (unsigned long long)pow(tailleAlphabet, taille);
}

// Vérifier si la valeur de N est correcte
int estValeurCorrecte(unsigned long long N) {
    return N <= ULLONG_MAX;
}

// Afficher la configuration
void afficherConfiguration() {
    printf("Configuration :\n");
    printf(" - Alphabet : %s\n", globalConfig.alphabet);
    printf(" - Taille des textes clairs : %d\n", globalConfig.taille);
    printf(" - Nombre de textes clairs valides (N) : %llu\n", globalConfig.N);
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("Usage: %s <ALPHABET> <TAILLE> <COMMANDE> [ARGUMENTS]\n", argv[0]);
        return 1;
    }

    char *alphabet = argv[1];
    int taille = atoi(argv[2]);
    char *commande = argv[3];

    calculerN(alphabet, taille);

    if (!estValeurCorrecte(globalConfig.N)) {
        printf("Erreur : la valeur de N n'est pas correcte.\n");
        return 1;
    }

    if (strcmp(commande, "create") == 0) {
        // Ajoutez ici le code pour créer une table arc-en-ciel (question 10)
        printf("Commande : create\n");
        // Ajoutez votre code ici
    } else if (strcmp(commande, "crack") == 0) {
        // Ajoutez ici le code pour craquer un mot de passe (question 11)
        printf("Commande : crack\n");
        // Ajoutez votre code ici
    } else if (strcmp(commande, "test") == 0) {
        // Ajoutez ici le code pour les tests correspondants
        printf("Commande : test\n");
        // Ajoutez votre code ici
    } else {
        printf("Erreur : commande non reconnue.\n");
        return 1;
    }

    afficherConfiguration();

    return 0;
}

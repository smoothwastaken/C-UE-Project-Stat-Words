#include <stdio.h>
#include <stdlib.h>

#define TAILLE_MAX 50

// Mot d’un texte
struct sMot {
    char * mot ; // le mot (chaîne de caractères allouée dynamiquement )
    int taille ; // nombre de caractères du mot
    int occurrences ; // nombre d’occurrences du mot dans un texte
    struct sMot * suivant ; // mot suivant dans le contexte d’une liste chaînée
};

// Liste de mots
struct sListeMots {
    struct sMot * debut ; // pointeur vers le premier mot de la liste
    struct sMot * fin ; // pointeur vers le dernier mot de la liste
    int nbMots ; // nombre de mots de la liste
};

struct sMot * motCreer(char *mot, int occ) {
    // Alloue la structure du mot
    struct sMot * tMot = malloc(sizeof(struct sMot));
    if (tMot == NULL) {
        return NULL;
    }

    // Trouve la longueur du mot en question
    int lenMot = 0;
    while (mot[lenMot] != '\0' && lenMot < TAILLE_MAX) {
        lenMot ++;
    }

    // Alloue la place pour le mot
    char * TabMot = (char *) malloc((lenMot + 1) * sizeof(char));
    if (TabMot == NULL) {
        return NULL;
    }

    // Remplie TabMot avec les valeurs de mot passé en paramètre.
    for (int i = 0; i < lenMot; i ++) {
        TabMot[i] = mot[i];
    }

    // Associe les valeurs au mot.
    tMot -> mot = TabMot;
    tMot -> taille = lenMot;
    tMot -> occurrences = occ;
    tMot -> suivant = NULL;

    return tMot;
}

void motLiberer(struct sMot *mot) {
    free(mot -> mot);
    free(mot);
}

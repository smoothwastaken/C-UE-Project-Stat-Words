#include <stdio.h>
#include <stdlib.h>
#include "listemots.h"

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

tListeMots creerListeMots(void) {
    // Alloue la structure de la liste
    tListeMots liste = malloc(sizeof(struct sListeMots));
    if (liste == NULL) {
        return NULL;
    }

    // Initialise les valeurs de la liste
    liste -> debut = NULL;
    liste -> fin = NULL;
    liste -> nbMots = 0;

    return liste;
}

void detruireListeMots(tListeMots liste) {
    // Libère chaque mot de la liste
    struct sMot * courant = liste -> debut;
    struct sMot * suivant = NULL;
    while (courant != NULL) {
        suivant = courant -> suivant;
        motLiberer(courant);
        courant = suivant;
    }

    // Libère la liste
    free(liste);

    return;
}

int nombreDeMots(tListeMots liste) {
    // Retourne le nombre de mots de la liste
    return liste -> nbMots;
}

void ajouterMotAvecOcc(tListeMots liste, char *mot, int nbOcc) {
    // Crée un nouveau mot
    struct sMot * nouveauMot = motCreer(mot, nbOcc);

    // Vérifie si le mot a été créé
    if (nouveauMot == NULL) {
        return;
    }

    // Ajoute le mot à la liste selon si la liste est vide ou non
    // Si la liste est vide, le mot est le premier et le dernier de la liste.
    if (liste -> debut == NULL) {
        liste -> debut = nouveauMot;
        liste -> fin = nouveauMot;
    // Sinon, le mot est ajouté à la fin de la liste.
    } else {
        liste -> fin -> suivant = nouveauMot;
        liste -> fin = nouveauMot;
    }

    // Incrémente le nombre de mots de la liste
    liste -> nbMots ++;

    return;
}

void ajouterMot(tListeMots liste, char *mot) {
    // Ajoute un mot à la liste avec une occurrence de 1
    ajouterMotAvecOcc(liste, mot, 1);
}

void ecrireListeMots(tListeMots liste, FILE *fich) {
    // Écrit les mots de la liste dans un fichier
    struct sMot * courant = liste -> debut;

    // Écrit chaque mot de la liste dans le fichier
    while (courant != NULL) {
        // Écrit le mot et un espace
        fprintf(fich, "%s ", courant -> mot);
        // Passe au mot suivant
        courant = courant -> suivant;
    }

    // Retour à la ligne
    fprintf(fich, "\n");

    return;
}

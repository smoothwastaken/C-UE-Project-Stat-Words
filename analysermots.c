#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "listemots.h"
#include "utils.h"

#define TAILLE_MAX_MOT 100
#define TAILLE_MAX_PHRASES 10000


long get_file_size(char *filename) {
    FILE *fp = fopen(filename, "r"); // Ouvre le fichier en mode lecture
    if (fp == NULL) return EXIT_FAILURE; // Vérifie si le fichier a bien été ouvert

    if (fseek(fp, 0, SEEK_END) < 0) { // Déplace le curseur à la fin du fichier
        fclose(fp);
        return EXIT_FAILURE;
    }

    long size = ftell(fp); // Obtient la position actuelle du curseur, c'est-à-dire la taille du fichier
    fclose(fp); // Ferme le fichier
    return size;
}

int main(int argc, char *argv[]) {
    /* Créez la fonction principale pour l’analyse de la fréquence des mots d’un texte dans le fichier
    analysermots.c qui utilisera les modules listemots et utils. Vous compléterez le Makefile précédent
    en ajoutant la cible analysermots pour produire l’exécutable. Ce dernier devra être appelé avec deux
    arguments (faites les vérifications usuelles sur le nombre d’arguments reçus) : le nom du fichier à
    analyser et la taille minimale des mots que nous souhaitons considérer. Exemple :
    make analysermots
    ./ analysermots le - tour - du - monde - en -80 - jours - iso -8859 -1. txt 4
    De manière similaire au niveau 1, le fichier texte devra être lu caractère par caractère. Dès qu’un
    nouveau mot est détecté, ce dernier doit être ajouté à la liste s’il n’est pas déjà présent, sinon son
    nombre d’occurrences doit être mis à jour (incrémenté de 1).
    Une fois tout le texte analysé, deux fichiers seront produits en sortie (selon le format défini dans la
    fonction ecrireCsvListeMots) :
    — liste_mots_01.txt qui contiendra la liste complète des mots du texte avec leur nombre d’occurrences ;
    — liste_mots_02.txt qui contiendra uniquement les mots dont la taille est supérieure ou égale
    au deuxième argument passé au programme.
    N’oubliez pas de libérer la mémoire à la fin de votre programme.
    Comme précédemment, vous pouvez lire les fichiers produits avec un éditeur de texte en activant
    l’encodage ISO 8859-1, ou en utilisant le fichier ouvrirLatin1.html que nous vous fournissons. */

    // Vérifie si le nombre d'arguments est correct
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <fichier> <taille_min>\n", argv[0]);
        return 1;
    }

    // Récupération de la taille du fichier
    long size = get_file_size(argv[1]);
    if (size == EXIT_FAILURE) {
        perror("get_file_size");
        return EXIT_FAILURE;
    }

    // Ouverture du fichier
    FILE *fichier = fopen(argv[1], "r");
    if (fichier == NULL) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    tListeMots tousLesMots = creerListeMots();

    // Lecture du fichier (caractère par caractère)
    // On vérifie à chaque fois si c'est la fin d'un mot ou d'une phrase, et on forme le mot ou la phrase.
    char mot[TAILLE_MAX_MOT] = {'a'};
    long cursorPos = 0;
    int i = 0;
    while (cursorPos < size) {
        // Lecture du caractère
        char c = fgetc(fichier);

        // Si on arrive à la fin du fichier, on sort de la boucle
        if (c == EOF) break;

        // Détection de la fin d'un mot et ajout du mot à la liste (si c'est un mot)
        if (caractereDunMot(c)) {
            mot[i] = c;
            i++;

        } else if (i > 0 ) {
            // On ajoute le mot à la liste des mots
            mot[i] = '\0';
            ajouterOccurrenceMot(tousLesMots, mot);

            // On réinitialise le mot
            for (int i = 0; i < TAILLE_MAX_MOT; i ++) {
                mot[i] = 'a';
            }
            i = 0;
        }

        cursorPos++;
    }

    // Création des fichiers de sortie
    // Fichier 1 : liste_mots_01.txt
    ecrireCsvListeMots(tousLesMots, "liste_mots_01.txt");

    // Fichier 2 : liste_mots_02.txt
    // Suppression des mots de taille inférieure à la taille minimale
    int tailleMin = atoi(argv[2]);
    supprimerPetitsMots(tousLesMots, tailleMin);
    ecrireCsvListeMots(tousLesMots, "liste_mots_02.txt");

    // Fermeture du fichier
    fclose(fichier);
}

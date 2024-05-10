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
    // Récupération du nom du fichier à analyser passé en argument
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <fichier>\n", argv[0]);
        return EXIT_FAILURE;
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

    long nbPhrases = 0;
    long nbMots = 0;
    long sommeTailleMot = 0;
    long nbCaracteres = 0;

    tListeMots currentPhrase = creerListeMots();
    tListeMots phraseLaPlusLongue = creerListeMots();
    tListeMots listePhrases[TAILLE_MAX_PHRASES + 1];

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

        // Comptage du nombre de caractères
        nbCaracteres++;

        // Détection de la fin d'un mot et ajout du mot à la liste (si c'est un mot)
        if (caractereDunMot(c)) {
            mot[i] = c;
            sommeTailleMot++;
            i++;

        } else if (i > 0 ) {
            // On ajoute le mot à la liste des mots
            mot[i] = '\0';
            ajouterOccurrenceMot(currentPhrase, mot);

            // On vérifie si c'est la fin d'une phrase
            if (caractereFinDePhrase(c)) {

                // On ajoute la phrase à la liste des phrases
                listePhrases[nbPhrases] = currentPhrase;

                // On vérifie si c'est la phrase la plus longue
                if (nombreDeMots(currentPhrase) > nombreDeMots(phraseLaPlusLongue)) {
                    phraseLaPlusLongue = currentPhrase;
                }

                // On réinitialise la phrase courante
                currentPhrase = creerListeMots();

                // On incrémente le nombre de phrases
                nbPhrases++;
            }

            // On réinitialise le mot
            for (int i = 0; i < TAILLE_MAX_MOT; i ++) {
                mot[i] = 'a';
            }

            nbMots++;
            i = 0;
        }

        cursorPos++;
    }

    // Calcul de la longueur moyenne d'un mot
    float longueurMoyenneMot = (double) sommeTailleMot / (double) nbMots;

    // Calcul de la longueur moyenne d'une phrase (en nombre de mots)
    float longueurMoyennePhrase = (double) nbMots / (double) nbPhrases;

    // Fermeture du fichier
    fclose(fichier);

    // Ouverture du fichier de statistiques
    FILE *fichierStats = fopen("statistiques.txt", "w+");
    if (fichierStats == NULL) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    // Écriture des statistiques dans le fichier
    fprintf(fichierStats, "Texte : %s\n", argv[1]);
    fprintf(fichierStats, "Nombre de phrases : %ld\n", nbPhrases);
    fprintf(fichierStats, "Nombre de mots : %ld\n", nbMots);
    fprintf(fichierStats, "Nombre de caracteres : %ld\n", nbCaracteres);
    fprintf(fichierStats, "Longueur moyenne d'un mot : %.2f\n", longueurMoyenneMot);
    fprintf(fichierStats, "Longueur moyenne d'une phrase : %.2f\n", longueurMoyennePhrase);
    fprintf(fichierStats, "Phrase la plus longue (%d mots) : ", nombreDeMots(phraseLaPlusLongue));

    ecrireListeMots(phraseLaPlusLongue, fichierStats); // Écrire la phrase ici

    // Fermeture du fichier de statistiques
    fclose(fichierStats);

    return EXIT_SUCCESS;
}

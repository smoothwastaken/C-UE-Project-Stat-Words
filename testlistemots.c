#include "listemots.h"

#define EXIT_SUCCESS 0

int main(void) {

    // Nouvelle liste
    tListeMots liste = creerListeMots();

    // Ajout de mots
    ajouterMotAvecOcc(liste, "Bonjour", 1);
    ajouterMotAvecOcc(liste, "Salut", 2);
    ajouterMotAvecOcc(liste, "Hello", 1);

    // Affichage de la liste
    ecrireListeMots(liste, stdout);

    // Destruction de la liste
    detruireListeMots(liste);

    return EXIT_SUCCESS;
}

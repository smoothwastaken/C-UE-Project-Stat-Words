#include <stdio.h>

#ifndef LISTEMOTS_H
#define LISTEMOTS_H

// Type permettant de manipuler une liste de mots
typedef struct sListeMots * tListeMots ;

extern tListeMots creerListeMots(void);

extern void detruireListeMots(tListeMots liste);

extern int nombreDeMots(tListeMots liste);

extern void ajouterMotAvecOcc(tListeMots liste, char *mot, int nbOcc);

extern void ajouterMot(tListeMots liste, char *mot);

extern void ecrireListeMots(tListeMots liste, FILE *fich);

#endif /* LISTEMOTS_H */

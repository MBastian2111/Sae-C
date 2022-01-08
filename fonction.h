#ifndef FONCTION_H_
#define FONCTION_H_

#define STRIN 28
#define LSTRIN 48
#define SSTRIN 16
#define VSSTRIN 7
struct personne // Création d'une structure personne pour stocker chaque lignes du fichier
{
  char prenom[STRIN], nom[STRIN], ville[STRIN], numtel[SSTRIN], email[LSTRIN],
      fonction[STRIN], codepost[VSSTRIN]; // création de string pour stocker
                                          // individuelement chaque info
};
typedef struct personne personne; // défini la structure personne comme un type

 

personne *ouvrir_fichier(char*, long*);

void viderBuffer(void);

long savelefichier(personne *,long*);

long afficher(personne* , personne, long* );

personne entrer_champs_personne(void);

long filtre(personne *, long*);

long selecligne(personne *, long*);

void quicksort(personne *, long, long, int);

void modif_personne(personne *, long*);

personne *ajout_personne(personne *, long*);

personne *suppression_personne(personne *, long*);

void clrscr();

#endif 
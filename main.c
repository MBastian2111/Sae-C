#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonction.h"
typedef struct personne personne; // défini la structure personne comme un type
personne defaultpersonne = {'\0', '\0', '\0', '\0','\0', '\0', '\0'}; // Création d'une personne vide pour pouvoir une valeur par défaut sur certainnes fonction



int main(void)
{
  long nbligne = 0;
  personne *annuaire = NULL;
  long ligne, etat, cpasfini = 1, etatfichier = 0;
  int choix;
  char nomfichier[100];
  while (cpasfini)
  {
    if (etatfichier == 0)
    {
      do
      {
        printf("Aucun fichier n'est ouvert, entrer le nom du fichier pour ouvrir ou juste sur entrer pour fermer le programme :\n");
        fgets(nomfichier, 100, stdin);
        clrscr();
        if(nomfichier[0]=='\n')
        {
          return 0;
        }
        nomfichier[strlen(nomfichier) - 1] = '\0';
        annuaire = ouvrir_fichier(nomfichier, &nbligne);
      } while (annuaire == NULL);
        etatfichier = 1;
      
    }
    {
      if (etatfichier == 2)
        printf("Le fichier n'est pas sauvegarder\n");
      printf("1) Ajouter un client\n");
      printf("2) Modifier un client\n");
      printf("3) Supprimer un client\n");
      printf("4) Afficher tout les clients\n");
      printf("5) Filtrer et afficher les clients\n");
      printf("6) Sauvegarder le fichier\n");
      printf("7) Trier le fichier\n");
      printf("8) Afficher les ligne avec des information manquante\n");
      printf("9) Fermer le fichier\n");
      scanf("%d", &choix);
      viderBuffer();
      clrscr();

      switch (choix)
      {
      case 1:
        annuaire = ajout_personne(annuaire, &nbligne);
        etatfichier = 2;
        break;
      case 2:
        modif_personne(annuaire, &nbligne);
        etatfichier = 2;
        break;
      case 3:
        annuaire = suppression_personne(annuaire, &nbligne);
        etatfichier = 2;
        break;
      case 4:
        afficher(annuaire, defaultpersonne, &nbligne);
        break;
      case 5:
        afficher(annuaire, entrer_champs_personne(), &nbligne);
        break;
      case 6:
        savelefichier(annuaire, &nbligne);
        etatfichier = 1;
        break;
      case 7:
        printf("0 : prenom | 1 : nom | 2 : ville | 3 : code-postal | 4 : numéro | 5 : email | 6 : fonction ");
        scanf("%d", &choix);
        viderBuffer();
        clock_t start = clock();
        quicksort(annuaire, 0, nbligne - 1, choix);
        clock_t end = clock();
        float seconds = (float)(end - start) / CLOCKS_PER_SEC;
        printf("%f s", seconds);
        break;
      case 8:
        info_manquante(annuaire, &nbligne);
        break;
      case 9:
        etatfichier = 0;
        free(annuaire);
        break;
      default:
        printf("nombre incorect");
        break;
      }
    }
  }
  return 0;
}
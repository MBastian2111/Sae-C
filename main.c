#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonction.h"
typedef struct personne personne; // défini la structure personne comme un type
personne defaultpersonne = {'\0', '\0', '\0', '\0','\0', '\0', '\0'}; // Création d'une personne vide pour pouvoir une valeur par défaut sur certainnes fonction



int main(void) // Bastian Mounier
{
  long nbligne = 0;
  personne *annuaire = NULL;
  long ligne, cpasfini = 1; // Cpasfini fait tourner le programme à l'infini
  int choix,etatfichier = 0; //variable pour stocker l'input du user, si le fichier est ouvert et si le fichier est sauvegardé
  char nomfichier[100]; //pour que l'utilisateur rentre le nom du fichier
  while (cpasfini) //boucle pour faire tourner le programme
  {
    if (etatfichier == 0) //fichier pas ouvert
    {
      do
      {
        printf("Aucun fichier n'est ouvert, entrer le nom du fichier pour ouvrir ou juste sur entrer pour fermer le programme :\n");
        fgets(nomfichier, 100, stdin);
        clrscr(); //fonction qui permet d'éffacer le terminal
        if(nomfichier[0]=='\n') // l'utilisateur à appuyer sur entrer pour fermer le programme
        {
          return 0; //fin du programme
        }
        nomfichier[strlen(nomfichier) - 1] = '\0'; //remplace l'\n par un \0
        annuaire = ouvrir_fichier(nomfichier, &nbligne);
      } while (annuaire == NULL); //detecter si l'ouverture à fonctionné
        etatfichier = 1; // change l'état de du fichier
    }
    else //si le fichier est ouvert, il affiche le menu
    {
      if (etatfichier == 2) //si l'état du fichier est = à 2 alors il prévient l'utilisateur que le fichier n'est pas sauvgarder
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
      viderBuffer(); //vide \n du scanf dans le buffer
      clrscr();

      switch (choix) //switch case qui vas éxecuter la fonction demander par utilisateur, change l'état du fichier si le fichier est modifié
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
        printf("0 : prenom | 1 : nom | 2 : ville | 3 : code-postal | 4 : numéro | 5 : email | 6 : fonction "); //demande quel trie tu veux
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
}
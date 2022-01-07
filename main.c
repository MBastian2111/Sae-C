#include <endian.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STRIN 28
#define LSTRIN 48
#define SSTRIN 16
#define VSSTRIN 7

int nbligne = 0;

struct personne // Création d'une structure personne pour stocker chaque lignes
                // du fichier
{
  char prenom[STRIN], nom[STRIN], ville[STRIN], numtel[SSTRIN], email[LSTRIN],
      fonction[STRIN], codepost[VSSTRIN]; // création de string pour stocker
                                          // individuelement chaque info
};
typedef struct personne personne; // défini la structure personne comme un type

personne defaultpersonne = {
    '\0', '\0', '\0', '\0',
    '\0', '\0', '\0'}; // Création d'une personne vide pour pouvoir une valeur
                       // par défaut sur certainnes fonction

personne *ouvrir_fichier(char *nom_fichier) // Création d'une fonction qui à pour
                                            // butd'ouvrir perser un fichier csv
{
  int c, j = 0, k = 0, field_count = 0, i = 0; //c sert à stocker les lettre pour compter le nombre de ligne, j correspond à l'avancement dans le buffer de la ligne, k correspond à l'emplacement d'écriture dans le tableau de structure, field_count est le numéro de variable qu'on écri(nom, prénom), i correspond au numéro de ligne
  char buff[1024]; // cette variable stocke la une ligne du fichier csv
  FILE *fp = fopen(nom_fichier, "r"); // ouvre le fichier donner par l'utilisateur en lecture

  if (!fp) //test si le pointeur du fichier est égal à null, si oui alors il y a eu un problème à l'ouverture
  {
    printf("error fichier\n");
    return NULL;
  }
  for (c = getc(fp); c != EOF; c = getc(fp)) //cet boucle for compte le nombre d'\n pour connaitre le nombre de ligne
  {
    if (c == '\n') 
      nbligne = nbligne + 1;
  }
  printf("nbligne : %d \n", nbligne); // affiche pour l'utilisateur le nombre de ligne chargé
  personne *values = NULL; //créé un pointeur null pour le tableau de sctruct
  values = malloc(sizeof(personne) * nbligne); //allocation de la mémoire pour le tableau de struct pour ouvrir chargé et parser le fichier
  if (values == NULL) // vérifie si l'allocation de la mémoire à fonctionner
  {
    printf("Problème de mémoire ram");
    exit(1);
  }
  fseek(fp, 0, SEEK_SET); //remet le pointeur du qui lis le fichier au début

  while (fgets(buff, 1024, fp)) //cet boucle charge ch
  {
    field_count = 0;
    j = 0;
    k = 0;
    while (buff[j] != '\n' && buff[j] != '\r' && buff[j] != EOF)
    {
      if (buff[j] == ',')
      {
        if (field_count == 0)
        {
          values[i].prenom[k] = '\0';
        }
        else if (field_count == 1)
        {
          values[i].nom[k] = '\0';
        }
        else if (field_count == 2)
        {
          values[i].ville[k] = '\0';
        }
        else if (field_count == 3)
        {
          values[i].codepost[k] = '\0';
        }
        else if (field_count == 4)
        {
          values[i].numtel[k] = '\0';
        }
        else if (field_count == 5)
        {
          values[i].email[k] = '\0';
        }
        else if (field_count == 6)
        {
          values[i].fonction[k] = '\0';
        }

        k = 0;
        field_count++;
      }
      else
      {
        if (field_count == 0)
        {
          values[i].prenom[k] = buff[j];
        }
        else if (field_count == 1)
        {
          values[i].nom[k] = buff[j];
        }
        else if (field_count == 2)
        {
          values[i].ville[k] = buff[j];
        }
        else if (field_count == 3)
        {
          values[i].codepost[k] = buff[j];
        }
        else if (field_count == 4)
        {
          values[i].numtel[k] = buff[j];
        }
        else if (field_count == 5)
        {
          values[i].email[k] = buff[j];
        }
        else if (field_count == 6)
        {
          values[i].fonction[k] = buff[j];
        }
        k++;
      }
      j++;
    }
    i++;
  }
  fclose(fp);
  return values;
}

void viderBuffer(void)
{
  int c;
  while ((c = getchar()) != EOF && c != '\n')
    ;
}

int savelefichier(personne *pelo)
{
  int i = 0;
  FILE *fw = fopen("annuaire5000.csv", "w");
  if (!fw)
  {
    printf("error fichier");
    return 1;
  }
  for (i = 0; i < nbligne; i++)
  {
    fprintf(fw, "%s,%s,%s,%s,%s,%s,%s\n", pelo[i].prenom, pelo[i].nom,
            pelo[i].ville, pelo[i].codepost, pelo[i].numtel, pelo[i].email,
            pelo[i].fonction);
  }
  fclose(fw);
  return 0;
}

int afficher(personne *pelo, personne peloachercher)
{
  int nblignepossible = 0, conteur = 1;
  for (conteur = 0; conteur < 180; conteur++)
    printf("_");
  printf("\n");
  printf("|%7s|%24s|%27s|%23s|%11s|%17s|%47s|%17s|\n", "ligne", "prenom", "nom",
         "ville", "code postal", "téléphone", "email", "fonction");
  for (conteur = 0; conteur < 180; conteur++)
  {
    if (conteur == 0 || conteur == 179 || conteur == 8 || conteur == 33 ||
        conteur == 61 || conteur == 85 || conteur == 97 || conteur == 113 ||
        conteur == 161)
      printf("|");
    else
      printf("_");
  }
  printf("\n");
  for (int i = 0; i < nbligne; i++)
  {
    if ((strstr(pelo[i].prenom, peloachercher.prenom) != NULL ||
         peloachercher.prenom[0] == '\0') &&
        (strstr(pelo[i].nom, peloachercher.nom) != NULL ||
         peloachercher.nom[0] == '\0') &&
        (strstr(pelo[i].ville, peloachercher.ville) != NULL ||
         peloachercher.ville[0] == '\0') &&
        (strstr(pelo[i].codepost, peloachercher.codepost) != NULL ||
         peloachercher.codepost[0] == '\0') &&
        (strstr(pelo[i].numtel, peloachercher.numtel) != NULL ||
         peloachercher.numtel[0] == '\0') &&
        (strstr(pelo[i].email, peloachercher.email) != NULL ||
         peloachercher.email[0] == '\0') &&
        (strstr(pelo[i].fonction, peloachercher.fonction) != NULL ||
         peloachercher.fonction[0] == '\0'))
    {
      printf("|%7d|%24s|%27s|%23s|%11s|%15s|%47s|%17s|", i, pelo[i].prenom,
             pelo[i].nom, pelo[i].ville, pelo[i].codepost, pelo[i].numtel,
             pelo[i].email, pelo[i].fonction);
      nblignepossible++;
      printf("\n");
    }
  }
  for (conteur = 0; conteur < 180; conteur++)
  {
    if (conteur == 0 || conteur == 179 || conteur == 8 || conteur == 33 ||
        conteur == 61 || conteur == 85 || conteur == 97 || conteur == 113 ||
        conteur == 161)
      printf("|");
    else
      printf("_");
  }
  printf("\n");
  if (!(nblignepossible))
  {
    printf("Aucun résultat\n");
    return -1;
  }
  else
    return 0;
}

personne entrer_champs_personne(void)
{
  int i, j, boole = 1, c;
  char temp;
  personne personnetemp;
  printf("Prenom : ");
  fgets(personnetemp.prenom, STRIN, stdin);
  personnetemp.prenom[strlen(personnetemp.prenom) - 1] = '\0';
  if (personnetemp.prenom[0] < 123 && personnetemp.prenom[0] > 96)
    personnetemp.prenom[0] = personnetemp.prenom[0] - 32;
  for (i = 0; i < strlen(personnetemp.prenom); i++)
  {
    if (personnetemp.prenom[i] == '-' || personnetemp.prenom[i] == ' ')
      if (personnetemp.prenom[i + 1] < 123 && personnetemp.prenom[i + 1] > 96)
        personnetemp.prenom[i + 1] = personnetemp.prenom[i + 1] - 32;
  }

  printf("Nom : ");
  fgets(personnetemp.nom, STRIN, stdin);
  personnetemp.nom[strlen(personnetemp.nom) - 1] = '\0';
  if (personnetemp.nom[0] < 123 && personnetemp.nom[0] > 96)
    personnetemp.nom[0] = personnetemp.nom[0] - 32;
  for (i = 0; i < strlen(personnetemp.nom); i++)
    if (personnetemp.nom[i] == '-' || personnetemp.nom[i] == ' ')
      if (personnetemp.nom[i + 1] < 123 && personnetemp.nom[i + 1] > 96)
        personnetemp.nom[i + 1] = personnetemp.nom[i + 1] - 32;

  printf("Ville : ");
  fgets(personnetemp.ville, STRIN, stdin);
  personnetemp.ville[strlen(personnetemp.ville) - 1] = '\0';
  for (i = 0; i < strlen(personnetemp.ville); i++)
    if (personnetemp.ville[i] < 123 && personnetemp.ville[i] > 96)
      personnetemp.ville[i] = personnetemp.ville[i] - 32;

  do
  {
    i = 0;
    printf("Code Postal : ");
    fgets(personnetemp.codepost, VSSTRIN, stdin);
    while (personnetemp.codepost[i] != '\n')
      i++;
    personnetemp.codepost[i] = '\0';
    boole = 1;
    if (personnetemp.codepost[0] != '\0')
    {
      for (i = 0; i < 5; i++)
      {
        if (personnetemp.codepost[i] < 47 || personnetemp.codepost[i] > 57)
        {
          boole = 0;
          personnetemp.codepost[0] = '\0';
          break;
        }
        else
        {
          boole = 1;
        }
      }
    }
  } while (!boole);
  printf("Numéro de téléphone : ");
  fgets(personnetemp.numtel, SSTRIN, stdin);
  personnetemp.numtel[strlen(personnetemp.numtel) - 1] = '\0';
  if (personnetemp.numtel[0] != 0)
  {
    for (i = 0; i < strlen(personnetemp.numtel); i++)
    {
      if (((i - 2) % 3) == 0 && personnetemp.numtel[i] != '.')
      {
        for (j = 14; j > i; j--)
          personnetemp.numtel[j] = personnetemp.numtel[j - 1];
        personnetemp.numtel[i] = '.';
      }
    }
  }
  printf("E-mail : ");
  fgets(personnetemp.email, LSTRIN, stdin);
  personnetemp.email[strlen(personnetemp.email) - 1] = '\0';
  printf("Fonction : ");
  fgets(personnetemp.fonction, STRIN, stdin);
  personnetemp.fonction[strlen(personnetemp.fonction) - 1] = '\0';
  return personnetemp;
}

int filtre(personne *pelo)
{
  personne peloachercher;
  printf("Insérer du texte pour filtrer et appuyer sur entrer, appuyer juste "
         "sur entrer pour ne pas mettre de filtre\n");
  peloachercher = entrer_champs_personne();
  return afficher(pelo, peloachercher);
}

int selecligne(personne *pelo)
{
  int numligne_a_selec = -2;
  while (numligne_a_selec == -2)
  {
    numligne_a_selec = filtre(pelo);
    if (numligne_a_selec == -1)
    {
      do
      {
        printf(
            "-2 pour recommencer la recherche, -1 pour finir la recherche\n");
        scanf("%d", &numligne_a_selec);
        viderBuffer();
        if (numligne_a_selec != -2 && numligne_a_selec != -1)
          printf("erreur nombre incorrect");
      } while (numligne_a_selec != -2 && numligne_a_selec != -1);
    }
    else
    {
      do
      {
        printf("donner le numméro de ligne pour la selectionner, -2 pour "
               "recommencer, -1 pour finir la recherche\n");
        scanf("%d", &numligne_a_selec);
        viderBuffer();
        if (numligne_a_selec > nbligne)
          printf("erreur ligne hors champs");
        if ((numligne_a_selec != -2) && (numligne_a_selec != -1) &&
            (numligne_a_selec < 0))
          printf("erreur nombre incorrect");
      } while ((numligne_a_selec != -2 && numligne_a_selec != -1 &&
                numligne_a_selec < 0) ||
               numligne_a_selec > nbligne);
    }
  }

  return numligne_a_selec;
}

void quicksort(personne *pelo, int first, int last, int type_info)
{
  int i, j, pivot;
  personne temp;
  switch (type_info)
  {
  case 0:
    if (first < last)
    {
      pivot = first;
      i = first;
      j = last;

      while (i < j)
      {
        while ((strcmp(pelo[i].prenom, pelo[pivot].prenom) <= 0) && i < last)
          i++;
        while (strcmp(pelo[j].prenom, pelo[pivot].prenom) > 0)
          j--;
        if (i < j)
        {
          temp = pelo[i];
          pelo[i] = pelo[j];
          pelo[j] = temp;
        }
      }

      temp = pelo[pivot];
      pelo[pivot] = pelo[j];
      pelo[j] = temp;
      quicksort(pelo, first, j - 1, 0);
      quicksort(pelo, j + 1, last, 0);
    }
    break;
  case 1:
    if (first < last)
    {
      pivot = first;
      i = first;
      j = last;

      while (i < j)
      {
        while ((strcmp(pelo[i].nom, pelo[pivot].nom) <= 0) && i < last)
          i++;
        while (strcmp(pelo[j].nom, pelo[pivot].nom) > 0)
          j--;
        if (i < j)
        {
          temp = pelo[i];
          pelo[i] = pelo[j];
          pelo[j] = temp;
        }
      }

      temp = pelo[pivot];
      pelo[pivot] = pelo[j];
      pelo[j] = temp;
      quicksort(pelo, first, j - 1, 0);
      quicksort(pelo, j + 1, last, 0);
    }
    break;
  case 2:
    if (first < last)
    {
      pivot = first;
      i = first;
      j = last;

      while (i < j)
      {
        while ((strcmp(pelo[i].ville, pelo[pivot].ville) <= 0) && i < last)
          i++;
        while (strcmp(pelo[j].ville, pelo[pivot].ville) > 0)
          j--;
        if (i < j)
        {
          temp = pelo[i];
          pelo[i] = pelo[j];
          pelo[j] = temp;
        }
      }

      temp = pelo[pivot];
      pelo[pivot] = pelo[j];
      pelo[j] = temp;
      quicksort(pelo, first, j - 1, 0);
      quicksort(pelo, j + 1, last, 0);
    }
    break;
  case 3:
    if (first < last)
    {
      pivot = first;
      i = first;
      j = last;

      while (i < j)
      {
        while ((strcmp(pelo[i].codepost, pelo[pivot].codepost) <= 0) &&
               i < last)
          i++;
        while (strcmp(pelo[j].codepost, pelo[pivot].codepost) > 0)
          j--;
        if (i < j)
        {
          temp = pelo[i];
          pelo[i] = pelo[j];
          pelo[j] = temp;
        }
      }

      temp = pelo[pivot];
      pelo[pivot] = pelo[j];
      pelo[j] = temp;
      quicksort(pelo, first, j - 1, 0);
      quicksort(pelo, j + 1, last, 0);
    }
    break;
  case 4:
    if (first < last)
    {
      pivot = first;
      i = first;
      j = last;

      while (i < j)
      {
        while ((strcmp(pelo[i].numtel, pelo[pivot].numtel) <= 0) && i < last)
          i++;
        while (strcmp(pelo[j].numtel, pelo[pivot].numtel) > 0)
          j--;
        if (i < j)
        {
          temp = pelo[i];
          pelo[i] = pelo[j];
          pelo[j] = temp;
        }
      }

      temp = pelo[pivot];
      pelo[pivot] = pelo[j];
      pelo[j] = temp;
      quicksort(pelo, first, j - 1, 0);
      quicksort(pelo, j + 1, last, 0);
    }
    break;
  case 5:
    if (first < last)
    {
      pivot = first;
      i = first;
      j = last;

      while (i < j)
      {
        while ((strcmp(pelo[i].email, pelo[pivot].email) <= 0) && i < last)
          i++;
        while (strcmp(pelo[j].email, pelo[pivot].email) > 0)
          j--;
        if (i < j)
        {
          temp = pelo[i];
          pelo[i] = pelo[j];
          pelo[j] = temp;
        }
      }

      temp = pelo[pivot];
      pelo[pivot] = pelo[j];
      pelo[j] = temp;
      quicksort(pelo, first, j - 1, 0);
      quicksort(pelo, j + 1, last, 0);
    }
    break;
  case 6:
    if (first < last)
    {
      pivot = first;
      i = first;
      j = last;

      while (i < j)
      {
        while ((strcmp(pelo[i].fonction, pelo[pivot].fonction) <= 0) &&
               i < last)
          i++;
        while (strcmp(pelo[j].fonction, pelo[pivot].fonction) > 0)
          j--;
        if (i < j)
        {
          temp = pelo[i];
          pelo[i] = pelo[j];
          pelo[j] = temp;
        }
      }

      temp = pelo[pivot];
      pelo[pivot] = pelo[j];
      pelo[j] = temp;
      quicksort(pelo, first, j - 1, 0);
      quicksort(pelo, j + 1, last, 0);
    }
    break;
  }
}

void modif_personne(personne *pelo)
{
  int ligne_selec;
  ligne_selec = selecligne(pelo);
  if (ligne_selec == -1)
    exit(-1);
  personne personne_a_modifier = entrer_champs_personne();
  if (personne_a_modifier.prenom[0] != '\0')
    strcpy(pelo[ligne_selec].prenom, personne_a_modifier.prenom);
  if (personne_a_modifier.nom[0] != '\0')
    strcpy(pelo[ligne_selec].nom, personne_a_modifier.nom);
  if (personne_a_modifier.ville[0] != '\0')
    strcpy(pelo[ligne_selec].ville, personne_a_modifier.ville);
  if (personne_a_modifier.codepost[0] != '\0')
    strcpy(pelo[ligne_selec].codepost, personne_a_modifier.codepost);
  if (personne_a_modifier.numtel[0] != '\0')
    strcpy(pelo[ligne_selec].numtel, personne_a_modifier.numtel);
  if (personne_a_modifier.email[0] != '\0')
    strcpy(pelo[ligne_selec].email, personne_a_modifier.email);
  if (personne_a_modifier.fonction[0] != '\0')
    strcpy(pelo[ligne_selec].fonction, personne_a_modifier.fonction);
  printf("La ligne à été modifié\n");
}

personne *ajout_personne(personne *ligne)
{
  personne personne_a_ajouter;
  printf("Saisisser les information et appuyer sur entrer, appuyer juste sur "
         "entrer pour ne pas mettre d'information\n");
  personne_a_ajouter = entrer_champs_personne();
  ligne = realloc(ligne, sizeof(personne) * nbligne + sizeof(personne));
  if (!ligne)
  {
    printf("Ram de ses morts");
    exit(-1);
  }
  nbligne++;
  ligne[nbligne - 1] = personne_a_ajouter;
  return ligne;
}

personne *suppression_personne(personne *ligne)
{
  int ligne_selec, i;
  printf("Saisisser les information de la personne à supprimer et appuyer sur "
         "entrer, appuyer juste sur entrer pour ne pas mettre d'information\n");
  ligne_selec = selecligne(ligne);
  if (ligne_selec == -1)
  {
    printf("aucune ligne selectionné");
    return ligne;
  }
  printf("Ram de ses morts");
  for (i = ligne_selec; i < nbligne; i++)
  {
    ligne[i] = ligne[i + 1];
  }
  ligne = realloc(ligne, sizeof(personne) * nbligne - sizeof(personne));
  if (!ligne)
  {
    printf("Ram de ses morts");
    exit(-1);
  }
  nbligne--;
  return ligne;
}

int main(void)
{
  personne *annuaire = NULL;
  int ligne, etat, cpasfini = 1, etatfichier = 0, choix;
  char nomfichier[100];
  while (cpasfini)
  {
    if (etatfichier == 0)
    {
      printf("Aucun fichier n'est ouvert, 1 pour ouvrir un fichier 2 pour "
             "fermer :\n");
      scanf("%d", &choix);
      system("clear");
      viderBuffer();
      if (choix == 1)
      {
        do
        {
          printf("rentrer le nom du fichier à ouvrir :\n");
          fgets(nomfichier, 100, stdin);
          system("clear");
          nomfichier[strlen(nomfichier) - 1] = '\0';
          annuaire = ouvrir_fichier(nomfichier);
        } while (annuaire == NULL);
        etatfichier = 1;
      }
      else
      {
        cpasfini = 0;
      }
    }
    else
    {
      if (etatfichier == 2)
        printf("Le fichier n'est pas sauvegarder\n");
      printf("1) Ajouter un client\n");
      printf("2) Modifier un client\n");
      printf("3) Supprimer un client\n");
      printf("4) Afficer tout les clients\n");
      printf("5) Filtrer et afficher les clients\n");
      printf("6) Sauvegarder le fichier\n");
      printf("7) Trier le fichier\n");
      printf("8) Fermer le fichier\n");
      scanf("%d", &choix);
      viderBuffer();
      system("clear");

      switch (choix)
      {
      case 1:
        annuaire = ajout_personne(annuaire);
        etatfichier = 2;
        break;
      case 2:
        modif_personne(annuaire);
        etatfichier = 2;
        break;
      case 3:
        annuaire = suppression_personne(annuaire);
        etatfichier = 2;
        break;
      case 4:
        afficher(annuaire, defaultpersonne);
        break;
      case 5:
        afficher(annuaire, entrer_champs_personne());
        break;
      case 6:
        savelefichier(annuaire);
        etatfichier = 1;
        break;
      case 7:
        printf("0 : prenom | 1 : nom | 2 : ville | 3 : code-postal | 4 : numéro | 5 : email | 6 : fonction ");
        scanf("%d", &choix);
        viderBuffer();
        quicksort(annuaire, 0, nbligne - 1, choix);
        break;
      case 8:
        etatfichier = 0;
        free(annuaire);
        break;
      default:
        printf("nombre incorecte");
        break;
      }
    }
  }
  return 0;
}
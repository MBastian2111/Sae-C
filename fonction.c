#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonction.h"

 // Création d'une personne vide pour pouvoir une valeur par défaut sur certainnes fonction


void clrscr() //https://stackoverflow.com/a/33992073 /Bastian Mounier
{
    system("@cls||clear");
}

personne *ouvrir_fichier(char *nom_fichier, long *nbligne) //Jérémie Vernay
{ // Création d'une fonction qui à pour // butd'ouvrir perser un fichier csv
  long j = 0, k = 0, field_count = 0, i = 0; //c sert à stocker les lettre pour compter le nombre de ligne, j correspond à l'avancement dans le buffer de la ligne, k correspond à l'emplacement d'écriture dans le tableau de structure, field_count est le numéro de variable qu'on écri(nom, prénom), i correspond au numéro de ligne
  int c;
  char buff[1024]; // cette variable stocke la une ligne du fichier csv

  clock_t start = clock();

  FILE *fp = fopen(nom_fichier, "r"); // ouvre le fichier donner par l'utilisateur en lecture

  if (!fp) //test si le pointeur du fichier est égal à null, si oui alors il y a eu un problème à l'ouverture
  {
    printf("error fichier\n");
    return NULL;
  }
  for (c = getc(fp); c != EOF; c = getc(fp)) //cet boucle for compte le nombre d'\n pour connaitre le nombre de ligne
  {
    if (c == '\n') 
      *nbligne = *nbligne + 1;
  }
  printf("nbligne : %ld \n", *nbligne); // affiche pour l'utilisateur le nombre de ligne chargé
  personne *values = NULL; //créé un pointeur null pour le tableau de sctruct
  values = malloc(sizeof(personne) * *nbligne); //allocation de la mémoire pour le tableau de struct pour ouvrir chargé et parser le fichier
  if (values == NULL) // vérifie si l'allocation de la mémoire à fonctionner
  {
    printf("Problème de mémoire ram");
    exit(1);
  }
  fseek(fp, 0, SEEK_SET); //remet le pointeur du qui lis le fichier au début

  while (fgets(buff, 1024, fp)) //cet boucle charge le fichier ligne par ligne de 1024 caractère max
  {
    field_count = 0; 
    j = 0;
    k = 0;
    while (buff[j] != '\n' && buff[j] != '\r' && buff[j] != EOF) // tant que ce n'est pas la fin du fichier ou de la ligne, on continue de remplir la même ligne
    {
      if (buff[j] == ',') //si c'est une virlgule on passe à l"élèment suivant et on met un \0 pour finir la string
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
      else //sinon il place le charactère à l'emplacement j du buffer pour le mettre dans l'emplacement j du champ de la ligne i
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
        k++; //incrémente de 1 l'emplacement d'écriture dans la structure
      }
      j++; //incrémente de 1 l'emplacement dans le buffer
    }
    i++; //incrémente de 1 l'emplacement de ligne
  }
  fclose(fp); //ferme le fichier pour libérer la mémoir
  clock_t end = clock();

  float seconds = (float)(end - start) / CLOCKS_PER_SEC;
  printf("tps : %fs\n ",seconds);
  return values; //retourne le pointeur du talbeau
}

void viderBuffer(void) //cette fonction permet de vider le buffer de stdin (généralement après un scanf) /Bastian Mounier
{
  long c;
  while ((c = getchar()) != EOF && c != '\n') //la boucle récupère des charactère tant qu'il différent d'\n ou qu'il est vide
    ;
}

long savelefichier(personne *tab, long *nbligne) //cette fonction permet de sauvegarder les modification dans le fichier /Jérémie Vernay
{
  clock_t start = clock();
  long i = 0; //initialisation d'une variable pour une boucle for
  FILE *fw = fopen("annuaire5000.csv", "w"); //on ouvre le fichier en écriture
  if (!fw) //test si on à pu ouvrir le fichier
  {
    printf("error fichier");
    return 1;
  }
  for (i = 0; i < *nbligne; i++) //une boucle qui vas print dans le fichier chaque ligne du tableau de struct
  {
    fprintf(fw, "%s,%s,%s,%s,%s,%s,%s\n", tab[i].prenom, tab[i].nom,
            tab[i].ville, tab[i].codepost, tab[i].numtel, tab[i].email,
            tab[i].fonction);
  }
  fclose(fw); //ferme le fichier
  clock_t end = clock();
  float seconds = (float)(end - start) / CLOCKS_PER_SEC;
  printf("%f s", seconds);
  return 0;
}

long afficher(personne *tab, personne peloachercher, long *nbligne) //cette fonction permet d'afficher un tableau et de le filtrer avec une structure personnne, il existe une struct defaut qui permet de ne pas mettre de filtre /Jérémie Vernay
{
  clock_t start = clock();
  long nblignepossible = 0, conteur = 1; //variable utilisé pour l'affichage
  for (conteur = 0; conteur < 180; conteur++) //les deux boucle for affiche le conteneur du tableau grâce au charactère ascii
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
  for (long i = 0; i < *nbligne; i++) //cette boucle vérifie pour chaque ligne si tout les champ donné par l'utilisateur corresponde, 
  {
    if ((strstr(tab[i].prenom, peloachercher.prenom) != NULL || //si l'utilisateur n'applique pas de filtre sur un champ alors le "=='\0'" permet de ne pas filtrer sur le champ
         peloachercher.prenom[0] == '\0') &&
        (strstr(tab[i].nom, peloachercher.nom) != NULL ||
         peloachercher.nom[0] == '\0') &&
        (strstr(tab[i].ville, peloachercher.ville) != NULL ||
         peloachercher.ville[0] == '\0') &&
        (strstr(tab[i].codepost, peloachercher.codepost) != NULL ||
         peloachercher.codepost[0] == '\0') &&
        (strstr(tab[i].numtel, peloachercher.numtel) != NULL ||
         peloachercher.numtel[0] == '\0') &&
        (strstr(tab[i].email, peloachercher.email) != NULL ||
         peloachercher.email[0] == '\0') &&
        (strstr(tab[i].fonction, peloachercher.fonction) != NULL ||
         peloachercher.fonction[0] == '\0'))
    {
      printf("|%7ld|%24s|%27s|%23s|%11s|%15s|%47s|%17s|", i, tab[i].prenom, //si les critères coresponde alors la ligne du tableau est affiché
             tab[i].nom, tab[i].ville, tab[i].codepost, tab[i].numtel,
             tab[i].email, tab[i].fonction);
      nblignepossible++; //permet de savoir si il y a un résultat
      printf("\n");
    }
  }
  for (conteur = 0; conteur < 180; conteur++) //affiche le bas du contour du tableau
  {
    if (conteur == 0 || conteur == 179 || conteur == 8 || conteur == 33 ||
        conteur == 61 || conteur == 85 || conteur == 97 || conteur == 113 ||
        conteur == 161)
      printf("|");
    else
      printf("_");
  }
  printf("\n");
  if (!(nblignepossible)) //permet en fonction de si il y a un résultat ou nom de renvoyer un code différent
  {
    printf("Aucun résultat\n");
    return -1;
  }
  else
    return 0;
  clock_t end = clock();
  float seconds = (float)(end - start) / CLOCKS_PER_SEC;
  printf("%f s", seconds);
}

personne entrer_champs_personne(void) //cette fonction permet de remplire une variable de structure personne de façon robuste /Jérémie Vernay
{
  long i, j, boole = 1, c; 
  personne personnetemp;
  printf("Prenom : ");
  fgets(personnetemp.prenom, STRIN, stdin);
  personnetemp.prenom[strlen(personnetemp.prenom) - 1] = '\0';
  if (personnetemp.prenom[0] < 123 && personnetemp.prenom[0] > 96) //met la première lettre en maj si elle ne l'est pas
    personnetemp.prenom[0] = personnetemp.prenom[0] - 32; 
  for (i = 0; i < strlen(personnetemp.prenom); i++) //si il y a un espace dans la string la prochaine lettre est mise en maj si elle ne l'est pas
  {
    if (personnetemp.prenom[i] == '-' || personnetemp.prenom[i] == ' ')
      if (personnetemp.prenom[i + 1] < 123 && personnetemp.prenom[i + 1] > 96)
        personnetemp.prenom[i + 1] = personnetemp.prenom[i + 1] - 32;
  }

  printf("Nom : ");
  fgets(personnetemp.nom, STRIN, stdin);
  personnetemp.nom[strlen(personnetemp.nom) - 1] = '\0';
  if (personnetemp.nom[0] < 123 && personnetemp.nom[0] > 96) //met la première lettre en maj si elle ne l'est pas
    personnetemp.nom[0] = personnetemp.nom[0] - 32;
  for (i = 0; i < strlen(personnetemp.nom); i++) //si il y a un espace dans la string la prochaine lettre est mise en maj si elle ne l'est pas
    if (personnetemp.nom[i] == '-' || personnetemp.nom[i] == ' ')
      if (personnetemp.nom[i + 1] < 123 && personnetemp.nom[i + 1] > 96)
        personnetemp.nom[i + 1] = personnetemp.nom[i + 1] - 32;

  printf("Ville : ");
  fgets(personnetemp.ville, STRIN, stdin);
  personnetemp.ville[strlen(personnetemp.ville) - 1] = '\0';
  for (i = 0; i < strlen(personnetemp.ville); i++) //met toute les lettres en maj
    if (personnetemp.ville[i] < 123 && personnetemp.ville[i] > 96)
      personnetemp.ville[i] = personnetemp.ville[i] - 32;

  do
  {
    i = 0;
    printf("Code Postal : ");
    fgets(personnetemp.codepost, VSSTRIN, stdin); //Le programme va vérifier si c'est un code postal, il doit être complet
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
  printf("Numéro de téléphone : "); //Cette partie permet de mettre les '.' dans la string et déplacer les caractères
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
  return personnetemp; //le programme renvoie la variable comptenant les différents champs
}

long filtre(personne *tab, long *nbligne) //cette fonction permet de lancer la fonction affichage avec un filtre /Jérémie Vernay
{
  personne peloachercher;
  printf("Insérer du texte pour filtrer et appuyer sur entrer, appuyer juste "
         "sur entrer pour ne pas mettre de filtre\n");
  peloachercher = entrer_champs_personne(); //prend une variable personnne
  return afficher(tab, peloachercher, nbligne); //quelle donne ensuite à la fonction afficher
}

long selecligne(personne *tab, long *nbligne) //cette fonction permet à l'utilisateur de sélectionner une ligne /Jérémie Vernay
{
  long numligne_a_selec = -2; 
  while (numligne_a_selec == -2) //tant que l'utilisateur n'annule pas ou ne valide pas une ligne alors il continue faire la recherche d'une ligne
  {
    numligne_a_selec = filtre(tab, nbligne); // Le programme affiche le tableau avec un trie pour que l'utilisateur sache quelle ligne selectionner
    if (numligne_a_selec == -1)
    {
      do
      {
        printf("-2 pour recommencer la recherche, -1 pour finir la recherche\n");
        scanf("%ld", &numligne_a_selec);
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
        scanf("%ld", &numligne_a_selec);
        viderBuffer();
        if (numligne_a_selec > *nbligne)
          printf("erreur ligne hors champs");
        if ((numligne_a_selec != -2) && (numligne_a_selec != -1) &&
            (numligne_a_selec < 0))
          printf("erreur nombre incorrect");
      } while ((numligne_a_selec != -2 && numligne_a_selec != -1 &&
                numligne_a_selec < 0) ||
               numligne_a_selec > *nbligne);
    }
  }

  return numligne_a_selec;
}

void quicksort(personne *tab, long first, long last, int type_info) //fonction de tri rapide trouver sur internet(https://waytolearnx.com/2019/08/tri-rapide-en-c.html) et adapteur pour pouvoir trier sur n'importe quel champ /Jérémie Vernay
{
  long i, j, pivot;
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
        while ((strcmp(tab[i].prenom, tab[pivot].prenom) <= 0) && i < last)
          i++;
        while (strcmp(tab[j].prenom, tab[pivot].prenom) > 0)
          j--;
        if (i < j)
        {
          temp = tab[i];
          tab[i] = tab[j];
          tab[j] = temp;
        }
      }

      temp = tab[pivot];
      tab[pivot] = tab[j];
      tab[j] = temp;
      quicksort(tab, first, j - 1, type_info);
      quicksort(tab, j + 1, last, type_info);
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
        while ((strcmp(tab[i].nom, tab[pivot].nom) <= 0) && i < last)
          i++;
        while (strcmp(tab[j].nom, tab[pivot].nom) > 0)
          j--;
        if (i < j)
        {
          temp = tab[i];
          tab[i] = tab[j];
          tab[j] = temp;
        }
      }

      temp = tab[pivot];
      tab[pivot] = tab[j];
      tab[j] = temp;
      quicksort(tab, first, j - 1, type_info);
      quicksort(tab, j + 1, last, type_info);
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
        while ((strcmp(tab[i].ville, tab[pivot].ville) <= 0) && i < last)
          i++;
        while (strcmp(tab[j].ville, tab[pivot].ville) > 0)
          j--;
        if (i < j)
        {
          temp = tab[i];
          tab[i] = tab[j];
          tab[j] = temp;
        }
      }

      temp = tab[pivot];
      tab[pivot] = tab[j];
      tab[j] = temp;
      quicksort(tab, first, j - 1, type_info);
      quicksort(tab, j + 1, last, type_info);
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
        while ((strcmp(tab[i].codepost, tab[pivot].codepost) <= 0) &&
               i < last)
          i++;
        while (strcmp(tab[j].codepost, tab[pivot].codepost) > 0)
          j--;
        if (i < j)
        {
          temp = tab[i];
          tab[i] = tab[j];
          tab[j] = temp;
        }
      }

      temp = tab[pivot];
      tab[pivot] = tab[j];
      tab[j] = temp;
      quicksort(tab, first, j - 1, type_info);
      quicksort(tab, j + 1, last, type_info);
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
        while ((strcmp(tab[i].numtel, tab[pivot].numtel) <= 0) && i < last)
          i++;
        while (strcmp(tab[j].numtel, tab[pivot].numtel) > 0)
          j--;
        if (i < j)
        {
          temp = tab[i];
          tab[i] = tab[j];
          tab[j] = temp;
        }
      }

      temp = tab[pivot];
      tab[pivot] = tab[j];
      tab[j] = temp;
      quicksort(tab, first, j - 1, type_info);
      quicksort(tab, j + 1, last, type_info);
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
        while ((strcmp(tab[i].email, tab[pivot].email) <= 0) && i < last)
          i++;
        while (strcmp(tab[j].email, tab[pivot].email) > 0)
          j--;
        if (i < j)
        {
          temp = tab[i];
          tab[i] = tab[j];
          tab[j] = temp;
        }
      }

      temp = tab[pivot];
      tab[pivot] = tab[j];
      tab[j] = temp;
      quicksort(tab, first, j - 1, type_info);
      quicksort(tab, j + 1, last, type_info);
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
        while ((strcmp(tab[i].fonction, tab[pivot].fonction) <= 0) &&
               i < last)
          i++;
        while (strcmp(tab[j].fonction, tab[pivot].fonction) > 0)
          j--;
        if (i < j)
        {
          temp = tab[i];
          tab[i] = tab[j];
          tab[j] = temp;
        }
      }

      temp = tab[pivot];
      tab[pivot] = tab[j];
      tab[j] = temp;
      quicksort(tab, first, j - 1, type_info);
      quicksort(tab, j + 1, last, type_info);
    }
    break;
  }
}

void modif_personne(personne *tab,long *nbligne) //la fonction permet de modifier une ligne du tableau /Bastian Mounier
{
  long ligne_selec;
  ligne_selec = selecligne(tab, nbligne); //elle récupère le numéro de ligne à modifier
  if (ligne_selec == -1)
    exit(-1);
  personne personne_a_modifier = entrer_champs_personne(); //elle récupère les nouvelles infos avec la fonction entrer_champs_personne
  clock_t start = clock();
  if (personne_a_modifier.prenom[0] != '\0') //si l'utilisateur à rentrer une info alors il la copie dans dans le champ de la ligne selectionné
    strcpy(tab[ligne_selec].prenom, personne_a_modifier.prenom);
  if (personne_a_modifier.nom[0] != '\0')
    strcpy(tab[ligne_selec].nom, personne_a_modifier.nom);
  if (personne_a_modifier.ville[0] != '\0')
    strcpy(tab[ligne_selec].ville, personne_a_modifier.ville);
  if (personne_a_modifier.codepost[0] != '\0')
    strcpy(tab[ligne_selec].codepost, personne_a_modifier.codepost);
  if (personne_a_modifier.numtel[0] != '\0')
    strcpy(tab[ligne_selec].numtel, personne_a_modifier.numtel);
  if (personne_a_modifier.email[0] != '\0')
    strcpy(tab[ligne_selec].email, personne_a_modifier.email);
  if (personne_a_modifier.fonction[0] != '\0')
    strcpy(tab[ligne_selec].fonction, personne_a_modifier.fonction);
  printf("La ligne à été modifié\n");
  clock_t end = clock();
  float seconds = (float)(end - start) / CLOCKS_PER_SEC;
  printf("%f s", seconds);
}

personne *ajout_personne(personne *tab, long *nbligne) //cette fonction augmente la taille du tableau et rajoute des information sur la nouvelle ligne /Jérémie Vernay
{
  personne personne_a_ajouter;
  printf("Saisisser les information et appuyer sur entrer, appuyer juste sur "
         "entrer pour ne pas mettre d'information\n");
  personne_a_ajouter = entrer_champs_personne(); //on recupère les nouvelles info
  clock_t start = clock();
  tab = realloc(tab, sizeof(personne) * (*nbligne) + sizeof(personne)); //on réalloue de la mémoire pour la nouvelle ligne
  if (!tab)
  {
    printf("Ram de ses morts");
    exit(-1);
  }
  (*nbligne)++; //on augmente le nombre de ligne
  tab[*nbligne - 1] = personne_a_ajouter; // on place les info dans la nouvelle ligne
  clock_t end = clock();
  float seconds = (float)(end - start) / CLOCKS_PER_SEC;
  printf("%f s", seconds);
  return tab; //on retourne l'emplacement du tableau vu qu'il a été changé avec maloc
}

personne *suppression_personne(personne *tab, long *nbligne) //cette fonction diminue la taille du tableau et supprime une ligne /Jérémie Vernay
{
  long ligne_selec, i;
  printf("Saisisser les information de la personne à supprimer et appuyer sur "
         "entrer, appuyer juste sur entrer pour ne pas mettre d'information\n");
  ligne_selec = selecligne(tab, nbligne); //on selectionne une ligne
  clock_t start = clock();
  if (ligne_selec == -1)
  {
    printf("aucune ligne selectionné");
    return tab;
  }
  for (i = ligne_selec; i < *nbligne; i++) //on écrase la ligne en décalant toute les ligne
  {
    tab[i] = tab[i + 1];
  }
  tab = realloc(tab, sizeof(personne) * (*nbligne) - sizeof(personne)); //on réalloue l'espace pour le tableau mais avec une ligne de moins
  if (!tab)
  {
    exit(-1);
  }
  (*nbligne)--;
  clock_t end = clock();
  float seconds = (float)(end - start) / CLOCKS_PER_SEC;
  printf("%f s", seconds);
  return tab; // on renvoie l'adresse ddu tableau
}

void info_manquante(personne *tab,long *nbligne) //Jérémie Vernay
{
  clock_t start = clock();
  long i, nblignevide = 0, conteur = 1;
  for (conteur = 0; conteur < 180; conteur++) //les deux boucle for affiche le conteneur du tableau grâce au charactère ascii
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
    for (long i = 0; i < *nbligne; i++) //cette boucle vérifie pour chaque ligne si tout les champ donné par l'utilisateur corresponde, 
  {
    if (tab[i].prenom[0] == '\0' || tab[i].nom[0] == '\0' || tab[i].ville[0] == '\0' || tab[i].codepost[0] == '\0' || tab[i].numtel[0] == '\0' || tab[i].email[0] == '\0' || tab[i].fonction[0] == '\0')
    {
      printf("|%7ld|%24s|%27s|%23s|%11s|%15s|%47s|%17s|", i, tab[i].prenom, //si les critères coresponde alors la ligne du tableau est affiché
             tab[i].nom, tab[i].ville, tab[i].codepost, tab[i].numtel,
             tab[i].email, tab[i].fonction);
      nblignevide++; //permet de savoir si il y a un résultat
      printf("\n");
    }
  }
  for (conteur = 0; conteur < 180; conteur++) //affiche le bas du contour du tableau
  {
    if (conteur == 0 || conteur == 179 || conteur == 8 || conteur == 33 ||
        conteur == 61 || conteur == 85 || conteur == 97 || conteur == 113 ||
        conteur == 161)
      printf("|");
    else
      printf("_");
  }
  printf("\n");

  printf("Il y a %ld ligne avec des informations manquantes", nblignevide);
  clock_t end = clock();
  float seconds = (float)(end - start) / CLOCKS_PER_SEC;
  printf("%f s", seconds);
}

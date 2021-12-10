#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#define MAXCHAR 1000

int  nbligne=0;

struct personne // Création d'une structure personne pour stocker chaque lignes du fichier
{
    char prenom[50], nom[50], ville[50], numtel[16],email[50], fonction[50], codepost[10]; //création de string pour socker individuelement chaque info
};
typedef struct personne personne; // défini la structure personne comme un type

personne defaultpersonne = {'\0','\0','\0','\0','\0','\0','\0'}; //Création d'une personne vide pour pouvoir une valeur par défaut sur certainnes fonction

personne* ouvrir_fichier(void) //Création d'une fonction qui à pour but d'ouvrir perser un fichier csv
{
    int c, j=0, k=0, field_count = 0, i =0;
    char buff[1024];
    FILE *fp = fopen("annuaire5000.csv", "r");

    if(!fp)
    {
        printf("error fichier");
        return NULL;
    }
    for (c = getc(fp); c != EOF; c = getc(fp))
    {
        if (c == '\n') nbligne = nbligne + 1;
    }
    printf("nbligne : %d \n", nbligne);
    personne *values = NULL;
    values = malloc(sizeof(personne) * nbligne);
    if(values == NULL) 
    {
        printf("check ta ram poto");
        exit(1);
    }
    fseek(fp, 0, SEEK_SET);



    while (fgets(buff, 1024, fp)) 
    {
        field_count = 0;
        j=0;
        k=0;
        while(buff[j] != '\n' && buff[j] != EOF)
        {
            if (buff[j] == ',')
            {
                if(field_count == 0)
                {
                    values[i].prenom[k] = '\0';
                }
                else if(field_count == 1) 
                {
                    values[i].nom[k] = '\0';
                }
                else if(field_count == 2) 
                {
                    values[i].ville[k] = '\0';
                }
                else if(field_count == 3) 
                {
                    values[i].codepost[k] = '\0';
                }
                else if(field_count == 4) 
                { 
                    values[i].numtel[k] = '\0';
                }
                else if(field_count == 5) 
                {
                    values[i].email[k] = '\0';
                }
                else if(field_count == 6) 
                { 
                    values[i].fonction[k] = '\0'; 
                }
                k=0;
                field_count++; 
            }
            else {
                if(field_count == 0)
                {
                    values[i].prenom[k] = buff[j];
                }
                else if(field_count == 1) 
                {
                    values[i].nom[k] = buff[j]; 
                }
                else if(field_count == 2) 
                {
                    values[i].ville[k] = buff[j]; 
                }
                else if(field_count == 3) 
                {
                    values[i].codepost[k] = buff[j]; 
                }
                else if(field_count == 4) 
                {
                    values[i].numtel[k] = buff[j]; 
                }
                else if(field_count == 5) 
                {
                    values[i].email[k] = buff[j]; 
                }
                else if(field_count == 6) 
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
  while((c=getchar()) != EOF && c != '\n');
 
}

int savelefichier(personne *pelo)
{
    int i = 0;
    FILE *fw = fopen("annuaire5000.csv", "w");
    printf("test 8\n");
    if(!fw)
    {
        printf("error fichier");
        return 1;
    }
    printf("test 8\n");
    for(i = 0; i < nbligne; i++)
    {
        fprintf(fw, "%s,%s,%s,%s,%s,%s,%s\n", pelo[i].prenom, pelo[i].nom, pelo[i].ville, pelo[i].codepost, pelo[i].numtel,pelo[i].email,pelo[i].fonction);
    }
    fclose(fw);
    return 0;
}

int afficher(personne *pelo, personne peloachercher)
{
    int nblignepossible = 0;
    for(int i = 0; i<nbligne; i++)
    {
        if ((strstr(pelo[i].prenom, peloachercher.prenom) != NULL || peloachercher.prenom[0]=='\0') && (strstr(pelo[i].nom, peloachercher.nom) != NULL || peloachercher.nom[0]=='\0') && (strstr(pelo[i].ville, peloachercher.ville) != NULL || peloachercher.ville[0]=='\0') && (strstr(pelo[i].codepost, peloachercher.codepost) != NULL || peloachercher.codepost[0]=='\0') && (strstr(pelo[i].numtel, peloachercher.numtel) != NULL || peloachercher.numtel[0]=='\0') && (strstr(pelo[i].email, peloachercher.email) != NULL || peloachercher.email[0]=='\0') && (strstr(pelo[i].fonction, peloachercher.fonction) != NULL || peloachercher.fonction[0]=='\0'))
        {
            printf("ligne %d ==> Prénom : %s| Nom : %s|  Ville : %s| Code postal : %s| Téléphone : %s| Email : %s| Fonction : %s\n",i,pelo[i].prenom,pelo[i].nom, pelo[i].ville, pelo[i].codepost, pelo[i].numtel, pelo[i].email, pelo[i].fonction);
        nblignepossible++;
        }
    }
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
    personne personnetemp;
    printf("Prenom : ");
    fgets(personnetemp.prenom, 50, stdin);
    personnetemp.prenom[strlen(personnetemp.prenom) - 1] = '\0';
    printf("Nom : ");
    fgets(personnetemp.nom, 50, stdin);
    personnetemp.nom[strlen(personnetemp.nom) - 1] = '\0';
    printf("Ville : ");
    fgets(personnetemp.ville, 50, stdin);
    personnetemp.ville[strlen(personnetemp.ville) - 1] = '\0';
    printf("Code Postal : ");
    fgets(personnetemp.codepost, 10, stdin);
    personnetemp.codepost[strlen(personnetemp.codepost) - 1] = '\0';
    printf("Numéro de téléphone : ");
    fgets(personnetemp.numtel, 16, stdin);
    personnetemp.numtel[strlen(personnetemp.numtel) - 1] = '\0';
    printf("E-mail : ");
    fgets(personnetemp.email, 50, stdin);
    personnetemp.email[strlen(personnetemp.email) - 1] = '\0';
    printf("Fonction : ");
    fgets(personnetemp.fonction, 50, stdin);
    personnetemp.fonction[strlen(personnetemp.fonction) - 1] = '\0';
    return personnetemp;
 }

int filtre(personne *pelo)
{
    personne peloachercher;
    printf("Insérer du texte pour filtrer et appuyer sur entrer, appuyer juste sur entrer pour ne pas mettre de filtre\n");
    peloachercher=entrer_champs_personne();
    return afficher(pelo, peloachercher);
}

int selecligne(personne *pelo)
{
    int numligne_a_selec = -2;
    while (numligne_a_selec == -2) 
    {
        numligne_a_selec=filtre(pelo);
        if (numligne_a_selec == -1)
        {   
            do {
            printf("-2 pour recommencer la recherche, -1 pour finir la recherche\n");
            scanf("%d", &numligne_a_selec);
            if (numligne_a_selec != -2 && numligne_a_selec != -1)
                printf("erreur nombre incorrect");
            }while (numligne_a_selec != -2 && numligne_a_selec != -1);
        }
        else
        {
            do {
            printf("donner le numméro de ligne pour la selectionner, -2 pour recommencer, -1 pour finir la recherche\n");
            scanf("%d", &numligne_a_selec);
            viderBuffer();
            if (numligne_a_selec > nbligne)
                printf("erreur ligne hors champs");
            if ((numligne_a_selec != -2) && (numligne_a_selec != -1) && (numligne_a_selec<0))
                printf("erreur nombre incorrect");
            }while ((numligne_a_selec != -2 && numligne_a_selec != -1 && numligne_a_selec<0 ) || numligne_a_selec > nbligne);
        }

    }

    
    return numligne_a_selec;
}

void quicksort(personne *pelo,int first,int last)
{
   int i, j, pivot;
   personne temp;

   if(first<last){
      pivot=first;
      i=first;
      j=last;

      while(i<j){
         while((strcmp(pelo[i].numtel,pelo[pivot].numtel)<0)&&i<last)
            i++;
         while(strcmp(pelo[j].numtel,pelo[pivot].numtel) > 0)
            j--;
         if(i<j){
            temp=pelo[i];
            pelo[i]=pelo[j];
            pelo[j]=temp;
         }
      }

      temp=pelo[pivot];
      pelo[pivot]=pelo[j];
      pelo[j]=temp;
      quicksort(pelo,first,j-1);
      quicksort(pelo,j+1,last);

   }
}

void modif_personne(personne *pelo)
{
    int ligne_selec;
    ligne_selec=selecligne(pelo);
    if (ligne_selec == -1) 
        exit(-1);
    personne personne_a_modifier=entrer_champs_personne();
    if (personne_a_modifier.prenom[0] != '\0') strcpy(pelo[ligne_selec].prenom, personne_a_modifier.prenom);
    if (personne_a_modifier.nom[0] != '\0') strcpy(pelo[ligne_selec].nom, personne_a_modifier.nom);
    if (personne_a_modifier.ville[0] != '\0') strcpy(pelo[ligne_selec].ville, personne_a_modifier.ville);
    if (personne_a_modifier.codepost[0] != '\0') strcpy(pelo[ligne_selec].codepost, personne_a_modifier.codepost);
    if (personne_a_modifier.numtel[0] != '\0') strcpy(pelo[ligne_selec].numtel, personne_a_modifier.numtel);
    if (personne_a_modifier.email[0] != '\0') strcpy(pelo[ligne_selec].email, personne_a_modifier.email);
    if (personne_a_modifier.fonction[0] != '\0') strcpy(pelo[ligne_selec].fonction, personne_a_modifier.fonction);
    printf("La ligne à été modifié\n");
}

personne* ajout_personne(personne *ligne)
{
    personne personne_a_ajouter;
    printf("test 1\n");
    printf("Saisisser les information et appuyer sur entrer, appuyer juste sur entrer pour ne pas mettre d'information\n");
    printf("test 2\n");
    personne_a_ajouter=entrer_champs_personne();
    printf("test 3\n");
    ligne = realloc(ligne,sizeof(personne) * nbligne + sizeof(personne));
    printf("test 4\n");
    if(!ligne)
    {
        printf("error fichier");
        exit(-1);
    }
    printf("test 4\n");
    nbligne++;
    printf("test 5\n");
    ligne[nbligne-1]=personne_a_ajouter;
    return ligne;
    printf("test 6\n");
}
void suppression_personne(personne *ligne)
{
    personne personne_a_ajouter;
    printf("Saisisser les information et appuyer sur entrer, appuyer juste sur entrer pour ne pas mettre d'information\n");
    personne_a_ajouter=entrer_champs_personne();
    ligne = realloc(ligne,sizeof(personne) * nbligne + sizeof(personne));
    nbligne++;
    ligne[nbligne-1]=personne_a_ajouter;
}



int main(void)
{
    personne *pelo ;
    int ligne, test;
    pelo = ouvrir_fichier();
    quicksort(pelo, 0,nbligne-1);
    afficher(pelo,  defaultpersonne);
    pelo = ajout_personne(pelo);
    printf("test7 %s", pelo[nbligne-1].nom);
    savelefichier(pelo);
    return 0;
}
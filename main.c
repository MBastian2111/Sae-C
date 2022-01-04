#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#define STRIN 27
#define LSTRIN 47
#define SSTRIN 15
#define VSSTRIN 6

int  nbligne=0;

struct personne // Création d'une structure personne pour stocker chaque lignes du fichier
{
    char prenom[STRIN], nom[STRIN], ville[STRIN], numtel[SSTRIN],email[LSTRIN], fonction[STRIN], codepost[VSSTRIN]; //création de string pour stocker individuelement chaque info
};
typedef struct personne personne; // défini la structure personne comme un type

personne defaultpersonne = {'\0','\0','\0','\0','\0','\0','\0'}; //Création d'une personne vide pour pouvoir une valeur par défaut sur certainnes fonction

personne* ouvrir_fichier(char* nom_fichier) //Création d'une fonction qui à pour but d'ouvrir perser un fichier csv
{
    int c, j=0, k=0, field_count = 0, i =0;
    char buff[1024] ,t[10];
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
        while(buff[j] != '\n' && buff[j] != '\r' && buff[j] != EOF)
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
                    if (i == 4999)
                      t[k]= buff[j];
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

int estla(char ch2[] ,char ch1[])
{

    int count1 = 0, count2 = 0, i, j, flag;
    while (ch2[count1] != '\0')
        count1++;
    while (ch1[count2] != '\0')
        count2++;
    for (i = 0; i <= count1 - count2; i++)
    {
        for (j = i; j < i + count2; j++)
        {
            flag = 1;
            if (ch2[j] != ch1[j - i])
            {
                flag = 0;
                break;
            }
        }
        if (flag == 1)
            break;
    }
    if (flag == 1)
        return 1;
    else
        return 0;
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
    if(!fw)
    {
        printf("error fichier");
        return 1;
    }
    for(i = 0; i < nbligne; i++)
    {
        fprintf(fw, "%s,%s,%s,%s,%s,%s,%s\n", pelo[i].prenom, pelo[i].nom, pelo[i].ville, pelo[i].codepost, pelo[i].numtel,pelo[i].email,pelo[i].fonction);
    }
    fclose(fw);
    return 0;
}

int afficher(personne *pelo, personne peloachercher)
{
    int nblignepossible = 0, conteur = 1;
    for (conteur=0;conteur<180; conteur++)
        printf("_");
    printf("\n");
    printf("|%7s|%24s|%27s|%23s|%11s|%17s|%47s|%17s|\n", "ligne","prenom", "nom", "ville", "code postal", "téléphone", "email","fonction");
    for (conteur=0;conteur<180; conteur++)
    {
        if (conteur == 0 || conteur == 179 || conteur == 8 || conteur == 33 || conteur == 61 || conteur == 85 || conteur == 97 || conteur == 113 || conteur == 161)
            printf("|");
        else
            printf("_");
    }
    printf("\n");
    for(int i = 0; i<nbligne; i++)
    {
        if ((strstr(pelo[i].prenom, peloachercher.prenom) != NULL || peloachercher.prenom[0]=='\0') && (strstr(pelo[i].nom, peloachercher.nom) != NULL || peloachercher.nom[0]=='\0') && (strstr(pelo[i].ville, peloachercher.ville) != NULL || peloachercher.ville[0]=='\0') && (strstr(pelo[i].codepost, peloachercher.codepost) != NULL || peloachercher.codepost[0]=='\0') && (strstr(pelo[i].numtel, peloachercher.numtel) != NULL || peloachercher.numtel[0]=='\0') && (strstr(pelo[i].email, peloachercher.email) != NULL || peloachercher.email[0]=='\0') && (strstr(pelo[i].fonction, peloachercher.fonction) != NULL || peloachercher.fonction[0]=='\0'))
        {
            printf("|%7d|%24s|%27s|%23s|%11s|%15s|%47s|%17s|",i,pelo[i].prenom,pelo[i].nom, pelo[i].ville, pelo[i].codepost, pelo[i].numtel, pelo[i].email, pelo[i].fonction);
            nblignepossible++;
            printf("\n");
        }
    }
    for (conteur=0;conteur<180; conteur++)
    {
        if (conteur == 0 || conteur == 179 || conteur == 8 || conteur == 33 || conteur == 61 || conteur == 85 || conteur == 97 || conteur == 113 || conteur == 161)
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
    int i,j, boole = 1, c;
    char temp;
    personne personnetemp;
    printf("Prenom : ");
    fgets(personnetemp.prenom, STRIN, stdin);
    personnetemp.prenom[strlen(personnetemp.prenom) - 1] = '\0';
    if (personnetemp.prenom[0] < 123 &&  personnetemp.prenom[0] > 96)
        personnetemp.prenom[0] = personnetemp.prenom[0] - 32;
    for (i = 0; i< strlen(personnetemp.prenom); i++)
    {
        if (personnetemp.prenom[i]=='-')
            if (personnetemp.prenom[i+1] < 123 &&  personnetemp.prenom[i+1] > 96)
                personnetemp.prenom[i+1] = personnetemp.prenom[i+1] - 32;
    }

    printf("Nom : ");
    fgets(personnetemp.nom, STRIN, stdin);
    personnetemp.nom[strlen(personnetemp.nom) - 1] = '\0';
    if (personnetemp.nom[0] < 123 &&  personnetemp.nom[0] > 96)
        personnetemp.nom[0] = personnetemp.nom[0] - 32;
    for (i = 0; i< strlen(personnetemp.nom); i++)
        if (personnetemp.nom[i]=='-')
            if (personnetemp.nom[i+1] < 123 &&  personnetemp.nom[i+1] > 96)
                personnetemp.nom[i+1] = personnetemp.nom[i+1] - 32;

    printf("Ville : ");
    fgets(personnetemp.ville, STRIN, stdin);
    personnetemp.ville[strlen(personnetemp.ville) - 1] = '\0';
    for (i = 0; i< strlen(personnetemp.ville); i++)
        if (personnetemp.ville[i] < 123 &&  personnetemp.ville[i] > 96)
            personnetemp.ville[i] = personnetemp.ville[i] - 32;
    
    do 
    {
    i = 0;
    printf("Code Postal : ");
    fgets(personnetemp.codepost, VSSTRIN, stdin);
    while(personnetemp.codepost[i] != '\n')
        i++;
    personnetemp.codepost[i] = '\0';
    boole = 1;
    if(personnetemp.codepost[0]!='\0')
    {
        printf("%s", personnetemp.codepost);
        for(i = 0; i < 5; i++)
        { 
            if (personnetemp.codepost[i] < 47 || personnetemp.codepost[i] > 57)
            {
                boole =0;
                personnetemp.codepost[0]='\0';
                break;
            }
            else 
            {
                boole = 1;
            }
        }
        viderBuffer();
    }
    }while (!boole);
    printf("Numéro de téléphone : ");
    fgets(personnetemp.numtel, SSTRIN, stdin);
    personnetemp.numtel[strlen(personnetemp.numtel)-1] = '\0';
    if(personnetemp.numtel[0]!=0)
    {
        for ( i = 0 ; i<strlen(personnetemp.numtel); i++)
        {
            if( ((i-2) % 3) == 0 && personnetemp.numtel[i]!='.')
            {
                for( j = 14; j>i ; j--)
                    personnetemp.numtel[j] = personnetemp.numtel[j-1];
                personnetemp.numtel[i]='.';
                }
        }
    }
    printf("E-mail : ");
    fgets(personnetemp.email, LSTRIN, stdin);
    personnetemp.email[strlen(personnetemp.email) - 1] = '\0';
    printf("Fonction : ");
    fgets(personnetemp.fonction, 20, stdin);
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
            viderBuffer();
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
    printf("Saisisser les information et appuyer sur entrer, appuyer juste sur entrer pour ne pas mettre d'information\n");
    personne_a_ajouter=entrer_champs_personne();
    ligne = realloc(ligne,sizeof(personne) * nbligne + sizeof(personne));
    if(!ligne)
    {
        printf("Ram de ses morts");
        exit(-1);
    }
    nbligne++;
    ligne[nbligne-1]=personne_a_ajouter;
    return ligne;
}
personne* suppression_personne(personne *ligne)
{
    int ligne_selec, i;
    printf("Saisisser les information de la personne à supprimer et appuyer sur entrer, appuyer juste sur entrer pour ne pas mettre d'information\n");
    ligne_selec = selecligne(ligne);
    if (ligne_selec == -1)
    {
        printf("aucune ligne selectionné");
        return ligne;
    }
    printf("Ram de ses morts");
    for(i = ligne_selec ; i<nbligne ; i ++ )
        {
            ligne[i] = ligne[i+1];
        }
    ligne = realloc(ligne,sizeof(personne) * nbligne - sizeof(personne));
    if(!ligne)
    {
        printf("Ram de ses morts");
        exit(-1);
    }
    nbligne--;
    return ligne;
}



int main(void)
{
    personne *pelo ;
    int ligne, etat, i;
    pelo = ouvrir_fichier("test");
    printf("%s",pelo[4999].codepost);
    modif_personne(pelo);
    savelefichier(pelo);
    return 0;
}
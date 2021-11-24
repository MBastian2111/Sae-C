#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXCHAR 1000


struct personne // Création d'une structure personne pour stocker chaque lignes du fichier
{
    char prenom[50], nom[50], ville[50], numtel[16],email[50], fonction[50], codepost[10]; //création de string pour socker individuelement chaque info
};
typedef struct personne personne; // défini la structure personne comme un type
int  nbligne=0;


personne* ouvrir_fichier(void)
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

int savelefichier(personne values[])
{
    int i = 0;
    FILE *fp = fopen("annuaire5000.csv", "w");
    if(!fp)
    {
        printf("error fichier");
        return 1;
    }
    for(i = 0; i < nbligne; i++){
        fprintf(fp, "%s,%s,%s,%s,%s,%s,%s\n", values[i].prenom, values[i].nom, values[i].ville, values[i].codepost, values[i].numtel,values[i].email,values[i].fonction);
    }
    return 0;
}

int selecligne(personne *pelo)
{
    int numligne_a_selec, nblignepossible = 0;
    personne peloachercher;
    printf("Prenom : ");
    fgets(peloachercher.prenom, 50, stdin);
    peloachercher.prenom[strlen(peloachercher.prenom) - 1] = '\0';
    printf("Nom : ");
    fgets(peloachercher.nom, 50, stdin);
    peloachercher.nom[strlen(peloachercher.nom) - 1] = '\0';
    printf("Ville : ");
    fgets(peloachercher.ville, 50, stdin);
    peloachercher.ville[strlen(peloachercher.ville) - 1] = '\0';
    printf("Code Postal : ");
    fgets(peloachercher.codepost, 10, stdin);
    peloachercher.codepost[strlen(peloachercher.codepost) - 1] = '\0';
    printf("Numéro de téléphone : ");
    fgets(peloachercher.numtel, 16, stdin);
    peloachercher.numtel[strlen(peloachercher.numtel) - 1] = '\0';
    printf("E-mail : ");
    fgets(peloachercher.email, 50, stdin);
    peloachercher.email[strlen(peloachercher.email) - 1] = '\0';
    printf("Fonction : ");
    fgets(peloachercher.fonction, 50, stdin);
    peloachercher.fonction[strlen(peloachercher.fonction) - 1] = '\0';

    for(int i = 0; i<nbligne; i++)
    {
        if ((strstr(pelo[i].prenom, peloachercher.prenom) != NULL || peloachercher.prenom[0]=='\0') && (strstr(pelo[i].nom, peloachercher.nom) != NULL || peloachercher.nom[0]=='\0') && (strstr(pelo[i].ville, peloachercher.ville) != NULL || peloachercher.ville[0]=='\0') && (strstr(pelo[i].codepost, peloachercher.codepost) != NULL || peloachercher.codepost[0]=='\0') && (strstr(pelo[i].numtel, peloachercher.numtel) != NULL || peloachercher.numtel[0]=='\0') && (strstr(pelo[i].email, peloachercher.email) != NULL || peloachercher.email[0]=='\0') && (strstr(pelo[i].fonction, peloachercher.fonction) != NULL || peloachercher.fonction[0]=='\0'))
        {
            printf("ligne %d ==> Prénom : %s| Nom : %s|  Ville : %s| Code postal : %s| Téléphone : %s| Email : %s| Fonction : %s\n",i,pelo[i].prenom,pelo[i].nom, pelo[i].ville, pelo[i].codepost, pelo[i].numtel, pelo[i].email, pelo[i].fonction);
            nblignepossible ++;
        }
    }
    if (!(nblignepossible))
    {
        printf("Aucun résultat\n");
        return -1;
    }
    else {
        printf("selectionner une ligne avec son numéro : ");
        scanf("%d", &numligne_a_selec);
        printf("\n");
    }


    return numligne_a_selec;
}

void modif_ligne(personne *pelo)
{
    int modifier = selecligne;
    personne peloamodif;
    printf("Prénom : ");
    fgets(peloamodif.prenom, 50, stdin);
    peloamodif.prenom[strlen(peloamodif.prenom) - 1] = '\0';
    strcpy(pelo[modifier].prenom, peloamodif.prenom);

    printf("Nom : ");
    fgets(peloamodif.nom, 50, stdin);
    peloamodif.prenom[strlen(peloamodif.prenom) - 1] = '\0';
    strcpy(pelo[modifier].prenom, peloamodif.prenom);

    printf("Ville: ");
    fgets(peloamodif.ville, 50, stdin);
    peloamodif.prenom[strlen(peloamodif.prenom) - 1] = '\0';
    strcpy(pelo[modifier].prenom, peloamodif.prenom);

    printf("Code Postal: ");
    fgets(peloamodif.codepost, 50, stdin);
    peloamodif.prenom[strlen(peloamodif.prenom) - 1] = '\0';
    strcpy(pelo[modifier].prenom, peloamodif.prenom);

    printf("Numéro de téléphone : ");
    fgets(peloamodif.numtel, 50, stdin);
    peloamodif.prenom[strlen(peloamodif.prenom) - 1] = '\0';
    strcpy(pelo[modifier].prenom, peloamodif.prenom);

    printf("E-mail : ");
    fgets(peloamodif.email, 50, stdin);
    peloamodif.prenom[strlen(peloamodif.prenom) - 1] = '\0';
    strcpy(pelo[modifier].prenom, peloamodif.prenom);

    printf("Fonction : ");
    fgets(peloamodif.fonction, 50, stdin);
    peloamodif.prenom[strlen(peloamodif.prenom) - 1] = '\0';
    strcpy(pelo[modifier].prenom, peloamodif.prenom);
}


int main(void)
{
    personne *pelo ;
    int ligne, test;
    pelo = ouvrir_fichier();
    printf("%s", pelo[389].nom);
    strcpy(pelo[391].nom, "test");
    savelefichier(pelo);
    test = selecligne(pelo);
    printf("on a selec la ligne%d",test );
    return 0;
}

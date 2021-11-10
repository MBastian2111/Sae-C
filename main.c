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
                field_count++; 
                k=0;
            }
            else {
                if(field_count == 0)
                {
                    values[i].prenom[k] = buff[j]; 
                    values[i].prenom[k+1] = '\0';
                }
                else if(field_count == 1) 
                {
                    values[i].nom[k] = buff[j]; 
                    values[i].nom[k+1] = '\0';
                }
                else if(field_count == 2) 
                {
                    values[i].ville[k] = buff[j]; 
                    values[i].ville[k+1] = '\0';
                }
                else if(field_count == 3) 
                {
                    values[i].codepost[k] = buff[j]; 
                    values[i].codepost[k+1] = '\0';
                }
                else if(field_count == 4) 
                {
                    values[i].numtel[k] = buff[j]; 
                    values[i].numtel[k+1] = '\0';
                }
                else if(field_count == 5) 
                {
                    values[i].email[k] = buff[j]; 
                    values[i].email[k+1] = '\0';
                }
                else if(field_count == 6) 
                {
                    values[i].fonction[k] = buff[j]; 
                    values[i].fonction[k+1] = '\0'; 
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

int selecligne(void)
{
    printf("Nom : ");
    scanf("")
}


int main(void)
{
    personne *pelo ;
    int ligne;
    pelo = ouvrir_fichier();
    printf("%s", pelo[399].nom);
    strcpy(pelo[399].nom, "AHHHHHH");
    savelefichier(pelo);
    return 0;
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    char URL[50];
    int lungime;
    int nr_accesari;
    int checksum;
    char titlu[51];
    char *continut;
    char *continut_parsat;
    char *copie_paragraf;
} info_site;

typedef struct nume_site
{
    char name[100];
    info_site detalii_site;
} nume_site;

void parsare(nume_site *site , int n){
    int i;
    int j;
    int k = 0;

    for( i = 0; i < n; i++)
    {
        site[i].detalii_site.continut_parsat=malloc(2 * sizeof(char));
        site[i].detalii_site.copie_paragraf=malloc(2 * sizeof(char));
        char *pointer_titlu_tag1 = strstr( site[i].detalii_site.continut, "<title>");
       // printf("%s", site[i].detalii_site.continut);
        char *pointer_titlu_tag2 = strstr( site[i].detalii_site.continut, "</title>");
        int inceput_titlu = pointer_titlu_tag1 - site[i].detalii_site.continut + 7;
        int sfarsit_titlu = pointer_titlu_tag2 - site[i].detalii_site.continut;
         //printf("%s\n%s",pointer_titlu_tag1,pointer_titlu_tag2);
        k = 0;
        for( j = inceput_titlu; j < sfarsit_titlu; j++)
        {
            site[i].detalii_site.titlu[k] =site[i].detalii_site.continut[j];
            k++;
        }
        site[i].detalii_site.titlu[k] = '\0';
        k = 0;
        if( strstr( site[i].detalii_site.continut, "<p>") != NULL)
        {
            char *point_incep_paragraf   = strstr( site[i].detalii_site.continut, "<p>");
            char *point_sfarsit_paragraf = strstr( site[i].detalii_site.continut, "</p>");
            int inceput_paragraf         = point_incep_paragraf - site[i].detalii_site.continut + 3;
            int sfarsit_paragraf         = point_sfarsit_paragraf -site[i].detalii_site.continut;
            int dimensiune               = sfarsit_paragraf - inceput_paragraf + 1;

            site[i].detalii_site.continut_parsat = realloc( site[i].detalii_site.continut_parsat, (dimensiune + 1) * sizeof( char));
            site[i].detalii_site.copie_paragraf = realloc( site[i].detalii_site.copie_paragraf, (dimensiune + 3) * sizeof( char));
            site[i].detalii_site.copie_paragraf[0] = ' ';

            for ( j = inceput_paragraf; j < sfarsit_paragraf; j++)
            {
                site[i].detalii_site.continut_parsat[k] = site[i].detalii_site.continut[j];
                 if( site[i].detalii_site.continut[j] == '\n')
                {
                    site[i].detalii_site.copie_paragraf[k + 1] = ' ';
                }
                else
                {
                    site[i].detalii_site.copie_paragraf[k + 1] = site[i].detalii_site.continut[j];
                }
                k++;
            }
        site[i].detalii_site.continut_parsat[k] = '\0';
        site[i].detalii_site.copie_paragraf[k + 1] = ' ';
        site[i].detalii_site.copie_paragraf[k + 2] = '\0';
        k = 0;
        }

        if ( strstr( site[i].detalii_site.continut, ";\">") != NULL)
        {
            char *point_incep_paragraf   = strstr( site[i].detalii_site.continut, ";\">");
            char *point_sfarsit_paragraf = strstr( site[i].detalii_site.continut, "</p>");
            int inceput_paragraf         = point_incep_paragraf - site[i].detalii_site.continut + 3;
            int sfarsit_paragraf         = point_sfarsit_paragraf -site[i].detalii_site.continut;
            int dimensiune               = sfarsit_paragraf - inceput_paragraf + 1;

            site[i].detalii_site.continut_parsat = realloc( site[i].detalii_site.continut_parsat, dimensiune * sizeof( char));
            site[i].detalii_site.copie_paragraf = realloc( site[i].detalii_site.copie_paragraf, (dimensiune + 3) * sizeof( char));
            site[i].detalii_site.copie_paragraf[0] = ' ';

            for ( j = inceput_paragraf; j < sfarsit_paragraf; j++)
            {
                site[i].detalii_site.continut_parsat[k] = site[i].detalii_site.continut[j];
                if ( site[i].detalii_site.continut[j] == '\n')
                {
                    site[i].detalii_site.copie_paragraf[k + 1] = ' ';   
                }
                else
                {
                    site[i].detalii_site.copie_paragraf[k + 1] = site[i].detalii_site.continut[j];
                }
                
                k++;
            }
        site[i].detalii_site.continut_parsat[k] = '\0';
        site[i].detalii_site.copie_paragraf[k + 1] = ' ';
        site[i].detalii_site.copie_paragraf[k + 2] = '\0';
        k = 0;
        }
    //    printf("---->%s<-----\n",site[i].detalii_site.copie_paragraf);
    }


}

void citire(nume_site *site, int n)
{
    int i,k=0,nc=0,nl=3,x,cap=10,j=0;
    int dim_irelevanta=0;
    FILE *fp;
    char caracter;
    char s[200];

    for ( i = 0; i < n; i++ )
    {
        fp=fopen(site[i].name, "r");
        fscanf(fp,"%s %d %d %d",site[i].detalii_site.URL,&site[i].detalii_site.lungime,&site[i].detalii_site.nr_accesari,&site[i].detalii_site.checksum);
        char enter;
        fscanf(fp,"%c",&enter);
        int lung_cont =  site[i].detalii_site.lungime;
        site[i].detalii_site.continut = (char *)malloc( lung_cont * sizeof(char));

        for ( j = 0; j < lung_cont ; j++ )
        {
            fscanf(fp, "%c",&site[i].detalii_site.continut[j]);
            if( site[i].detalii_site.continut[j] == '\n')
            {
                lung_cont++;
                site[i].detalii_site.continut = realloc(site[i].detalii_site.continut, lung_cont * sizeof(char));
            }


        }
        fclose(fp);
    }

}
int comp(struct nume_site x ,struct nume_site y )
{          if( x.detalii_site.nr_accesari < y.detalii_site.nr_accesari)
                return 1;       //trebuie facut switch
            else
                return 0;
}

void sortare(int (*f)(struct nume_site  ,struct nume_site ),nume_site *are_cuv_cheie ,nume_site *site,  char **cuvinte_cheie, int nr_site, int nr_cuv )
{   nume_site aux;
    int i;
    int j;
    int k          = nr_site;

    f=comp;

        for ( i = 0; i < k - 1; i++)
        {   
            for(j = i + 1; j < k; j++)
            {
                if( f( are_cuv_cheie[i], are_cuv_cheie[j]) == 1)       //sortare lexicografica in ordine crescatoare
                {
                    aux = are_cuv_cheie[i];
                    are_cuv_cheie[i] = are_cuv_cheie[j];
                    are_cuv_cheie[j] = aux;

                }
            }
        }
        for ( i = 0; i < k ; i++)
        {
            printf("%s\n", are_cuv_cheie[i].detalii_site.URL);
        }
    


}




int main()
{   int nr_site     = 0;
    int capacitate  = 3;
    int j           = 0;
    int cnr_site    = 0;
    int i;
    int ok          = 0;
    nume_site *site = malloc(capacitate*sizeof(nume_site));
    nume_site *are_cuv_cheie;
    FILE *fr        = fopen("master.txt","r");
    char linie_cheie[100];
    char **cuv_cheie = malloc(capacitate * sizeof (char*));

    while(fscanf(fr, "%s", site[nr_site].name ) != EOF)
    {   nr_site++;
        if ( nr_site % 3 == 0)
        {
            capacitate = nr_site + 3;
            site = realloc(site, capacitate*sizeof(nume_site) );
        }

        
    }
    are_cuv_cheie = malloc( capacitate *sizeof (nume_site));


    cnr_site = nr_site;
    fclose(fr);
    citire(site,nr_site);
    int c2nr_site = cnr_site;
    parsare(site, c2nr_site);

   scanf("%[^\n]s",linie_cheie);  //citesc sir pana la enter

    int numar_cuvinte = 0;
    char cuvant[100];
    char copie[200];
    int secventa      = 0;
    int dim_secv      = 0;
    char *copie_cuvant;
    

    linie_cheie[strlen(linie_cheie) + 1] = '\0';
    copie_cuvant = strtok(linie_cheie, " "); //iau primul cuvant din sir 
    strcpy(cuvant,copie_cuvant);                //il copiez in alt string numit cuvant


    if( cuvant[0] == '\"')                  //verific daca e secventa
    {   dim_secv     = dim_secv + strlen(cuvant) + 1;
        cuv_cheie[0] = malloc( dim_secv * sizeof (char));
        strcpy(cuv_cheie[numar_cuvinte],cuvant);    //copiez cuvantul in pointerul dublu de cuvinte cheie
        cuv_cheie[numar_cuvinte][0] = ' ';          //inlocuiesc ghilimelele cu spatiu 
        ok           = 1;                           // ok=1 echivalent cu faptul ca ma aflu intr-o secventa
        if( cuvant[ strlen(cuvant) - 1] == '"')     //verific daca se termina secventa
                {
                    
                    cuv_cheie[numar_cuvinte][strlen(cuv_cheie[numar_cuvinte]) - 1]=' ';     //copiez cuvantul pe aceeasi "linie"
                    cuv_cheie[numar_cuvinte][strlen(cuv_cheie[numar_cuvinte])]='\0';        //iar ghilimelele devin spatiu
                    ok = 0;                                                                 //nu mai sunt in secventa
                    numar_cuvinte++;                                                        //trec la urmatoarea "linie"
                }
    }

    if( cuvant[0] != '"')       //daca nu intru in secventa
    {
        cuv_cheie[numar_cuvinte] = malloc( (strlen (cuvant) + 2) * sizeof(char));
                strcpy(cuv_cheie[numar_cuvinte],cuvant);        //copiez cuvantul pe aceeasi "linie"
                
                if(cuvant[0] != '-')    //daca nu incepe cuvantul cu "-"
                {
                    for ( i = strlen( cuvant); i > 0; i-- )     //mut cuvantul cu o pozitie la dreapta
                        cuv_cheie[numar_cuvinte][i] = cuv_cheie[numar_cuvinte][i - 1];

                    cuv_cheie[numar_cuvinte][0] = ' ';          //pun spatiu pe prima poz
                    
                }
                if(cuvant[0] == '-')    //daca incepe cu "-"
                {
                    for( i = strlen(cuvant); i > 1; i--)        //mut la dreapt
                        cuv_cheie[numar_cuvinte][i] = cuv_cheie[numar_cuvinte][i - 1];
                    cuv_cheie[numar_cuvinte][1] = ' ';          //si pun spatiu dupa "-"
                    
                }
                cuv_cheie[numar_cuvinte][strlen(cuvant) + 1] = ' ';     //spatiu la final de cuv cheie
                cuv_cheie[numar_cuvinte][strlen(cuvant) + 2] = '\0';
                
                numar_cuvinte++;

    }

        while ( (copie_cuvant = strtok(NULL," " )) != NULL)     //iau cuvant cu cuvant
        {
            strcpy(cuvant,copie_cuvant);        //voi lucra cu "cuvant"

            if( numar_cuvinte == capacitate-1)
            {
                capacitate = capacitate * 2;
                cuv_cheie  = realloc( cuv_cheie, capacitate * sizeof(char *));
            }

            if( ok == 0 && cuvant[0] != '"')                //ok=0 daca nu sunt in secventa si nu incepe una
            {     
                cuv_cheie[numar_cuvinte] = malloc( (strlen (cuvant) + 2) * sizeof(char)); //aloc dim si pentru cele doua spatii pe care le voi pune
                strcpy(cuv_cheie[numar_cuvinte],cuvant);
                //pentru toate mut la dreapta cu o pozitie
                //si pun cate un spatiu inainte si dupa fiecare cuvant daca nu incepe cu "-"
                //daca incepe cu "-", spatiul de la inceput il pun dupa "-"
                if(cuvant[0] != '-')
                {
                    for ( i = strlen( cuvant); i > 0; i-- )         //mut la dreapta
                        cuv_cheie[numar_cuvinte][i] = cuv_cheie[numar_cuvinte][i - 1];

                    cuv_cheie[numar_cuvinte][0] = ' ';
                }
                if(cuvant[0] == '-')
                {
                    for( i = strlen(cuvant); i > 1; i--)    //mut la dreapta
                        cuv_cheie[numar_cuvinte][i] = cuv_cheie[numar_cuvinte][i - 1];
                    
                    cuv_cheie[numar_cuvinte][1] = ' ';  //si pun spatiu dupa "-"
                }
                cuv_cheie[numar_cuvinte][strlen(cuvant) + 1] = ' ';
                cuv_cheie[numar_cuvinte][strlen(cuvant) + 2] = '\0';
                numar_cuvinte++;

            }
            if( cuvant[0] == '"' && ok == 0)
            {   dim_secv = dim_secv + strlen(cuvant) + 1;
                cuv_cheie[numar_cuvinte] = malloc( dim_secv * sizeof (char));
                strcpy(cuv_cheie[numar_cuvinte],cuvant);
                cuv_cheie[numar_cuvinte][0] = ' ';
                ok           = 1;
                if( cuvant[ strlen(cuvant) - 1] == '"')
                {
                    
                    cuv_cheie[numar_cuvinte][strlen(cuv_cheie[numar_cuvinte])-1] = ' ';
                    cuv_cheie[numar_cuvinte][strlen(cuv_cheie[numar_cuvinte])] = '\0';
                    ok = 0;
                    numar_cuvinte++;
                }
            }
            else if ( ok == 1)                  //ok=1 deci sunt intr-o secventa
            {
                if( cuvant[ strlen(cuvant) - 1] == '"')     //si se termina secventa
                {
                    dim_secv = dim_secv + strlen(cuvant) + 1;
                    cuv_cheie[numar_cuvinte] = realloc(cuv_cheie[numar_cuvinte], dim_secv * sizeof(char));
                    strcat(cuv_cheie[numar_cuvinte]," ");       //concatenez spatiu
                    cuvant[strlen(cuvant) - 1] = ' ';           //pun spatiu la final de cuvant in loc de "
                    cuvant[strlen(cuvant)] = '\0';              
                    strcat(cuv_cheie[numar_cuvinte], cuvant);   //si il concatenez
                    dim_secv = 0;
                    numar_cuvinte++;
                    ok = 0;                                     //ies din secventa
                }
                else
                {   //altfel pun spatiu si concatenez
                    dim_secv = dim_secv + strlen(cuvant) + 1 ;
                    cuv_cheie[numar_cuvinte] = realloc(cuv_cheie[numar_cuvinte], dim_secv * sizeof(char));
                    strcat(cuv_cheie[numar_cuvinte]," ");
                    strcat(cuv_cheie[numar_cuvinte], cuvant);
                    
                }

            }


        }
  


    int k          = 0;
        ok         = 0;
    int site_incorect[100] = { } ;
    for ( i = 0; i < cnr_site; i++)
    {
        for ( j = 0; j < numar_cuvinte; j++)
        {
            if( (cuv_cheie[j][0]) == '-')
            {   
                if (  strstr( site[i].detalii_site.copie_paragraf, cuv_cheie[j] + 1) != NULL )     //verific daca cuvantul apare in vreun site
                    site_incorect[i] ++;                                                           //daca apare il incrementez in vector,altfel ramane 0
        
            }   
        }
    }

    for ( i = 0; i < cnr_site; i++)
    {
        for ( j = 0; j < numar_cuvinte; j++)
        {   
            if ( cuv_cheie[j][0] != '-')
            {
                if ( strstr( site[i].detalii_site.copie_paragraf, cuv_cheie[j]) != NULL && ok == 0 && site_incorect[i] == 0) 
                {   //daca exista cuvantul cheie in paragraf si site-ul este corect (nu se afla cuvant fals cheie care incepe cu "-")
                    //il retin
                     are_cuv_cheie[k++] = site[i];
                   
                ok = 1; //site-ul a fost gasit odata
                }
            }
            
        }
        ok = 0;
    }

    int (*comp)(struct nume_site, struct nume_site );
    sortare(comp,are_cuv_cheie,site,cuv_cheie,k, numar_cuvinte);
free(site);
free(are_cuv_cheie);
free(cuv_cheie);
//    for ( j = 0; j < cnr_site; j++ ){
 //       free(site[j].detalii_site.continut);
 //       free(site[j].detalii_site.continut_parsat);
 //       free(site[j].detalii_site.copie_paragraf);
      
  //  }
//    free(site);
//    free(are_cuv_cheie);
  //  printf("%d--",numar_cuvinte);
  //  for(i=0;i<numar_cuvinte;i++)
  //  printf(">%s<\n",cuv_cheie[i]);
  //  for(i = 0; i < numar_cuvinte; i++)
  //  {
     //   free(cuv_cheie[i]);
     //   cuv_cheie[i] = NULL;
        
   // }
       
 //   free(cuv_cheie);
//    cuv_cheie = NULL;
   

    return 0;
}

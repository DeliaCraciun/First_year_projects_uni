#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "citire_parsare.h"

void cautare_avansata(nume_site *site,nume_site *are_cuv_cheie,char **cuv_cheie, int cnr_site,int *k,int *nr_cuv,int capacitate,char linie_cheie[100])
{
    int numar_cuvinte = 0;
    char cuvant[100];
    char copie[200];
    int secventa      = 0;
    int dim_secv      = 0;
    char *copie_cuvant;
    int i;
    int ok;
    int j;

    linie_cheie[strlen(linie_cheie) + 1] = '\0';
    copie_cuvant = strtok(linie_cheie, " ");
    strcpy(cuvant,copie_cuvant);


    if( cuvant[0] == '\"')
    {   dim_secv     = dim_secv + strlen(cuvant) + 1;
        cuv_cheie[0] = malloc( dim_secv * sizeof (char));
        strcpy(cuv_cheie[numar_cuvinte],cuvant);
        cuv_cheie[numar_cuvinte][0] = ' ';
        ok           = 1;
        if( cuvant[ strlen(cuvant) - 1] == '"')
                {
                    
                    cuv_cheie[numar_cuvinte][strlen(cuv_cheie[numar_cuvinte]) - 1]=' ';
                    cuv_cheie[numar_cuvinte][strlen(cuv_cheie[numar_cuvinte])]='\0';
                    ok = 0;
                    numar_cuvinte++;
                }
    }

    if( cuvant[0] != '"')
    {
        cuv_cheie[numar_cuvinte] = malloc( (strlen (cuvant) + 2) * sizeof(char));
                strcpy(cuv_cheie[numar_cuvinte],cuvant);
                
                if(cuvant[0] != '-')
                {
                    for ( i = strlen( cuvant); i > 0; i-- )
                        cuv_cheie[numar_cuvinte][i] = cuv_cheie[numar_cuvinte][i - 1];

                    cuv_cheie[numar_cuvinte][0] = ' ';
                    
                }
                if(cuvant[0] == '-')
                {
                    for( i = strlen(cuvant); i > 1; i--)
                        cuv_cheie[numar_cuvinte][i] = cuv_cheie[numar_cuvinte][i - 1];
                    cuv_cheie[numar_cuvinte][1] = ' ';
                    
                }
                cuv_cheie[numar_cuvinte][strlen(cuvant) + 1] = ' ';
                cuv_cheie[numar_cuvinte][strlen(cuvant) + 2] = '\0';
                
                numar_cuvinte++;

    }

        while ( (copie_cuvant = strtok(NULL," " )) != NULL)
        {
            strcpy(cuvant,copie_cuvant);

            if( numar_cuvinte == capacitate-1)
            {
                capacitate = capacitate * 2;
                cuv_cheie  = realloc( cuv_cheie, capacitate * sizeof(char *));
            }

            if( ok == 0 && cuvant[0] != '"')                //ok=0 daca nu sunt in secventa
            {     
                cuv_cheie[numar_cuvinte] = malloc( (strlen (cuvant) + 2) * sizeof(char));
                strcpy(cuv_cheie[numar_cuvinte],cuvant);
                
                if(cuvant[0] != '-')
                {
                    for ( i = strlen( cuvant); i > 0; i-- )
                        cuv_cheie[numar_cuvinte][i] = cuv_cheie[numar_cuvinte][i - 1];

                    cuv_cheie[numar_cuvinte][0] = ' ';
                }
                if(cuvant[0] == '-')
                {
                    for( i = strlen(cuvant); i > 1; i--)
                        cuv_cheie[numar_cuvinte][i] = cuv_cheie[numar_cuvinte][i - 1];
                    
                    cuv_cheie[numar_cuvinte][1] = ' ';
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

               // printf("!");
                //printf("%c\n",cuvant[0]);
             //   printf("%s\n",cuv_cheie[numar_cuvinte]);
            }
            else if ( ok == 1)                  //ok=1 deci sunt intr-o secventa
            {
                if( cuvant[ strlen(cuvant) - 1] == '"')
                {
                    dim_secv = dim_secv + strlen(cuvant) + 1;
                    cuv_cheie[numar_cuvinte] = realloc(cuv_cheie[numar_cuvinte], dim_secv * sizeof(char));
                    strcat(cuv_cheie[numar_cuvinte]," ");
                    cuvant[strlen(cuvant) - 1] = ' ';
                    cuvant[strlen(cuvant)] = '\0';
                    strcat(cuv_cheie[numar_cuvinte], cuvant);
                    dim_secv = 0;
                    numar_cuvinte++;
                    ok = 0;
                }
                else
                {
                    dim_secv = dim_secv + strlen(cuvant) + 1 ;
                    cuv_cheie[numar_cuvinte] = realloc(cuv_cheie[numar_cuvinte], dim_secv * sizeof(char));
                    strcat(cuv_cheie[numar_cuvinte]," ");
                    strcat(cuv_cheie[numar_cuvinte], cuvant);
                    
                }

            }


        }
      //  for(i=0;i<numar_cuvinte;i++)
        //    printf("--%s--\n",cuv_cheie[i]);

        ok         = 0;
    int site_incorect[100] = { } ;
    for ( i = 0; i < cnr_site; i++)
    {
        for ( j = 0; j < numar_cuvinte; j++)
        {
            if( (cuv_cheie[j][0]) == '-')
            {   
                if (  strstr( site[i].detalii_site.copie_paragraf, cuv_cheie[j] + 1) != NULL )     //verific daca cuvantul apare in vreun site
                    site_incorect[i] ++;                                                           //daca apare il fac in vector 1,altfel 0
        
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
                {
                     are_cuv_cheie[(*k)++] = site[i];
                   
                ok = 1;
                }
            }
            
        }
        ok = 0;
    }
}


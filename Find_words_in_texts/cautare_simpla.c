#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "citire_parsare.h"

void cautare_simpla(nume_site *site,nume_site *are_cuv_cheie,char **cuv_cheie, int cnr_site,int *k,int *nr_cuv,int capacitate,char linie_cheie[100])
{
    int numar_cuvinte = 0;
    char *cuvant;
    int i;
       cuvant = strtok( linie_cheie, " ");
    cuv_cheie[0] = malloc( (strlen(cuvant) + 3) * sizeof (char));
    strcpy(cuv_cheie[numar_cuvinte],cuvant);

    for ( i = strlen( cuvant); i > 0; i-- )
        cuv_cheie[numar_cuvinte][i] = cuv_cheie[numar_cuvinte][i - 1];

    cuv_cheie[numar_cuvinte][0] = ' ';
    cuv_cheie[numar_cuvinte][strlen(cuvant) + 1] = ' ';
    cuv_cheie[numar_cuvinte][strlen(cuvant) + 2] = '\0';

    numar_cuvinte++;

        while ( (cuvant = strtok(NULL," " )) != NULL)
        {
            if( numar_cuvinte == capacitate)
            {
                capacitate = capacitate * 2;
                cuv_cheie = realloc( cuv_cheie, capacitate * sizeof(char *));
            }
            cuv_cheie[numar_cuvinte] = malloc( (strlen (cuvant) + 3) * sizeof(char));
            strcpy(cuv_cheie[numar_cuvinte],cuvant);
            for ( i = strlen( cuvant); i > 0; i-- )
                cuv_cheie[numar_cuvinte][i] = cuv_cheie[numar_cuvinte][i - 1];
        
            cuv_cheie[numar_cuvinte][0] = ' ';
            cuv_cheie[numar_cuvinte][strlen(cuvant) + 1] = ' ';
            cuv_cheie[numar_cuvinte][strlen(cuvant) + 2] = '\0';
            numar_cuvinte++;
   
        }
//   for(j=0;j<numar_cuvinte;j++)
  //   printf("->%s<-\n",cuv_cheie[j]);   

   //  printf("DA");

    int ok         = 0;
    int j;
    *k = 0;
      
    for ( i = 0; i < cnr_site; i++)
    {
        for ( j = 0; j < numar_cuvinte; j++)
        {
            if ( strstr( site[i].detalii_site.copie_paragraf, cuv_cheie[j]) != NULL && ok == 0)
            {   are_cuv_cheie[(*k)++] = site[i];
                ok = 1;
            }
           
        }
       
        ok = 0;
    }
    (*nr_cuv) = numar_cuvinte;
}
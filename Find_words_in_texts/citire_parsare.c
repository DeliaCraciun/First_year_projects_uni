#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "citire_parsare.h"

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
        site[i].detalii_site.continut_parsat = (char *)malloc( lung_cont * sizeof(char));
  
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


void parsare(nume_site *site , int n){
    int i;
    int j;
    int k = 0;
   
    for( i = 0; i < n; i++)
    {   site[i].detalii_site.continut_parsat=malloc(2 * sizeof(char));
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
            int dimensiune               = sfarsit_paragraf - inceput_paragraf ;

            site[i].detalii_site.continut_parsat = realloc( site[i].detalii_site.continut_parsat, (dimensiune + 1) * sizeof( char));
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
   //      printf("----->%s<------",site[i].detalii_site.copie_paragraf);
    }
    
   
    

}



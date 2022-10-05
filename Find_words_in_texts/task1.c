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
    char *continut;             //cod HTML
    char *continut_parsat;
} info_site;

typedef struct
{
    char name[100];
    info_site detalii_site;
} nume_site;

void parsare(nume_site *site , int n){
    int i;
    int j;
    int k = 0;
   
    for( i = 0; i < n; i++)
    {   site[i].detalii_site.continut[site[i].detalii_site.lungime] = '\0';         //pun terminator de sir la final de continut
        char *pointer_titlu_tag1 = strstr( site[i].detalii_site.continut, "<title>");       // pointer la inceput de titlu dupa ce il gasesc cu strstr
        char *pointer_titlu_tag2 = strstr( site[i].detalii_site.continut, "</title>");      //pointer la final de titlu
        int inceput_titlu = pointer_titlu_tag1 - site[i].detalii_site.continut + 7;         //aflu de unde incepe titlul exact,imediat dupa tag
        int sfarsit_titlu = pointer_titlu_tag2 - site[i].detalii_site.continut;             //unde se termina titlul,inainte de tag
        site[i].detalii_site.continut_parsat = malloc(2*sizeof(char));
         //printf("%s\n%s",pointer_titlu_tag1,pointer_titlu_tag2);
        k = 0;
        for( j = inceput_titlu; j < sfarsit_titlu; j++)
        {   
            site[i].detalii_site.titlu[k] =site[i].detalii_site.continut[j];            //salvez titlul caracter cu caracter
            k++;
        }
        site[i].detalii_site.titlu[k] = '\0';
        k = 0;
        if( strstr( site[i].detalii_site.continut, "<p>") != NULL)                  //daca am gasit tag fara style de paragraf
        {
            char *point_incep_paragraf   = strstr( site[i].detalii_site.continut, "<p>");   //pointer la paragraf dupa tag
            char *point_sfarsit_paragraf = strstr( site[i].detalii_site.continut, "</p>");  //pointer la final de paragraf,inainte de tag
            int inceput_paragraf         = point_incep_paragraf - site[i].detalii_site.continut + 3; 
            int sfarsit_paragraf         = point_sfarsit_paragraf -site[i].detalii_site.continut;   
            int dimensiune               = sfarsit_paragraf - inceput_paragraf + 1;         //lungime paragraf

            site[i].detalii_site.continut_parsat = realloc( site[i].detalii_site.continut_parsat, dimensiune * sizeof( char));  

            for ( j = inceput_paragraf; j < sfarsit_paragraf; j++)
            {
                site[i].detalii_site.continut_parsat[k] = site[i].detalii_site.continut[j];     //salvare paragraf caracter cu caracter
                k++;
            }
        site[i].detalii_site.continut_parsat[k] = '\0';
        k = 0;
        }
        
        if ( strstr( site[i].detalii_site.continut, ";\">") != NULL)    //daca e paragraf cu style
        {
            char *point_incep_paragraf   = strstr( site[i].detalii_site.continut, ";\">");  //pointer la paragraf dupa tag ce contine style
            char *point_sfarsit_paragraf = strstr( site[i].detalii_site.continut, "</p>");  //pointer la final de paragraf,inainte de tag
            int inceput_paragraf         = point_incep_paragraf - site[i].detalii_site.continut + 3;
            int sfarsit_paragraf         = point_sfarsit_paragraf -site[i].detalii_site.continut;
            int dimensiune               = sfarsit_paragraf - inceput_paragraf + 1;         //dim paragraf

            site[i].detalii_site.continut_parsat = realloc( site[i].detalii_site.continut_parsat, dimensiune * sizeof( char));

            for ( j = inceput_paragraf; j < sfarsit_paragraf; j++)
            {
                site[i].detalii_site.continut_parsat[k] = site[i].detalii_site.continut[j];     //copiere paragraf caracter cu caracter
                k++;
            }
        site[i].detalii_site.continut_parsat[k] = '\0';
        k = 0;
        }
    }
    

}

void citire(nume_site *site, int n)
{
    int i = 0;
    int j = 0;
    FILE *fp;

    for ( i = 0; i < n; i++ )       //deschid fiecare site si citesc pentru fiecare informatiile
    {   
        fp=fopen(site[i].name, "r");
        //citesc datele de pe prima linie
        fscanf(fp,"%s %d %d %d",site[i].detalii_site.URL,&site[i].detalii_site.lungime,&site[i].detalii_site.nr_accesari,&site[i].detalii_site.checksum);
        char enter;
        fscanf(fp,"%c",&enter); //citesc enter-ul
        int lung_cont =  site[i].detalii_site.lungime;      //salvez nr. de octeti(care nu contine enter) dati pentru alocare
        site[i].detalii_site.continut = (char *)malloc( lung_cont * sizeof(char));
  
        for ( j = 0; j < lung_cont ; j++ )  
        {
            fscanf(fp, "%c",&site[i].detalii_site.continut[j]); //citesc caracter cu caracter,salvand continutul intr-un pointer
            if( site[i].detalii_site.continut[j] == '\n')   //cand ajung la enter, realoc cu o "casuta" in plus
            {
                lung_cont++;
                site[i].detalii_site.continut = realloc(site[i].detalii_site.continut, lung_cont * sizeof(char));
            }

        
        }

        fclose(fp); 
    }

}    



int main()
{   int nr_site     = 0;
    int capacitate  = 3;
    int j           = 0;
    int cnr_site    = 0;
    nume_site *site = malloc(capacitate*sizeof(nume_site));
    FILE *fr        = fopen("master.txt","r");

    while(fscanf(fr, "%s", site[nr_site].name ) != EOF) //citesc linie cu linie pana la final de fisier
    {
        nr_site++;
        if ( nr_site % 3 == 0)      //realoc din 3 in 3
        {
            capacitate = nr_site + 3;
            site = realloc(site, capacitate*sizeof(nume_site) );
        }

        
    }
     

    cnr_site = nr_site;
    fclose(fr);
    citire(site,nr_site);
    int c2nr_site = cnr_site;
    parsare(site, c2nr_site);

    for ( j = 0; j < cnr_site ; j++ )
    {
        printf("%s %d %s",site[j].detalii_site.URL, site[j].detalii_site.nr_accesari, site[j].detalii_site.titlu );
        printf("\n");
    }
    for ( j = 0; j < cnr_site; j++ ){
            free(site[j].detalii_site.continut);
            free(site[j].detalii_site.continut_parsat);
    }   
    free(site);


    return 0;
}

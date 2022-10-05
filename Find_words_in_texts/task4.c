#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct
{
    char URL[50];
    int lungime;
    int nr_accesari;
    int checksum;
    char titlu[51];
    char *continut;
    char *continut_parsat;
} info_site;

typedef struct
{
    char name[100];
    info_site detalii_site;
} nume_site;

void dec_to_bin(int n,char *s)      //transforma decimal in binar si il pune in s
{ 
    int rest;
    int i=7;
    while(n!=0 && i >=0){            
        rest=n%2;
        n=n/2;
        s[i]=(char)(rest+48); //pentru a adauga siruri de caractere de 0,1 adaug 48 la int(ascii)
       i--;
    }
    for(int j = i; j >= 0; j--)
        s[j] = '0';
    s[8]='\0';  //pun terminator de sir 
}
int bin_to_dec(char *s)  //transforma binar in decimal
{
    int dec=0;
    int i=7,n;
    while(i>=0){
        n=(int)(s[i]-48); //pentru a ma intoarce la int de 0,1 scad 48 din caracter
        dec=dec+n*pow(2,7-i);
        i--;

    }
    return dec;
}

int rotl( char x, int k)
{   char s[9];
    int i;
    char aux;
    int nr = 0;
    int cont = 0;
    char copie = x;

    dec_to_bin((int)(copie),s); //transform caracterul in forma binara
    
    while( k != 0)
    {
        aux = s[0];
    for(i = 0; i < 7; i++)   //   mut la stanga cu o pozitie fiecare bit de k ori
        s[i] = s[i + 1];
    s[7] = aux;
    s[8] = '\0';
    k--;
    }
    

    return bin_to_dec(s);           //returnez binar

}

int rotr(char x, int k)
{
    char s[9];
    int i;
    char aux;
    int cont = 0;
    int nr = 0;
    char copie = x;

dec_to_bin((int)(copie),s);     //transform caracterul in forma binara
   s[8] = '\0';

while( k != 0)
{
    aux = s[7];
    for( i = 7; i > 0; i--)         //   mut la stanga cu o pozitie fiecare bit de k ori
        s[i] = s[i - 1];
    s[0] = aux;
    k--;
}
    

    return bin_to_dec(s);        //returnez binar
    
}

void parsare(nume_site *site , int n){
    int i;
    int j;
    int k = 0;
   
    for( i = 0; i < n; i++)
    {
        char *pointer_titlu_tag1 = strstr( site[i].detalii_site.continut, "<title>");
       // printf("%s", site[i].detalii_site.continut);
        char *pointer_titlu_tag2 = strstr( site[i].detalii_site.continut, "</title>");
        int inceput_titlu = pointer_titlu_tag1 - site[i].detalii_site.continut + 7;
        int sfarsit_titlu = pointer_titlu_tag2 - site[i].detalii_site.continut;
        site[i].detalii_site.continut_parsat = malloc(2*sizeof(char));
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

            site[i].detalii_site.continut_parsat = realloc( site[i].detalii_site.continut_parsat, dimensiune * sizeof( char));

            for ( j = inceput_paragraf; j < sfarsit_paragraf; j++)
            {
                site[i].detalii_site.continut_parsat[k] = site[i].detalii_site.continut[j];
                k++;
            }
        site[i].detalii_site.continut_parsat[k] = '\0';
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

            for ( j = inceput_paragraf; j < sfarsit_paragraf; j++)
            {
                site[i].detalii_site.continut_parsat[k] = site[i].detalii_site.continut[j];
                k++;
            }
        site[i].detalii_site.continut_parsat[k] = '\0';
        k = 0;
        }
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
        int lung_cont =  site[i].detalii_site.lungime ;
        site[i].detalii_site.continut = (char *)malloc( lung_cont * sizeof(char));
  
        for ( j = 0; j < lung_cont ; j++ )
        {
            fscanf(fp, "%c",&site[i].detalii_site.continut[j]);

        }
        site[i].detalii_site.continut[lung_cont ] = '\0';
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

    while(fscanf(fr, "%s", site[nr_site].name ) != EOF)
    {
        nr_site++;
        if ( nr_site % 3 == 0)
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

    int i;
    int ok;
    int cheie_gasita = 0;  
    char link[61];

    while(fgets(link,60,stdin)) //citesc link cu link de la tastatura
    {   
        if(link[strlen(link) - 1] == '\n');
            link[strlen(link) - 1] = '\0';
        //printf("%s",link);
        ok = 0;
        for(i = 0; i < cnr_site; i++)
        {   cheie_gasita = 0;
            if ( strcmp(link, site[i].detalii_site.URL) == 0)   //verific ca link-ul sa se regaseasca in vreunul
            {                                                   //din site-uri
                for( j = 0; j < strlen(site[i].detalii_site.continut); j++) //parcurg codul HTML
                {  // printf("da");
            
                    if( j % 2  != 0)    //daca e impara pozitia
                    {
                        cheie_gasita ^=  rotr( site[i].detalii_site.continut[j], j);    //adaug XOR la cheie dupa ce
                                                                                        //il ii mut bitii caracterului la dreapta
                    }                                                                   //de j ori
               
                    if( j % 2 == 0)
                    {
                    cheie_gasita ^=  rotl ( site[i].detalii_site.continut[j], j);       //adaug XOR la cheie dupa ce
                                                                                        //il ii mut bitii caracterului la stanga
                    }                                                                   //de j ori
                    
               
                
                }
                if( cheie_gasita == site[i].detalii_site.checksum)
                    printf("Website safe!\n");
                if( cheie_gasita != site[i].detalii_site.checksum)
                    printf("Malicious website! Official key: %d. Found key: %d\n",site[i].detalii_site.checksum,cheie_gasita);
                ok = 1;

            }
            
        }
        if(ok == 0)
                printf("Website not found!\n");
        
    }

    for ( j = 0; j < cnr_site; j++ ){
            free(site[j].detalii_site.continut);
            free(site[j].detalii_site.continut_parsat);
 
    }   
    free(site);



    return 0;
}

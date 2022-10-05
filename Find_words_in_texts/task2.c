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
int comp(struct  nume_site x , struct nume_site y )
{  // printf("%s && %s\n",x.detalii_site.titlu,y.detalii_site.titlu);    
    if( strcmp( x.detalii_site.copie_paragraf, y.detalii_site.copie_paragraf) == 0) //compar cu strcmp continuturile
    {                                                                               //daca sunt egale,sortez dupa nr. accesari
            if( x.detalii_site.nr_accesari < y.detalii_site.nr_accesari)
                return 1;       //trebuie facut switch
            else
                return 0;       //ordinea e corecta
    }
        
    if( strcmp( x.detalii_site.copie_paragraf, y.detalii_site.copie_paragraf) > 0)  //daca continutul de la struct x e mai mare dpdv
        return 1;                                                                  //lexicografic,fac switch
    else
        return 0;       //altfel le las asa
    
    
          
}

void sortare(int (*f)(struct nume_site  ,struct nume_site ),nume_site *are_cuv_cheie ,nume_site *site,  char **cuvinte_cheie, int nr_site, int nr_cuv )
{   nume_site aux ;
    int i;
    int j;
    int k          = nr_site;

    f=comp;     //egala cu functia mea de comparare
  //  printf("%d->",k);
        for ( i = 0; i < k - 1; i++)
        {
            for(j = i + 1; j < k; j++)
            {  
                if( f( are_cuv_cheie[i], are_cuv_cheie[j]) == 1)       //sortare lexicografica in ordine crescatoare 
                {   
                    aux = are_cuv_cheie[i];                            //interschimbare
                    are_cuv_cheie[i] = are_cuv_cheie[j];
                    are_cuv_cheie[j] = aux;
                
                }
                
            }    
        }
        for ( i = 0; i < k ; i++)
        printf("%s\n", are_cuv_cheie[i].detalii_site.URL);
     
            
         
}




int main()
{   int nr_site     = 0;
    int capacitate  = 3;
    int j           = 0;
    int cnr_site    = 0;
    int i           = 0;
    nume_site *site = malloc(capacitate*sizeof(nume_site));
    nume_site *are_cuv_cheie;
    FILE *fr        = fopen("master.txt","r");
    char linie_cheie[100];
    char **cuv_cheie = malloc(capacitate * sizeof (char*));    

    while(fscanf(fr, "%s", site[nr_site].name ) != EOF)
    {    nr_site++;
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


    scanf("%[^\n]s",linie_cheie);           //citesc un sir pana la enter

    int numar_cuvinte = 0;
    char *cuvant;
    cuvant = strtok( linie_cheie, " ");         //iau primul cuvant din sirul citit
	cuvant[strlen(cuvant)]='\0';
    cuv_cheie[0] = malloc( (strlen(cuvant) + 3) * sizeof (char));       //aloc spatiu pentru pointerul dublu plus 2 pozitii in plus 
    strcpy(cuv_cheie[numar_cuvinte],cuvant);                            //apoi copiez cuvantul cheie in acest pointer

    for ( i = strlen( cuvant); i > 0; i-- )                         
        cuv_cheie[numar_cuvinte][i] = cuv_cheie[numar_cuvinte][i - 1];      //mut cuvantul cu o pozitie mai la dreapta

    cuv_cheie[numar_cuvinte][0] = ' ';                                      //pt a pune spatiu pe prima si ultima pozitie
    cuv_cheie[numar_cuvinte][strlen(cuvant) + 1] = ' ';
    cuv_cheie[numar_cuvinte][strlen(cuvant) + 2] = '\0';

    numar_cuvinte++;        //trec la urmatorul cuvant

        while ( (cuvant = strtok(NULL," " )) != NULL)               //iau cuvintele pe rand
        {	cuvant[strlen(cuvant)] = '\0';
            if( numar_cuvinte == capacitate)                        //aloc dim pt "linii"
            {
                capacitate = capacitate * 2;
                cuv_cheie = realloc( cuv_cheie, capacitate * sizeof(char *));
            }
            cuv_cheie[numar_cuvinte] = malloc( (strlen (cuvant) + 3) * sizeof(char));   //aloc dim cu 2 in plus pt"coloane"
            strcpy(cuv_cheie[numar_cuvinte],cuvant);
            for ( i = strlen( cuvant); i > 0; i-- )                             //mut la dreapta cu o pozitie
                cuv_cheie[numar_cuvinte][i] = cuv_cheie[numar_cuvinte][i - 1];
        
            cuv_cheie[numar_cuvinte][0] = ' ';                                  //pun spatii
            cuv_cheie[numar_cuvinte][strlen(cuvant) + 1] = ' ';
            cuv_cheie[numar_cuvinte][strlen(cuvant) + 2] = '\0';
            numar_cuvinte++;
   
        }

    int k          = 0;
    int ok         = 0;
      
    for ( i = 0; i < cnr_site; i++)
    {
        for ( j = 0; j < numar_cuvinte; j++)
        {
            if ( strstr( site[i].detalii_site.copie_paragraf, cuv_cheie[j]) != NULL && ok == 0) //verific sa se regaseasca cuvantul cheie
            {   are_cuv_cheie[k++] = site[i];                                                   //in fiecare site
                ok = 1;                                                                         //fac ok=1 ca sa nu se mai verifice alte cuvinte
            }                                                                                   //in acelasi site,daca au fost deja gasite
           
        }
       
        ok = 0;
    }
   
    

    int (*comp)(struct nume_site, struct nume_site );       //declarare pointer la functie
    sortare(comp,are_cuv_cheie,site,cuv_cheie,k, numar_cuvinte);        //sortez

    j = 0;
//    free(site);
//    free(are_cuv_cheie);
//    free(cuv_cheie);
    for ( j = 0; j < cnr_site; j++ ){
        free(site[j].detalii_site.continut);
        free(site[j].detalii_site.continut_parsat);
        free(site[j].detalii_site.copie_paragraf);
	
    }
	for( j = 0; j < numar_cuvinte; j++)
	free(cuv_cheie[j]);
//	for( j = 0; j < k; j++)
//	free(are_cuv_cheie[j]); 
free(site);
free(are_cuv_cheie);
free(cuv_cheie);
    return 0;
}

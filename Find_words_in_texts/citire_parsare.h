#ifndef _CITIRE_PARSARE_h_
#define _CITIRE_PARSARE_h_

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

typedef struct 
{ 
    char name[100];
    info_site detalii_site;
} nume_site;

void citire(nume_site *site, int n);
void parsare(nume_site *site , int n);

#endif
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "citire_parsare.h"
#include "cautare_simpla.h"
#include "cautare_avansata.h"

void next_page(char string[200],int k,nume_site *are_cuv_cheie)
{   int height,width, start_y,start_x;
    height = 40;
    width = 50;
    start_x = start_y = 10;
    WINDOW *next = newwin(height,width,start_y,start_x);    //initializez fereastra noua
    clear();
    refresh();
    box(next,0,0);          //creez fereastra
    mvwprintw(next,2,2,"TEXT CAUTAT: %s",string);       //printez textul cautat

    int i;
    int y = 5;
    for(i = 0; i < k; i++)      //pt fiecare site gasit cu cuvinte cheie il afisez in fereastra asta
    {   y+=2;                   //la fiecare site nou,ma duc mai in jos cu 2 pozitii ca sa las
       // start_x+=2;           //spatiu
        mvwprintw(next,y,5,"%s",are_cuv_cheie[i].detalii_site.titlu);
        y+=1;
        mvwprintw(next,y,5,"%s",are_cuv_cheie[i].detalii_site.URL);
        wrefresh(next);     //refresh la fereastra ca sa se afiseze
    }
}

int main(int argc,int *argv)
{   int nr_site     = 0;
    int k           = 0;
    int nr_cuv      = 0;
    int capacitate  = 3;
    int j           = 0;
    int cnr_site    = 0;
    int i           = 0;
    nume_site *site = malloc(capacitate*sizeof( nume_site));
    nume_site *are_cuv_cheie;
    FILE *fr        = fopen("master1.txt","r");
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
             
    initscr();//initalizare ecran,seteaza memorie,curata ecranul
    noecho();   //nu pot scrie
    cbreak();
    int height,width, start_y,start_x;
    height = 20;
    width = 40;
    start_x = start_y = 10;
    WINDOW *win = newwin(height, width,start_y,start_x); //declar o fereastra de dimensiunile precizate
    refresh();
    box( win, 0 , 0);   //creez fereastra
    mvwprintw(win,1,10,"Browserul lui Biju");       //printez legenda pe fereastra
    mvwprintw(win,18,14,"tasta C pentru cautare");
    mvwprintw(win,17,14,"tasta S cautare simpla");
    mvwprintw(win,16,14,"tasta A cautare avansata");
    mvwprintw(win,15,14,"tasat Q inchidere program");
    wrefresh(win);
    //printf("%s",site[i].detalii_continut.titlu);
    int h,w;
    h = 5;
    w = 21;
    WINDOW *search_bar=newwin(h,w,15,20);   //initializez fereastra pt search-bar
    char string[200];
    char copie_string[200];
    while (1)
    {   char c = getch();       //iau prima tasta
        if (c == 'c')       //daca tasta este C
        {   
            box(search_bar, 0, 0);      //creez search-barul
            wrefresh(search_bar);       //refresh ca sa apara
            wmove(search_bar,1,2);      //mut mouse-ul in searchbar
            echo();                     //activez sccrierea
            wgetstr(search_bar,string); //salevz ce se scrie in string
            strcpy(copie_string,string);    //fac copie la string
            noecho();
            c = getch();
              if ( c == 's')
              {
                   cautare_simpla(site,are_cuv_cheie,cuv_cheie,cnr_site,&k,&nr_cuv,capacitate,copie_string); //fac cautare simpla
                   next_page(string,k,are_cuv_cheie);                                                        //pt stringul scris
                
                refresh();
                c = getch();                //daca urmatoarea tasta apasata este q=>inchide fereastra
                    if( c == 'q')
                        endwin();
              }
              
              if ( c == 'a')
              {
                   cautare_avansata(site,are_cuv_cheie,cuv_cheie,cnr_site,&k,&nr_cuv,capacitate,copie_string);//cautare avansata
                   next_page(string,k,are_cuv_cheie);                                                         //pt stringul scris
                
                refresh();
                c = getch();
                    if( c == 'q')        //daca urmatoarea tasta apasata este q=>inchide fereastra
                        endwin();
              }
        }
        else
            if( c == 'q')            //daca urmatoarea tasta apasata este q=>inchide fereastra
                endwin();
        c = getch();                
    }

    endwin();//elibereaza memoria si inchide ncurses

    
    return 0;
}
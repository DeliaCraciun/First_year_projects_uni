#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

typedef struct node {           
    int *timestamp;
    double *value;
    struct node *next;
    struct node *prev;
} node_t;

typedef struct dl_list {
    node_t *head;
    node_t *tail;
    int numarPerechi;
} list_t;

list_t *init_list() {
    list_t *new_list = malloc(sizeof(list_t));

    new_list->head = NULL;
    new_list->tail = NULL;
    new_list->numarPerechi = 0;

    return new_list;
}
node_t * init_node(int timestamp, double value) {
    node_t *new_node = malloc(sizeof(node_t));

    new_node->value = malloc(sizeof(double));
    new_node->timestamp = malloc(sizeof(int));
    *new_node->value = value;
    *new_node->timestamp = timestamp;

    new_node->next = NULL;
    new_node->prev = NULL;

    return new_node;
}
void free_node(node_t *nod)
{
    free(nod->value);
    free(nod->timestamp);
    free(nod);
}

void destroy_list(list_t *list) {
    node_t *aux;

    while (list->numarPerechi > 0) {
        aux = list->tail;                   
        list->tail = list->tail->prev;     
        free_node(aux);            
        --list->numarPerechi;              
    }

    free(list);
}

int insert_node(list_t *list, int position, node_t *nod) {


    if( position < 0 || position > list->numarPerechi)
        return -1;

    if(list->numarPerechi == 0)
    {
        list->tail = nod;
        list->head = nod;
        list->numarPerechi ++;

        return 0;
    }

    if( position == 0)
    {   
        nod->next = list->head;
        nod->prev = NULL;
        nod->next->prev = nod;
        list->head = nod;
        list->numarPerechi ++;
     
        return 0;
    }
   
    if( position == list->numarPerechi)
    {
        nod->prev = list->tail;
        nod->prev->next = nod;
        list->tail  = nod;
        list->numarPerechi ++;

        return 0;
    }

    node_t *x = list->head;
    int i;

    if(position < (list->numarPerechi/2) - 1)
    {
        for(i = 0; i < position; i++)
        {
            x = x->next;
        }
        nod->prev = x->prev;
        nod->next = x;
        nod->prev->next = nod;
        x->prev   = nod;
    }
    else
    {   x = list->tail;
        for( i = list->numarPerechi - 1; i > position; i--)
        {
            x = x->prev;
        }
        nod->prev = x->prev;
        nod->next = x;
        nod->prev->next = nod;
        x->prev   = nod;
    }

    list->numarPerechi ++;
    return 0;
}
int remove_node(list_t *list, int position) {

    node_t *x = list->head;
    node_t *aux;
    int i;

    if( position < 0 || position > list->numarPerechi -1 || list->numarPerechi == 0)
        return -1;
    
    if( position == 0 )
    {
        x->next->prev    = NULL;
        list->head = x->next;
        free(x);
        list->numarPerechi --;
        return 0;
    }

    x = list->tail;

    if( position == list->numarPerechi - 1)
    {
        x->prev->next = NULL;
        list->tail = x->prev;
        free(x);
        list->numarPerechi --;
        return 0;
    }

    if( position < list->numarPerechi/2 - 1)
    {   
        aux = list->head;
        for( i = 0; i < position; i++)
            aux = aux->next;
        aux->prev->next = aux->next;
        aux->next->prev = aux->prev;
      
        free(aux);

    }
    else
    {
        aux = list->tail;
        for( i = list->numarPerechi; i > position; i--)
            aux = aux->prev;
        
        aux->prev->next = aux->next;
        aux->next->prev = aux->prev;
        free(aux);
    }
    
    list->numarPerechi --;
    return 0;
}

int sorted_list(list_t *list, double value, int timestamp)
{
    node_t *nod = init_node(timestamp,value);
    node_t *aux;
    node_t *x;

    if( list->numarPerechi == 0)
    {
        list->tail = nod;
        list->head = nod;
        list->numarPerechi ++;
        return 0;
    }

    if( value <= *list->head->value)
    {
        nod->next = list->head;
        nod->next->prev = nod;
        nod->prev = NULL;
        list->head = nod;

        list->numarPerechi ++;
        return 0;
    }

    if( value >= *list->tail->value)
    {
        nod->prev = list->tail;
        nod->prev->next = nod;
        nod->next = NULL;
        list->tail = nod;

        list->numarPerechi ++;
        return 0;
    }

    for( x = list->head; x->next != NULL; x = x->next)
    {   if( x == NULL || x->next == NULL) 
            printf("Mem leak la sortare");
        if( *(x->value) <= value && *(x->next->value) >= value)
        {
            nod->prev = x;
            nod->next = x->next;
            x->next = nod;

            if( nod->next != NULL)
                nod->next->prev = nod;
            
            list->numarPerechi++;
            return 0; 
        }
    }

    return 0;
}
int sorted_list_timestamp(list_t *list, double value, int timestamp)
{
    node_t *nod = init_node(timestamp,value);
    node_t *aux;
    node_t *x;

    if( list->numarPerechi == 0)
    {
        list->tail = nod;
        list->head = nod;
       
        list->numarPerechi ++;
        return 0;
    }

    if( timestamp <= *list->head->timestamp)
    {
        nod->next = list->head;
        nod->next->prev = nod;
        nod->prev = NULL;
        list->head = nod;

        list->numarPerechi ++;
        return 0;
    }

    if( timestamp >= *list->tail->timestamp)
    {
        nod->prev = list->tail;
        nod->prev->next = nod;
        nod->next = NULL;
        list->tail = nod;

        list->numarPerechi ++;
        return 0;
    }

    for( x = list->head; x->next != NULL; x = x->next)
    {   if( x == NULL || x->next == NULL) 
            printf("Mem leak la sortare");
        if( *(x->timestamp) <= timestamp && *(x->next->timestamp) >= timestamp)
        {
            nod->prev = x;
            nod->next = x->next;
            x->next = nod;

            if( nod->next != NULL)
                nod->next->prev = nod;
            
            list->numarPerechi++;
            return 0;      
        }
    }
    return 0;
}

list_t *statistici(list_t *list, int k)
{
    int n = 0;
    int k_cp = k;
    int i,j;
    int x = 0;
    double s = 0;
    double s_patrate = 0;
    double medie = 0;
    double deviatie = 0;
    node_t *nod;
    node_t *aux;
    node_t *first_node = list->head;
    node_t *nod_bun;
    list_t *lista_buna = init_list();

    aux = first_node;

    while( n < k/2 )
    {
        nod = init_node(*(aux->timestamp), *(aux->value));
        aux = aux->next;
        insert_node(lista_buna, lista_buna->numarPerechi , nod);
        n++;

    } 

    n = 0;

    while( n != list->numarPerechi - 4 )
    {   
        s = 0;
        s_patrate = 0;
        nod = first_node;
      
        for( i = 0; i < k; i++ )
        {
            s = s + *(nod->value);
            nod = nod->next;
        }
    
        nod = first_node;
        medie = s / k_cp;

        for( i = 0; i < k; i++ )
        {
            s_patrate += pow(medie - *(nod->value), 2);
            nod = nod->next;
        }

        deviatie = sqrt( s_patrate / k_cp);
        nod = first_node;

       for( i = 0; i < k/2 ; i++)
           nod = nod->next;

       if( *(nod->value) >= (medie - deviatie) && *(nod->value) <= (medie + deviatie) )
       {
           nod_bun = init_node(*(nod->timestamp),*(nod->value) );
           insert_node(lista_buna, lista_buna->numarPerechi, nod_bun);
       }
       else
        {   
            ;
        }

       first_node = first_node->next;
       n++;
    }

    n = 0;
    aux = first_node->next->next;

    while( n < k/2 )
    {
        nod = init_node(*(aux->timestamp), *(aux->value));
        aux = aux->next;
        insert_node(lista_buna, lista_buna->numarPerechi , nod);

        n++;

    } 

    destroy_list(list);
    return lista_buna;

}

list_t *filtrare_mediana(list_t *list,int k)
{   
    list_t *tms = init_list();
    list_t *sortat_tms;
    node_t *nod = list->head;
    node_t *first_node = list->head;
    node_t *aux;
    int n = 0;
    int i;

    while( n != list->numarPerechi - 4 )
    {   sortat_tms = init_list();
        int timp_vechi = *nod->next->next->timestamp;
        for( i = 0; i < k; i++ )    //trimit fiecare elem  ca sa l bag intr o noua lista sortata
        {
            sorted_list(sortat_tms,*(nod->value), *(nod->timestamp));
            nod = nod->next;
        }
    
    aux = init_node(timp_vechi, *sortat_tms->head->next->next->value);
    insert_node(tms,n,aux);
    destroy_list(sortat_tms);

    first_node = first_node->next;
    nod = first_node; 
    n++;

    }

    destroy_list(list);
    return tms;
    
}
list_t *filtarre_medie_aritmetica(list_t *list, int k)
{
    node_t *first_node = list->head;
    node_t *nod = list->head;
    list_t *medii = init_list();
    double suma = 0;
    double medie = 0;
    int n = 0;
    int i;

    while( n!= list->numarPerechi - 4)
    {
        int timestamp = *first_node->next->next->timestamp;
        suma = 0;
        for( i = 0; i < k; i++)
        {
            suma = suma + *nod->value;
            nod = nod->next;
        }
        medie = suma / k;
        node_t *aux = init_node(timestamp,medie);
        insert_node(medii, n, aux);
        first_node = first_node->next;
        nod = first_node;
        n++;
    }

    destroy_list(list);
    return medii;

}
void uniformizare(list_t *list)
{
    node_t *nod;
    node_t *x;
    int tmsp;
    double val;

    for( x = list->head->next; x != NULL; x = x->next)
    {
        if( (*x->timestamp - *x->prev->timestamp) <= 1000 && (*x->timestamp - *x->prev->timestamp) >= 100)
        {
            tmsp = ( *x->timestamp + *x->prev->timestamp)/2;
            val = ( *x->value + *x->prev->value)/2;
            *x->value = val;
            *x->timestamp = tmsp;
        }

    }

}

void completare_date(list_t *list, int k)
{
    node_t *nod = list->head;
    node_t *x;
    node_t *aux;
    double C;
    double T;
    double W0 = 0;
    double W1 = 0;
    double W2 = 0;
    double numitor0 = 0;
    double numitor1 = 0;
    double numitor2 = 0;
    double suma_left = 0;
    double suma_right = 0;
    int i,j;
    int ok = 0;

        double numarator0 = pow(0,2)*0.9 + 0.1;
        double numarator1 = pow(0.5,2)*0.9 + 0.1;
        double numarator2 = pow(1,2)*0.9 + 0.1;

        for( j = 0; j < k; j++)
        {   if( j == 0)
                numitor0 = numitor0 + pow(0,2)*0.9 + 0.1;
            if( j == 1 )
                numitor0 = numitor0 + pow(0.5,2)*0.9 + 0.1;

            if( j == 2)
                numitor0 = numitor0 + pow(1,2)*0.9 + 0.1;

        }

        W0 = (numarator0/numitor0);
        W1 = (numarator1/(numitor0));
        W2 = (numarator2/numitor0);
    

    int cont = 0;
    x = list->head;

    while( x->next != NULL )
    {          
        if( (*x->next->timestamp - *x->timestamp) > 1000 )
        {   int tmp_vechi = *x->next->timestamp;
            double val0 = *x->prev->prev->value * W0;
            double val1 = *x->prev->value * W1;
            double val2 = *x->value * W2;
            double val0_1 = *x->next->next->next->value * W0;
            double val1_1 = *x->next->next->value * W1;
            double val2_1 = *x->next->value * W2;
            double left   = *x->timestamp;
            double right  = *x->next->timestamp;
            node_t *auxx = x->next;

            while( (tmp_vechi- *x->timestamp ) > 200)
            {
                T = *x->timestamp + 200;
                C = ( (T - left)/(right - left) );
                suma_left = (1 - C)*(val0 + val1 + val2);
                suma_right = C*(val0_1 + val1_1 + val2_1);
                aux = init_node(T,suma_left + suma_right);
                insert_node(list,cont + 1,aux);
                suma_left = suma_right = 0;
                x = x->next;
                cont++;
            }
            cont++;
            x = auxx;
        }
        else
        {
            x = x->next;
            cont++;
        }

    }

}

int statistici_st(list_t *list, int delta)
{
    node_t *x;
    list_t *Lista_sortata = init_list();
    int i;
    int right;
    int left;
    int max;

    for( x = list->head; x != NULL; x = x->next)
        sorted_list(Lista_sortata,*x->value,*x->timestamp);
    
    x = Lista_sortata->head;
    left = (int)((*Lista_sortata->head->value)/delta ) * delta - delta;
    right = left + delta;
    max = (int)(*Lista_sortata->tail->value / delta)*delta + delta;

    while ( max != left)
    {
        int cont = 0;
        for( x = Lista_sortata->head; x != NULL; x = x->next)
        {
            if(*x->value >= left && *x->value <= right)
                cont++;
        }

        if(cont != 0 )
        { 
        printf("[%d, %d] ",left,right);
        printf("%d\n",cont);
        }

        right = right + delta;
        left = left + delta;
    }

    destroy_list(Lista_sortata); 
    return 0;
}

int main(int argc, char **argv)
{   
    int i;
    int k = 5;
    int position = 0;
    int numarPerechi;
    list_t *list = init_list();
    node_t *nod;
    double value;
    int timestamp;

    scanf("%d ", &numarPerechi);

    for( i = 0; i < numarPerechi; i++ )
    {
        scanf("%d %lf",&timestamp,&value);
        nod = init_node(timestamp,value);
        insert_node(list, position , nod);
        position ++;  
    }

int j;
int ok = 0;
 
    for(i = 1; i < argc; i++)
    {
        
        if( strcmp(argv[i],"--e1") == 0)
        {
            list = statistici(list,5);
            ok = 0;
        }
        
        if(strcmp(argv[i],"--e2") == 0)
        {   
         list = filtrare_mediana(list,5);
         ok = 0;
        }
        
        if( strcmp(argv[i],"--e3") == 0)
        {
            list = filtarre_medie_aritmetica(list,5);
            ok = 0;
        }
        if(strcmp(argv[i],"--u") == 0)
        {
            uniformizare(list);
            ok = 0;
        }
        if(strcmp(argv[i],"--c") == 0)
        {
            completare_date(list,k);
            ok = 0;
        }
        if( strstr(argv[i],"--st") != NULL)
        {
            int x;
            int nr = 0;
            for(x = 4; x < strlen(argv[i]); x++)
            {
                nr = nr*10 + (argv[i][x] - '0');
            }
            statistici_st(list,nr);
            ok = 8;  

        }
    }

    if( ok == 0)
    {  
        nod = list->head;
        printf("%d\n", list->numarPerechi);

        for( j = 0; j < list->numarPerechi; j++)
        {
            printf("%d %.2lf\n",*(nod->timestamp),*(nod->value));
            nod = nod->next; 
        } 
    }
    destroy_list(list);

    return 0;
}
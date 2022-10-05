#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>

#define INF 100000

int32_t char_to_int32(char *string)
{   
    int i = 0;
    int32_t nr = 0;
    while( string[i] != '\0' && string[i] >= 48 && string[i] <= 57)
    {
        nr = nr * 10 + (string[i] - '0');
        i++;
    }
    return nr;
}
void free_task1_2(double ***graph, double ***graph1, int **pred_dus, int **pred_intoarcere, int n)
{
    int i;

    free(*pred_intoarcere);
    free(*pred_dus);

    for(i = 0; i < n; i++)
    {
        free((*graph)[i]);
        free((*graph1)[i]);
    }
    free(*graph);
    free(*graph1);
}

void printPath(int parent[], int j, int destinaton,int src)
{
    if ( j == -1)
        return;
    
    printPath(parent, parent[j],destinaton,src);
    printf(" %d", j);
}

double dijkstra(double **Graph,int nr_nodes,int src_deposit,int dest_deposit,int **pred_dus,int **pred_intoarcere,int *a)
{
    int i,j;
    int loop_times = 0;
    int cont = src_deposit;
    int pred[100] = {-1};
    double dist_min;
    int i_min;
    double dist[nr_nodes];
    int vis[nr_nodes];

    for(i = 0; i < nr_nodes; i++)
    {
        dist[i] = INF;
        vis[i]  = 0;

        if( *a == 0)
        {
            (*pred_dus)[i] = -1;
        }
        else
        {
            (*pred_intoarcere)[i] = -1;
        }
    }

    dist[src_deposit] = 0;
    vis[src_deposit]  = 1;

    for(i = 0; i < nr_nodes; i++)
    {
        if(Graph[src_deposit][i] != 0)
        {
            dist[i] = Graph[src_deposit][i];
        }
    }

    while( vis[dest_deposit] != 1)
    {
        dist_min = INF;
        
        for(i = 0; i < nr_nodes ; i++)
        {
            if( vis[i] == 0 && dist_min > dist[i])      //am identificat distanta minima de la nodul i
            {                                           
                dist_min = dist[i];
                i_min    = i;

            }
        }

        vis[i_min] = 1;     //notam ca vizitat

        for( i = 0; i < nr_nodes ; i++)
        {
            
            if( ( dist[i] > (dist[i_min] + Graph[i_min][i]) ) && Graph[i_min][i] != 0 && vis[i] == 0)
            {
                dist[i] = dist[i_min] + Graph[i_min][i];

                if( *a == 0)                //0 pentru drumul de dus
                {
                    (*pred_dus)[i] = i_min;
                }
                if( *a == 1)                //1 pentru drumul de intoarcere
                {
                        (*pred_intoarcere)[i] = i_min;
                }
                cont = i_min;
            }
        }  
    }

   return dist[dest_deposit];

}



void df1(double **graph,int nod,int **vis1, int nr_nodes)
{
    int i;
    (*vis1)[nod] = 1;

    for(i = 0; i < nr_nodes; i++)
    {
        if(graph[i][nod] != 0 && (*vis1)[i] == 0 )
        {
            df1(graph,i,vis1,nr_nodes);
        }
    }
}
void df2(double **graph,int nod,int **vis2, int nr_nodes)
{
    int i,j;

    (*vis2)[nod] = 1;

    for(i = 0; i < nr_nodes; i++)
    {
        if(graph[nod][i] != 0 && (*vis2)[i] == 0 )
        {
            df2(graph,i,vis2,nr_nodes);
        }
    }
}

int exist(int *v, int nr, int n)
{
    int i;

    for(i = 0; i < n; i++)
    {
        if(v[i] == nr)
        {
            return 1;
        }
    }

    return 0;
}

void kosaraju(double **graph,int nr_nodes,int *deposit,int nr_depo)
{
    int i,j;
    int conex_comp = 0;
    int *vis = malloc(nr_nodes * sizeof(int) );
    int *vis1= malloc(nr_nodes * sizeof(int) );
    int *vis2= malloc(nr_nodes * sizeof(int) );
    int scc[nr_nodes];

    for(i = 0; i < nr_nodes; i++)
    {
        vis[i] = 0;
        scc[i] = -1;
    }

    for(i = 0; i < nr_nodes; i++)
    {
        if(scc[i] == -1)
        {
            conex_comp++;

            for(j = 0; j < nr_nodes; j++)       //inainte de o cautare a unei comp tare conexe
            {                                   //refac vectorii de vizitat
                vis1[j] = vis2[j] = 0;
            }
            // vis1[deposit] = 1;
            // vis2[deposit] = 1;

            if(exist(deposit,i,nr_depo) == 1)
            {
                conex_comp--;
            }
            else
            {
                df1(graph,i,&vis1,nr_nodes);
                df2(graph,i,&vis2,nr_nodes);
            }

            for(j = 0; j < nr_nodes; j++)
            {
                if(vis1[j] == vis2[j] && vis1[j] != 0)
                {
                    scc[j] = conex_comp;
                    vis[j] = conex_comp;
                }
            }
        }
    }

    int afisare = 0;
    printf("%d\n",conex_comp);
    for(i = 1; i <= conex_comp; i++)
    {
        for(j = 0; j < nr_nodes; j++)
        {
            if(scc[j] == i)
            {
                if( afisare == 0)
                {
                    printf("%d",j);
                }
                else
                {
                    printf(" %d",j);
                }
                 
                afisare++;
            }
        }

        afisare = 0;

        if( i != conex_comp )
        {
            printf("\n");
        }
    }

    free(vis);
    free(vis1);
    free(vis2);

}


int main()
{   
    char buffer[100];
    double total_cost = 0;
    int i, j;
    int nr_nodes;
    int  arches;
    int nr_deposits;
    int src_node, dest_node;
    double price;
    char deposits[100];
    int nr_tasks;
    int src_deposit;
    int nr_shops;
    int ID_s[50];
    char task[5];
    double **graph;
    double **copie_graph;

    scanf("%d %d %d",&nr_nodes,&arches,&nr_deposits);
    scanf("%c",&buffer[0]);
    int *pred_dus = malloc(nr_nodes * sizeof(int));
    int *pred_intoarcere = malloc(nr_nodes * sizeof(int));
    graph = malloc(nr_nodes * sizeof(double*) );
    copie_graph = malloc(nr_nodes * sizeof(double*) );

    for( i = 0; i < nr_nodes; i ++)
    {
       graph[i] = malloc( nr_nodes * sizeof(double) );
       copie_graph[i] = malloc( nr_nodes * sizeof(double) );
    }

    if( graph == NULL)
    {
        printf("Graph without memory");
        return 0;
    }
    for(i = 0; i < nr_nodes; i++)
        {
            for(j = 0; j < nr_nodes; j ++)
            {
                graph[i][j] = 0;
                copie_graph[i][j] = 0;
            }
    
        }

    for( i = 0; i < arches; i++)
    {
        scanf("%d %d %lf",&src_node,&dest_node,&price);
        scanf("%c",&buffer[0]);
        graph[src_node][dest_node] = price;
        copie_graph[src_node][dest_node] = price;
    }

    fgets(deposits,100,stdin);
    scanf("%d",&nr_tasks);
    scanf("%c",&buffer[0]);

    for(j = 0; j < nr_tasks; j++)
    {
        scanf("%s",task);

        if( strcmp("e1",task) == 0)
        {
            scanf("%d",&src_deposit);
            scanf("%d",&nr_shops);
     
            for(i = 0; i < nr_shops; i++)
            {
                scanf("%d",&ID_s[i]);
            }

        }

        if( strcmp("e1",task) == 0)
        {
            total_cost = 0;

            for(i = 0; i < nr_shops; i++)
            {   
                double to = 0;
                double back = 0;
                int loop_times = 0;

                printf("%d\n",ID_s[i]);

                to = dijkstra(graph,nr_nodes,src_deposit,ID_s[i],&pred_dus,&pred_intoarcere,&loop_times);

                loop_times++;
                
                back = dijkstra(graph,nr_nodes,ID_s[i],src_deposit,&pred_dus,&pred_intoarcere,&loop_times);

                printf("%.1lf %.1lf\n",to,back);

                total_cost = total_cost + to + back;
                loop_times = 0;

                printf("%d",src_deposit);
                printPath(pred_dus,ID_s[i],ID_s[i],src_deposit);

                loop_times = 0;

                printPath(pred_intoarcere,src_deposit,src_deposit,ID_s[i]);
                printf("\n");
            }

            if( j == nr_tasks -1)
            {
                printf("%.1lf",total_cost);
            }
            else
            {
                printf("%.1lf\n",total_cost);
            }
            

        }

        if( strcmp(task,"e2") == 0)
        {
            char *token = strtok(deposits," ");
            char cuv[50];
            int v_depo[100];
            int cont = 0;

            while(token != NULL)
            {   
                strcpy(cuv,token);
                v_depo[cont] = char_to_int32(cuv);

                cont++;
                token = strtok(NULL," ");

            }
            for(i = 0; i < cont ; i++)
            {
                for(j = 0; j < nr_nodes; j++)
                {
                    copie_graph[v_depo[i]][j] = 0;
                    copie_graph[j][v_depo[i]] = 0;
                }
            }
            
            kosaraju(copie_graph,nr_nodes,v_depo,cont);
            
        }

    }

    free_task1_2(&graph,&copie_graph,&pred_dus,&pred_intoarcere,nr_nodes);

}
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <stdlib.h>
#include <math.h>


#pragma pack(1)
typedef struct QuadtreeNode
{
    unsigned char blue, green, red;
    uint32_t area;
    int32_t top_left, top_right;
    int32_t bottom_left, bottom_right;
} QuadtreeNode;
#pragma pack(1)
typedef struct Quadtree
{
    QuadtreeNode *data; // 23

    long long int index;
    struct Quadtree *topLeftTree;
    struct Quadtree *topRightTree;
    struct Quadtree *bottomRightTree;
    struct Quadtree *bottomLeftTree;
} Quadtree;
#pragma pack(1)
typedef struct culori
{
    unsigned char red, green, blue;
} culori;

void create_vector(QuadtreeNode **tree_vect, Quadtree *node,int *indice)
{
   // printf("NODUL MEU %d\n",node->data->red);
    if( node != NULL)
    {    
      //imi umplu campurile din vector
    //if( node->topLeftTree != NULL && node->topRightTree != NULL  && node->bottomRightTree != NULL &&  node->bottomLeftTree != NULL)
    {
        (*tree_vect)[*indice].area  = node->data->area;
        (*tree_vect)[*indice].blue  = node->data->blue;
        (*tree_vect)[*indice].red   = node->data->red;
        (*tree_vect)[*indice].green = node->data->green;
    }

    if( node->topLeftTree != NULL )    //nodul la cre ma aflu 
    {
        (*tree_vect)[*indice].top_left = node->topLeftTree->index;
    }
    else
    {
        (*tree_vect)[*indice].top_left = -1; 
     
        
    }
        if( node->topRightTree != NULL )    //nodul la cre ma aflu 
    {
        (*tree_vect)[*indice].top_right = node->topRightTree->index; 
        //printf(" ADRESA NOD TR %p Adresa 1/4 %p Adresa frunza \n",node,node->topRightTree,node->topRightTree->topRightTree);
    }
    else
    {
        (*tree_vect)[*indice].top_right = -1;
    
        
    }

        if( node->bottomRightTree != NULL )    //nodul la cre ma aflu 
    {
        (*tree_vect)[*indice].bottom_right = node->bottomRightTree->index; 
        //printf("Adresa nod BR %p Adresa 1/4  %p Adresa frunza %p\n",node, node->bottomRightTree, node->bottomRightTree->bottomLeftTree);
    }
    else
    {
        (*tree_vect)[*indice].bottom_right = -1;           //segm fault   
   
    }

        if( node->bottomLeftTree != NULL )    //nodul la cre ma aflu 
    {
        (*tree_vect)[*indice].bottom_left = node->bottomLeftTree->index;  
    }
    else
    {   
        (*tree_vect)[*indice].bottom_left = -1;  //segm fault
         
       // printf("da");
        
    }


    (*indice)++;

    create_vector(&(*tree_vect), node->topLeftTree , indice);
    create_vector(&(*tree_vect), node->topRightTree , indice);
    create_vector(&(*tree_vect), node->bottomRightTree , indice);
    create_vector(&(*tree_vect), node->bottomLeftTree , indice);
    
    }
   
    return;
}

void make_tree(culori **mat, int point_x, int point_y, Quadtree **node, double factor, uint32_t *nr_apeluri, uint32_t *frunze)
{
//    printf("Nr. parcurgeri facute: %d\n", *nr_apeluri);
    unsigned char m_blue, m_green, m_red;
    unsigned long long int s_blue = 0, s_green = 0, s_red = 0;
    int i, j;
    int width, height;
    unsigned long long int mean = 0;

    (*nr_apeluri)++;

    (*node)->topLeftTree = malloc(sizeof(Quadtree));
    (*node)->topLeftTree->data = malloc(sizeof(QuadtreeNode));
    (*node)->topRightTree = malloc(sizeof(Quadtree));
    (*node)->topRightTree->data = malloc(sizeof(QuadtreeNode));
    (*node)->bottomLeftTree = malloc(sizeof(Quadtree));
    (*node)->bottomLeftTree->data = malloc(sizeof(QuadtreeNode));
    (*node)->bottomRightTree = malloc(sizeof(Quadtree));
    (*node)->bottomRightTree->data = malloc(sizeof(QuadtreeNode));

    width = height = sqrt((*node)->data->area);
//    printf("%d %d\n",width, height);
    for (j = point_y; j < point_y + height; j++)
    {
        for (i = point_x; i < point_x + width; i++)
        {
            s_blue += (mat[i][j].blue);
            s_green += (mat[i][j].green);
            s_red += (mat[i][j].red);
        }
    }

    (*node)->data->blue = s_blue / ((*node)->data->area);
    (*node)->data->green = s_green / ((*node)->data->area);
    (*node)->data->red = s_red / ((*node)->data->area);
    // printf("Red: %d ", (*node)->data->red );
    // printf("Green: %d ", (*node)->data->green );
    // printf("Blue: %d\n", (*node)->data->blue);
    // printf("Aria: %d\n", (*node)->data->area);
    // printf("\n");

    for (j = point_y; j < point_y + height; j++)
    {
        //  printf("aScds\n");
        for (i = point_x; i < point_x + width; i++)
        {
            mean +=( (*node)->data->red - mat[i][j].red) *((*node)->data->red - mat[i][j].red)+
                 +( (*node)->data->green - mat[i][j].green)* ((*node)->data->green - mat[i][j].green)+ 
                   ( (*node)->data->blue - mat[i][j].blue) * ( (*node)->data->blue - mat[i][j].blue );
        }
    }
    
    unsigned long long int mean_f = mean / (3 * width * height);
//    printf("MEAN %lld MEAN_F %lld\n ", mean, mean_f);
    if (mean_f <= factor)
    {
        (*node)->index = *nr_apeluri - 1;
        *frunze += 4;
        (*node)->bottomLeftTree = NULL;
        (*node)->bottomRightTree = NULL;
        (*node)->topLeftTree = NULL;
        (*node)->topRightTree = NULL;
        (*node)->data->bottom_left = -1;
        (*node)->data->bottom_right = -1;
        (*node)->data->top_left = -1;
        (*node)->data->top_right = -1;

        return;
    }
    else
    {
        uint32_t arie = (*node)->data->area / 4;

        (*node)->index = *nr_apeluri - 1;
        (*node)->topLeftTree->data->area = arie;
        (*node)->topRightTree->data->area = arie;
        (*node)->bottomRightTree->data->area = arie;
        (*node)->bottomLeftTree->data->area = arie;

        make_tree(mat, point_x, point_y, &(*node)->topLeftTree, factor, nr_apeluri, frunze);
        make_tree(mat, point_x, point_y + width / 2, &(*node)->topRightTree, factor, nr_apeluri, frunze);
        make_tree(mat, point_x + height / 2, point_y + width / 2, &(*node)->bottomRightTree, factor, nr_apeluri, frunze);
        make_tree(mat, point_x + height / 2, point_y, &(*node)->bottomLeftTree, factor, nr_apeluri, frunze);

        
        // printf("da");
        return;
    }
     
}
void free_tree(Quadtree **root) {
    if (*root == NULL) {
        return;
    }

    free_tree(&(*root)->topLeftTree);
    free_tree(&(*root)->topRightTree);
    free_tree(&(*root)->bottomRightTree);
    free_tree(&(*root)->bottomLeftTree);

    // Sterg nodul curent
    free((*root)->data);
    free(*root);

    *root = NULL;
}


Quadtree *vector_to_tree(QuadtreeNode *vect, int i, int nr_nodes)
{
    Quadtree *aux = malloc(sizeof(Quadtree));
    aux->data     = malloc( sizeof(QuadtreeNode));
   if( i < nr_nodes)
   {
    //pun in aauxiliar datele din vector
    aux->index = i;
    aux->data->area         = vect[i].area;
    aux->data->blue         = vect[i].blue;
    aux->data->red          = vect[i].red;
    aux->data->green        = vect[i].green;
    aux->data->top_left     = vect[i].top_left;
    aux->data->top_right    = vect[i].top_right;
    aux->data->bottom_right = vect[i].bottom_right;
    aux->data->top_left     = vect[i].bottom_left;
    //root = aux;
    //printf("%d\n",i);
    if( vect[i].top_left == -1 && vect[i].top_right == -1 && vect[i].bottom_right == -1 && vect[i].bottom_left == -1)
    {
        //printf("INDICE:%lld RED: %d GREEN: %d ALBASTRU %d\n",aux->index ,aux->data->red, aux->data->green, aux->data->blue);
        aux->data->bottom_left = -1;
        aux->data->bottom_right = -1;
        aux->data->top_left = -1;
        aux->data->top_right = -1;
        aux->bottomLeftTree = NULL;
        aux->bottomRightTree = NULL;
        aux->topLeftTree = NULL;
        aux->topRightTree = NULL;
        //root = aux;
    }
    else
    {   
        //printf("INDICE %lld RED: %d GREEN: %d ALBASTRU %d\n", aux->index,aux->data->red, aux->data->green, aux->data->blue);
        aux->topLeftTree = vector_to_tree(vect, vect[i].top_left, nr_nodes);
        aux->topRightTree = vector_to_tree(vect, vect[i].top_right, nr_nodes);
        aux->bottomRightTree = vector_to_tree(vect, vect[i].bottom_right, nr_nodes);
        aux->bottomLeftTree = vector_to_tree(vect, vect[i].bottom_left, nr_nodes);

    }

   }
   return aux;


}

int main(int argc, char **argv)
{
    char s[5];
    char line[30];
    char buffer;
    int height, width;
    int max_col;
    int i, j;
    culori **mat;

    // printf("Height:%d Width:%d\n", height, width);

    int modul;


    // printf("Zona 1: Red: %d Green: %d Blue: %d   ", mat[1][1].red , mat[1][1].green , mat[1][1].blue );
    // printf("Zona 2: Red: %d Green: %d Blue: %d\n", mat[1][250].red , mat[1][250].green , mat[1][250].blue );
    // printf("Zona 3: Red: %d Green: %d Blue: %d   ", mat[123][20].red , mat[250][1].green , mat[250][1].blue );
    // printf("Zona 4: Red: %d Green: %d Blue: %d   ", mat[250][250].red , mat[250][250].green , mat[250][250].blue );

     if (strcmp(argv[1], "-c") == 0)
    {
        FILE *fb = fopen(argv[3], "rb");
        FILE *fb_w = fopen(argv[4],"wb");
        uint32_t nr_apeluri = 0;
        int index_vector = 0;
        uint32_t culori = 0;
        double factor = atoi(argv[2]);
        Quadtree *root = malloc(sizeof(Quadtree)); // alocare memorie root
        QuadtreeNode *vector_nodes = NULL;
        
        fscanf(fb, "%s", s);
        fscanf(fb, "%d %d", &height, &width);
        fscanf(fb, "%d", &max_col);
        fscanf(fb, "%c", &buffer);

        mat = malloc(height * sizeof(*mat));
        for (i = 0; i < height; i++)
            mat[i] = malloc(width * sizeof(mat));

        if (mat == NULL)
            printf("Nu s-a alocat memorie");

        for (i = 0; i < height; i++)
            for (j = 0; j < width; j++)
                fread(&mat[i][j], sizeof(**mat), 1, fb);

        root->data = malloc(sizeof(QuadtreeNode));
        root->data->area = width * height;
        
        make_tree(mat, 0, 0, &root, factor, &nr_apeluri, &culori); // apelez functia pornind din coltul de stanga sus
        vector_nodes = malloc( nr_apeluri * sizeof(QuadtreeNode) );

        if( vector_nodes == NULL)
        {
            printf("Vectorul nu a fost alocat");
            return 0;
        }
        create_vector(&vector_nodes, root, &index_vector);
        fwrite(&culori, sizeof(uint32_t), 1, fb_w);
        fwrite(&nr_apeluri, sizeof(uint32_t), 1, fb_w);

        int i;

        for( i = 0; i < nr_apeluri; i++)
        {
            fwrite(&vector_nodes[i], sizeof(QuadtreeNode), 1, fb_w);
            
        }

        //eliberare arbore
        free_tree(&root);
        free(vector_nodes);
        for (i = 0; i < height; i++)
            free(mat[i]);
        free(mat);
        fclose(fb);
        
    }

    else if( strcmp(argv[1], "-d") == 0)
    {
        FILE *fb = fopen(argv[2], "rb");
        FILE *fw = fopen(argv[3],"w");
        FILE *fwb = fopen(argv[3],"wb");
        uint32_t culori;
        uint32_t noduri;
        Quadtree *root = NULL;
        int cont = 0;
        int i,j;
        int width,height;
        //printf("da\n");
        fread(&culori, sizeof(uint32_t), 1, fb);
        fread(&noduri, sizeof(uint32_t), 1, fb);
        QuadtreeNode *vect = (QuadtreeNode *)malloc(sizeof(QuadtreeNode) * noduri );

        for(i = 0; i < noduri; i++)
        {
            fread(&vect[i], sizeof(QuadtreeNode), 1, fb);
           // if(i < 20)
           // printf("INDICE  COPII: %d %d %d %d\n", vect[i].top_left,vect[i].top_right, vect[i].bottom_right, vect[i].bottom_left);
        }

        root = vector_to_tree(vect, 0, noduri);
        width = height = sqrt(root->data->area);
        decompress(&mat, 0, 0, root, &cont);
        //decompression_test(root,&mat,0,0,wi);
        //printf("da\n");
        int x = 255;
        fprintf(fw,"P6\n%d %d\n255\n",height,width);
        for(i = 0; i < height; i++)
        
        { 
              fwrite(mat[i],sizeof(culori), width, fw);
            // for(j = 0; j < width; j++)
            // {
            //      printf("%d %d %d ",mat[i][j].red, mat[i][j].green, mat[i][j].blue);
            // }
            // printf("\n");
         
         }

        for(i = 0; i < height; i++)
        {    for(j = 0; j < width; j++)
            {
                fwrite(&mat[i][j],sizeof(culori),1,fw);
                printf("%d %d %d ",mat[i][j].red, mat[i][j].green, mat[i][j].blue);
            }
                printf("\n");
        }
        //fwrite(&mat,sizeof(culori), width * height, fwb);
        fclose(fwb);
        fclose(fw);
        fclose(fb);

    }


  
}

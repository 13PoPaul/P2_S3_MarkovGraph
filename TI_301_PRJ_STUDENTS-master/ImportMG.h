#include <stdio.h>
#include <stdlib.h>
#include "functions.c"

t_cell* create_cell( int ver, int prob);

t_list* create_empty_list();

t_list* add_cell(t_cell* cell,t_list* list);

typedef struct adjacency_list
{
    int N_Verticies;
    Vertex ** Verticies;
} adjacency_list;

adjacency_list * createEmptyAdjacency_list(int N_Verticies);

adjacency_list readGraph(const char * filename);



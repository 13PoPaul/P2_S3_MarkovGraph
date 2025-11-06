#include <stdio.h>
#include <stdlib.h>

typedef struct adjacency_list
{
    int N_Verticies;
    Vertex ** Verticies;
} adjacency_list;

adjacency_list * createEmptyAdjacency_list(int N_Verticies);

adjacency_list readGraph(const char * filename);



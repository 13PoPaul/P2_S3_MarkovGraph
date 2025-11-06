#include <stdio.h>
#include <stdlib.h>
#include "functions.c"


typedef struct s_cell{
  int vertex;
  double proba;
  struct s_cell* next;
  }t_cell;


typedef struct s_list {
  t_cell* head;
}t_list;


t_cell* create_cell( int ver, double prob);

t_list* create_empty_list();

t_list* add_cell(t_cell* cell,t_list* list);

typedef struct adjacency_list
{
    int N_Verticies;
    t_list ** Verticies;
} adjacency_list;

adjacency_list * createEmptyAdjacency_list(int N_Verticies);

adjacency_list readGraph(const char * filename);

void display_adjency_list(adjency_list *adj);


#include "ImportMG.h"
#include "functions.h"
#include <stdlib.h>


t_cell* create_cell( int ver, int prob){
  t_cell* cell;
  cell = malloc(sizeof(t_cell));
  cell->vertex = ver;
  cell->proba = prob;
  cell->next = NULL;

  return cell;
  }


t_list* create_empty_list() {

  t_list* list = malloc(sizeof(t_list));
  list->head = NULL;

  return list;
}


t_list* add_cell(t_cell* cell,t_list* list) {

  if (list->head == NULL) {
    list->head = cell;
    cell->next = NULL;
  }
  else {
    t_cell* current;
    current = list->head;
    while (current->next != NULL) {
      current = current->next;
    }
    current->next = cell;
    cell->next = NULL;
  }

  return list;
}


adjacency_list * createEmptyAdjacency_list(int N_Verticies)
{
  adjacency_list * ad_list;
  ad_list -> N_Verticies = N_Verticies;
  for (int i = 0; i < N_Verticies ; i++)
  {
        ad_list -> Verticies[i] == NULL;
  }
  return ad_list;
}

adjacency_list readGraph(const char * filename)
{
    FILE *file = fopen(filename, "rt"); // read-only, text
    int nbvert, start, end;
    float proba;
    //declare the variable for the adjacency list
    adjacency_list * M_Graph;
    if (file == NULL)
    {
        perror("Could not open file for reading");
        exit(EXIT_FAILURE);
    }
    // first line contains number of vertices
    if (fscanf(file, "%d", &nbvert) != 1)
    {
        perror("Could not read number of vertices");
        exit(EXIT_FAILURE);
    }
    //use create adjancy list function
    // Initialise an empty adjacency list using the number of vertices
    M_Graph =  createEmptyAdjacency_list(nbvert);
    while (fscanf(file, "%d %d %f", &start, &end, &proba) == 3)
    {
        // we obtain, for each line of the file, the values
        // start, end and proba
        //Add the edge that runs from 'start' to ‘end’ with the
        //probability 'proba' to the adjacency list
        for (int i = 0; i <  nbvert ; i++)
        {

        }
    }
    fclose(file);
    return M_Graph;
}

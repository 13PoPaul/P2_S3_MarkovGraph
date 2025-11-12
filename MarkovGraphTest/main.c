#include <stdio.h>
#include "ImportMG.h"
#include "check.c"
#include "mermaid.h"

int main() {
    printf("Hello, World!\n");
    adjacency_list * M_Graph = readGraph("data/exemple_valid_step3.txt");
    display_adjency_list(M_Graph);
    isMarkovGraph(M_Graph);
    exportToMermaid(M_Graph, "graph_mermaid.txt");
    return 0;
}

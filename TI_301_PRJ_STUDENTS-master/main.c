#include <stdio.h>
#include "ImportMG.h"
#include "check.c"

int main() {
    printf("Hello, World!\n");
    adjacency_list * M_Graph = readGraph("data/exemple1.txt");
    display_adjency_list(M_Graph);
    isMarkovGraph(M_Graph);
    return 0;
}

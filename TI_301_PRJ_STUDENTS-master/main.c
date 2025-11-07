#include <stdio.h>
#include "ImportMG.h"

int main() {
    printf("Hello, World!\n");
    adjacency_list * M_Graph = readGraph("exemple1.txt");
    return 0;
}

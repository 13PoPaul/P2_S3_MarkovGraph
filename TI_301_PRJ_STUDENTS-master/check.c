//
// Created by mathy on 06/11/2025.
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ImportMG.h"

// ---------- Step 2: Check if the graph is a Markov graph ----------

int isMarkovGraph(adjacency_list g) {
    int isMarkov = 1;

    for (int i = 0; i < g.N_Verticies; i++) {
        float sum = 0.0f;
        for (cell *p = g.tab[i].head; p != NULL; p = p->next)
            sum += p->proba;

        if (sum < 0.99f || sum > 1.01f) {
            printf("The sum of probabilities of vertex %d is %.2f\n", i + 1, sum);
            isMarkov = 0;
        }
    }

    if (isMarkov)
        printf("The graph is a Markov graph.\n");
    else
        printf("The graph is NOT a Markov graph.\n");

    return isMarkov;
}

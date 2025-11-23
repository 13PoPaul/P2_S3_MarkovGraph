#include <stdio.h>

int isMarkovGraph(adjacency_list *g) {
    int isMarkov = 1;  // On suppose que le graphe est Markov au départ

    for (int i = 0; i < g->N_Verticies; i++) {
        double sum = 0.0;

        // Parcourir la liste d’adjacence du sommet i
        for (t_cell *p = g->Verticies[i]->head; p != NULL; p = p->next) {
            sum += p->proba;
        }

        // Vérifier si la somme des probabilités est proche de 1
        if (sum < 0.99 || sum > 1.01) {
            printf("The sum of probabilities of vertex %d is %.2f\n", i + 1, sum);
            isMarkov = 0; // Le graphe n’est pas Markov si une somme est incorrecte
        }
    }

    if (isMarkov)
        printf("The graph is a Markov graph.\n");
    else
        printf("The graph is NOT a Markov graph.\n");

    return isMarkov;
}
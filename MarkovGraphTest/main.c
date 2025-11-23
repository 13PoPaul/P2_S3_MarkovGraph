#include <stdio.h>
#include "ImportMG.h"
#include "check.c"
#include "mermaid.h"
#include "part2.h"
#include "part3.h"

int main() {
    adjacency_list * M_Graph = readGraph("data/exemple_meteo.txt");
    display_adjency_list(M_Graph);
    isMarkovGraph(M_Graph);
    exportToMermaid(M_Graph, "graph_mermaid.txt");
    //PART2
    t_list_class * partition = tarjan(M_Graph);
    display_partition(partition);
    printf("\nExporting the Hass Graph into Hass_mermaid.txt");
    t_link_array * hasse_graph = generate_hasse_links(M_Graph, partition);
    export_hasse_mermaid(hasse_graph, partition, "Hass_mermaid.txt");
    display_graph_characteristics(partition, hasse_graph);

    //Gemini
    // --- AJOUT PARTIE 3 (ICI) ---
    printf("\n========================================\n");
    printf("       PART 3: MATRIX & PROBABILITIES     \n");
    printf("========================================\n");

    // 1. Conversion en Matrice
    t_matrix M = adjacencyToMatrix(M_Graph);
    printf("Transition Matrix M:\n");
    displayMatrix(M);

    // 2. Test de Convergence (Calcul de la distribution stationnaire globale)
    printf("\n--- Convergence Test (M^n) ---\n");

    t_matrix M_pow = createEmptyMatrix(M.rows, M.cols);
    t_matrix M_prev = createEmptyMatrix(M.rows, M.cols);
    t_matrix Temp = createEmptyMatrix(M.rows, M.cols);

    // Initialisation M^1
    copyMatrix(M_pow, M);

    int n = 1;
    double diff = 1.0;
    double epsilon = 0.001; // Seuil de précision

    // On multiplie jusqu'à ce que ça ne bouge plus
    while (diff > epsilon && n < 1000) {
        copyMatrix(M_prev, M_pow);          // Sauvegarde l'étape précédente
        multiplyMatrices(M_prev, M, M_pow); // Calcule étape suivante

        diff = diffMatrix(M_pow, M_prev);   // Calcule la différence
        n++;
    }

    printf("Convergence reached at n = %d (diff = %f)\n", n, diff);
    printf("Limit Distribution (first row):\n[ ");
    for(int j=0; j<M.cols; j++) printf("%.4f ", M_pow.data[0][j]);
    printf("]\n");


    // 3. Analyse par Classe (Sous-matrices et Périodicité)
    printf("\n--- Periodicity & Sub-Matrices by Class ---\n");

    t_class * curr = partition->head;
    while (curr != NULL) {
        printf("\nAnalyzing Class %s:\n", curr->name);

        // Extraction de la sous-matrice
        t_matrix sub = subMatrix(M, partition, curr->name);

        if (sub.rows > 0) {
            // displayMatrix(sub); // Décommenter si tu veux voir la sous-matrice

            // Calcul de la période
            int period = getPeriod(sub);
            printf("   -> Period = %d\n", period);

            if (period == 1) printf("   -> Nature: Aperiodic (Regular)\n");
            else printf("   -> Nature: Periodic\n");

            freeMatrix(&sub);
        } else {
            printf("   -> Empty matrix or class not found.\n");
        }

        curr = curr->next;
    }

    // --- NETTOYAGE MEMOIRE ---
    freeMatrix(&M);
    freeMatrix(&M_pow);
    freeMatrix(&M_prev);
    freeMatrix(&Temp);
    return 0;
}

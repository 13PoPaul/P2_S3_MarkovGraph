#include "ImportMG.h"
#include <stdio.h>
#include <stdlib.h>

// Convertit un numéro de sommet (1, 2, 3, …) en une étiquette ("A", "B", …, "Z", "AA", …)
void getId(int num, char *buffer) {
    if (num <= 26) {
        // Cas simple : une seule lettre
        buffer[0] = 'A' + (num - 1);
        buffer[1] = '\0';
    } else {
        // Cas à deux lettres (après 26)
        int first = (num - 1) / 26 - 1;
        int second = (num - 1) % 26;
        buffer[0] = 'A' + first;
        buffer[1] = 'A' + second;
        buffer[2] = '\0';
    }
}

// Exporte la liste d’adjacence dans un fichier texte compatible avec Mermaid
void exportToMermaid(adjacency_list *graph, const char *filename) {
    FILE *f = fopen(filename, "w");
    if (!f) {
        perror("Erreur d'ouverture du fichier de sortie");
        exit(EXIT_FAILURE);
    }

    // En-tête de configuration Mermaid
    fprintf(f, "---\n");
    fprintf(f, "config:\n");
    fprintf(f, "   layout: elk\n");
    fprintf(f, "   theme: neo\n");
    fprintf(f, "   look: neo\n");
    fprintf(f, "---\n\n");

    // Début du diagramme
    fprintf(f, "flowchart LR\n");

    // Déclaration des sommets
    for (int i = 0; i < graph->N_Verticies; i++) {
        char id[3];
        getId(i + 1, id);
        fprintf(f, "%s((%d))\n", id, i + 1);
    }
    fprintf(f, "\n");

    // Déclaration des arêtes avec probabilités
    for (int i = 0; i < graph->N_Verticies; i++) {
        if (graph->Verticies[i] == NULL) continue;

        t_cell *cur = graph->Verticies[i]->head;
        while (cur != NULL) {
            char from[3], to[3];
            getId(i + 1, from);
            getId(cur->vertex, to);

            fprintf(f, "%s -->|%.4f|%s\n", from, cur->proba, to);
            cur = cur->next;
        }
    }

    fclose(f);
    printf("File '%s' generated with sucess.\n", filename);
}
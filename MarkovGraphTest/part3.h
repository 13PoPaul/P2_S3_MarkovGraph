#ifndef PART3_H
#define PART3_H

#include "part2.h"    // Pour t_list_class
#include "ImportMG.h" // Pour adjacency_list
#include <math.h>

// Structure matrice
typedef struct {
    int rows;
    int cols;
    double **data;
} t_matrix;

/* --- Fonctions de base (Step 1) --- */
t_matrix createEmptyMatrix(int rows, int cols);
void freeMatrix(t_matrix *mat);
t_matrix adjacencyToMatrix(adjacency_list *adj);
void copyMatrix(t_matrix dest, t_matrix src);
void multiplyMatrices(t_matrix A, t_matrix B, t_matrix res);
double diffMatrix(t_matrix A, t_matrix B);
void displayMatrix(t_matrix mat);

/* --- Fonctions avancées (Step 2 & 3) --- */
t_matrix subMatrix(t_matrix matrix, t_list_class *part, char *class_name);
int getPeriod(t_matrix sub_matrix);

#endif
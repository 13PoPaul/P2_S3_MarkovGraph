#include "part3.h"   // <--- CORRECTION ICI
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* =========================================================================
   STEP 1: CALCULS MATRICIELS
   ========================================================================= */

t_matrix createEmptyMatrix(int rows, int cols) {
    t_matrix mat;
    mat.rows = rows;
    mat.cols = cols;
    mat.data = (double **)malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++) {
        mat.data[i] = (double *)calloc(cols, sizeof(double));
    }
    return mat;
}

void freeMatrix(t_matrix *mat) {
    if (mat->data) {
        for (int i = 0; i < mat->rows; i++) {
            free(mat->data[i]);
        }
        free(mat->data);
        mat->data = NULL;
    }
}

t_matrix adjacencyToMatrix(adjacency_list *adj) {
    int n = adj->N_Verticies;
    t_matrix mat = createEmptyMatrix(n, n);

    for (int i = 0; i < n; i++) {
        if (adj->Verticies[i] != NULL) {
            t_cell *curr = adj->Verticies[i]->head;
            while (curr != NULL) {
                // Conversion 1-based (ImportMG) vers 0-based (Matrix)
                int j = curr->vertex - 1;
                if (j >= 0 && j < n) {
                    mat.data[i][j] = curr->proba;
                }
                curr = curr->next;
            }
        }
    }
    return mat;
}

void copyMatrix(t_matrix dest, t_matrix src) {
    if (dest.rows != src.rows || dest.cols != src.cols) return;
    for (int i = 0; i < src.rows; i++) {
        for (int j = 0; j < src.cols; j++) {
            dest.data[i][j] = src.data[i][j];
        }
    }
}

void multiplyMatrices(t_matrix A, t_matrix B, t_matrix res) {
    if (A.cols != B.rows) return;

    for(int i=0; i<res.rows; i++)
        for(int j=0; j<res.cols; j++)
            res.data[i][j] = 0.0;

    for (int i = 0; i < A.rows; i++) {
        for (int j = 0; j < B.cols; j++) {
            for (int k = 0; k < A.cols; k++) {
                res.data[i][j] += A.data[i][k] * B.data[k][j];
            }
        }
    }
}

double diffMatrix(t_matrix A, t_matrix B) {
    double sum = 0.0;
    for (int i = 0; i < A.rows; i++) {
        for (int j = 0; j < A.cols; j++) {
            sum += fabs(A.data[i][j] - B.data[i][j]);
        }
    }
    return sum;
}

void displayMatrix(t_matrix mat) {
    for (int i = 0; i < mat.rows; i++) {
        printf("[ ");
        for (int j = 0; j < mat.cols; j++) {
            printf("%.3f ", mat.data[i][j]);
        }
        printf("]\n");
    }
}

/* =========================================================================
   STEP 2: SOUS-MATRICES
   ========================================================================= */

t_matrix subMatrix(t_matrix matrix, t_list_class *part, char *class_name) {
    t_class *curr = part->head;
    while (curr != NULL && strcmp(curr->name, class_name) != 0) {
        curr = curr->next;
    }

    if (curr == NULL) {
        return createEmptyMatrix(0, 0);
    }

    int count = 0;
    t_cell *v = curr->verticies->head;
    while (v) { count++; v = v->next; }

    int *indices = (int *)malloc(count * sizeof(int));
    v = curr->verticies->head;
    for (int k = 0; k < count; k++) {
        indices[k] = v->vertex - 1;
        v = v->next;
    }

    t_matrix sub = createEmptyMatrix(count, count);
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count; j++) {
            sub.data[i][j] = matrix.data[indices[i]][indices[j]];
        }
    }

    free(indices);
    return sub;
}

/* =========================================================================
   STEP 3: PERIODICITE
   ========================================================================= */

int gcd(int *vals, int nbvals) {
    if (nbvals == 0) return 0;
    int result = vals[0];
    for (int i = 1; i < nbvals; i++) {
        int a = result;
        int b = vals[i];
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        result = a;
    }
    return result;
}

int getPeriod(t_matrix sub_matrix) {
    int n = sub_matrix.rows;
    if (n == 0) return 0;

    int *periods = (int *)malloc(n * n * sizeof(int));
    int period_count = 0;

    t_matrix power_matrix = createEmptyMatrix(n, n);
    t_matrix result_matrix = createEmptyMatrix(n, n);

    copyMatrix(power_matrix, sub_matrix);

    for (int k = 1; k <= n; k++) {
        int diag_nonzero = 0;
        for (int i = 0; i < n; i++) {
            if (power_matrix.data[i][i] > 0.00001f) {
                diag_nonzero = 1;
                break;
            }
        }
        if (diag_nonzero) {
            periods[period_count++] = k;
        }
        multiplyMatrices(power_matrix, sub_matrix, result_matrix);
        copyMatrix(power_matrix, result_matrix);
    }

    int final_period = gcd(periods, period_count);

    free(periods);
    freeMatrix(&power_matrix);
    freeMatrix(&result_matrix);

    return final_period;
}
#ifndef PART2_H
#define PART2_H

#include "ImportMG.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* --- Structures spécifiques à Tarjan --- */

// Structure représentant l'état d'un sommet pendant l'algorithme
typedef struct t_tarjan_vertex {
    int Identifier;     // Numéro interne (0 à N-1)
    int IndexClasses;   // Date de découverte (num)
    int GVerticies;     // Plus bas lien accessible (mu / low-link)
    int Boolean;        // 1 si dans la pile, 0 sinon
} t_tarjan_vertex;

// Tableau conteneur pour les sommets Tarjan
typedef struct tarjan_list {
    int N_tarjan;             // Nombre de sommets
    t_tarjan_vertex * tarjan; // Tableau dynamique
} tarjan_list;

// Structure pour une Classe (Composante Fortement Connexe)
typedef struct s_class {
    char * name;            // Nom de la classe (ex: "C1")
    t_list * verticies;     // Liste des sommets (utilise t_list de ImportMG)
    struct s_class* next;   // Chaînage pour la liste de classes
} t_class;

// Liste des classes (La Partition finale)
typedef struct s_list_class {
    t_class * head;
} t_list_class;

/* --- Structures pour la Pile (Stack) --- */
typedef struct s_stack_node {
    int vertex_id;
    struct s_stack_node * next;
} t_stack_node;

typedef struct s_tarjan_stack {
    t_stack_node * top;
} t_tarjan_stack;


// 1. Initialisation
// Crée le tableau de suivi Tarjan à partir du graphe existant
tarjan_list * adjancy_converter(adjacency_list *adj);

// 2. Gestion de la pile
t_tarjan_stack * create_stack();
void stack_push(t_tarjan_stack * s, int id);
int stack_pop(t_tarjan_stack * s);
int is_stack_empty(t_tarjan_stack * s);

// 3. Algorithme de Tarjan
// Fonction récursive de parcours
void parcours(adjacency_list * adj, tarjan_list * data, t_tarjan_stack * stack, int curr, t_list_class * partition, int *time, int *count);
// Fonction principale à appeler dans le main
t_list_class * tarjan(adjacency_list * adj);

// 4. Affichage
void display_partition(t_list_class * partition);


//STEP 2

typedef struct s_link {
    int start_class; // ID de la classe de départ (ex: 1 pour C1)
    int end_class;   // ID de la classe d'arrivée (ex: 4 pour C4)
} t_link;

typedef struct s_link_array {
    int count;       // Nombre de liens trouvés
    int capacity;    // Capacité du tableau (pour realloc si besoin)
    t_link * links;  // Tableau dynamique de liens
} t_link_array;


//Créer le tableau de correspondance [Sommet -> ID Classe]
int * create_class_map(t_list_class * partition, int N_vertices);

//Générer les liens entre classes
t_link_array * generate_hasse_links(adjacency_list * adj, t_list_class * partition);

//Export Mermaid

void export_hasse_mermaid(t_link_array * graph, t_list_class * partition, const char * filename);
#endif

//STEP 3

void display_graph_characteristics(t_list_class * partition, t_link_array * links);
#include "part2.h"

// --- 1. Initialisation des structures de données ---

tarjan_list * adjancy_converter(adjacency_list * adj) {
    if (!adj) return NULL;

    tarjan_list * data = (tarjan_list *) malloc(sizeof(tarjan_list));
    data->N_tarjan = adj->N_Verticies;
    data->tarjan = (t_tarjan_vertex *) malloc(data->N_tarjan * sizeof(t_tarjan_vertex));

    // Initialisation par défaut
    for (int i = 0; i < data->N_tarjan; i++) {
        data->tarjan[i].Identifier = i;
        data->tarjan[i].IndexClasses = -1; // -1 signifie "non visité"
        data->tarjan[i].GVerticies = -1;
        data->tarjan[i].Boolean = 0;       // Pas dans la pile
    }
    return data;
}

// --- 2. Fonctions de pile (Stack) ---

t_tarjan_stack * create_stack() {
    t_tarjan_stack * s = (t_tarjan_stack *) malloc(sizeof(t_tarjan_stack));
    if (s != NULL) {
        s->top = NULL;
    }
    return s;
}

void stack_push(t_tarjan_stack * s, int id) {
    if (s == NULL) return;
    t_stack_node * new_node = (t_stack_node *) malloc(sizeof(t_stack_node));
    if (new_node != NULL) {
        new_node->vertex_id = id;
        new_node->next = s->top;
        s->top = new_node;
    }
}

int stack_pop(t_tarjan_stack * s) {
    if (s == NULL || s->top == NULL) return -1;
    t_stack_node * temp = s->top;
    int id = temp->vertex_id;
    s->top = temp->next;
    free(temp);
    return id;
}

int is_stack_empty(t_tarjan_stack * s) {
    return (s == NULL || s->top == NULL);
}

// --- 3. Cœur de l'algorithme : Parcours (DFS) ---

void parcours(adjacency_list * adj, tarjan_list * data, t_tarjan_stack * stack, int curr, t_list_class * partition, int *time, int *count) {

    // Initialisation du sommet courant (curr est un index 0-based)
    data->tarjan[curr].IndexClasses = *time;
    data->tarjan[curr].GVerticies = *time;
    data->tarjan[curr].Boolean = 1; // Marquer présent dans la pile
    (*time)++;

    stack_push(stack, curr);

    // Récupération de la liste des voisins via ImportMG
    // adj->Verticies est un tableau de pointeurs t_list*
    t_list * neighbor_list = adj->Verticies[curr];

    if (neighbor_list != NULL) {
        t_cell * curr_neighbor = neighbor_list->head;

        while (curr_neighbor != NULL) {
            // CRUCIAL : ImportMG stocke les numéros réels (1 à N).
            // On doit convertir en index (0 à N-1) pour accéder à data->tarjan
            int v = curr_neighbor->vertex - 1;

            // Vérification de sécurité (bornes)
            if (v >= 0 && v < data->N_tarjan) {

                if (data->tarjan[v].IndexClasses == -1) {
                    // Sommet non visité : appel récursif
                    parcours(adj, data, stack, v, partition, time, count);

                    // Retour récursif : mise à jour du low-link
                    if (data->tarjan[v].GVerticies < data->tarjan[curr].GVerticies) {
                        data->tarjan[curr].GVerticies = data->tarjan[v].GVerticies;
                    }
                }
                else if (data->tarjan[v].Boolean == 1) {
                    // Sommet déjà visité ET dans la pile (arc retour)
                    if (data->tarjan[v].IndexClasses < data->tarjan[curr].GVerticies) {
                        data->tarjan[curr].GVerticies = data->tarjan[v].IndexClasses;
                    }
                }
            }
            curr_neighbor = curr_neighbor->next;
        }
    }

    // Si curr est la racine d'une Composante Fortement Connexe (CFC)
    if (data->tarjan[curr].GVerticies == data->tarjan[curr].IndexClasses) {

        // Création d'une nouvelle classe
        t_class * new_class = (t_class *) malloc(sizeof(t_class));

        // On utilise la fonction de ImportMG pour initier la liste
        new_class->verticies = create_empty_list();

        // Nommage dynamique : C1, C2...
        (*count)++;
        new_class->name = (char*)malloc(16 * sizeof(char)); // Assurez assez d'espace
        sprintf(new_class->name, "C%d", *count);

        // Insertion en tête de la liste des partitions
        new_class->next = partition->head;
        partition->head = new_class;

        int node_pop = -1;

        // Dépiler jusqu'à retrouver le sommet racine 'curr'
        do {
            node_pop = stack_pop(stack);
            data->tarjan[node_pop].Boolean = 0; // Sorti de la pile

            // AJOUT DANS LA CLASSE
            // On stocke la valeur réelle (1-based) pour correspondre à l'affichage attendu
            // et à la logique de ImportMG. Donc on fait node_pop + 1.
            add_cell(new_class->verticies, node_pop + 1, 0.0);

        } while (node_pop != curr);
    }
}

// --- 4. Fonction Principale Tarjan ---

t_list_class * tarjan(adjacency_list * adj) {
    if (!adj) return NULL;

    // Prépare la structure de retour
    t_list_class * partition = (t_list_class *) malloc(sizeof(t_list_class));
    partition->head = NULL;

    // Prépare les données internes
    tarjan_list * data = adjancy_converter(adj);
    t_tarjan_stack * stack = create_stack();

    if (!data || !stack) return NULL;

    int time = 0;   // Compteur de temps global pour l'ordre de découverte
    int count = 0;  // Compteur pour nommer les classes C1, C2...

    // Boucle principale pour gérer les graphes non connexes
    for (int i = 0; i < adj->N_Verticies; i++) {
        if (data->tarjan[i].IndexClasses == -1) {
            parcours(adj, data, stack, i, partition, &time, &count);
        }
    }

    // Nettoyage de la mémoire intermédiaire
    free(data->tarjan);
    free(data);

    // Vider et libérer la pile si nécessaire (normalement elle est vide ici)
    while(!is_stack_empty(stack)) stack_pop(stack);
    free(stack);

    return partition;
}

// --- 5. Affichage ---

void display_partition(t_list_class * partition) {
    if (partition == NULL || partition->head == NULL) {
        printf("La partition est vide.\n");
        return;
    }

    t_class * current_class = partition->head;

    while (current_class != NULL) {
        printf("Component %s: {", current_class->name);

        t_cell * curr_vertex = current_class->verticies->head;
        while (curr_vertex != NULL) {
            // Ici, curr_vertex->vertex contient déjà la valeur réelle (1-based)
            // car nous avons fait le +1 lors du 'add_cell' dans 'parcours'.
            printf("%d", curr_vertex->vertex);

            if (curr_vertex->next != NULL) {
                printf(", ");
            }
            curr_vertex = curr_vertex->next;
        }
        printf("}\n");

        current_class = current_class->next;
    }
}

// STEP 2
// ... (Code précédent de Tarjan) ...

// --- STEP 2 : Diagramme de Hasse ---

// Fonction utilitaire : Extrait l'ID entier du nom "C12" -> 12
int get_class_id(char * name) {
    if (name == NULL || name[0] != 'C') return -1;
    return atoi(name + 1); // Saute le 'C' et convertit la suite
}

// 2.1 Associer chaque sommet à sa classe
int * create_class_map(t_list_class * partition, int N_vertices) {
    int * map = (int *) malloc(N_vertices * sizeof(int));

    // Init à -1 pour détecter les erreurs éventuelles
    for(int i=0; i<N_vertices; i++) map[i] = -1;

    t_class * current_class = partition->head;
    while (current_class != NULL) {
        int class_id = get_class_id(current_class->name);

        t_cell * curr_vertex = current_class->verticies->head;
        while (curr_vertex != NULL) {
            // Attention : curr_vertex->vertex est en 1-based (ex: 10)
            // On le stocke à l'index 0-based (ex: 9)
            int index = curr_vertex->vertex - 1;

            if (index >= 0 && index < N_vertices) {
                map[index] = class_id;
            }
            curr_vertex = curr_vertex->next;
        }
        current_class = current_class->next;
    }
    return map;
}

// Vérifie si un lien existe déjà pour éviter les doublons simples
int link_exists(t_link_array * arr, int start, int end) {
    for (int i = 0; i < arr->count; i++) {
        if (arr->links[i].start_class == start && arr->links[i].end_class == end) {
            return 1; // Vrai
        }
    }
    return 0; // Faux
}

// 2.2 Générer les liens (Le coeur de l'algorithme Hasse)
t_link_array * generate_hasse_links(adjacency_list * adj, t_list_class * partition) {

    // 1. Création de la map [Sommet -> Classe]
    int * class_map = create_class_map(partition, adj->N_Verticies);

    // 2. Préparation du tableau de liens
    t_link_array * res = (t_link_array *) malloc(sizeof(t_link_array));
    res->capacity = adj->N_Verticies * 2; // Estimation initiale
    res->count = 0;
    res->links = (t_link *) malloc(res->capacity * sizeof(t_link));

    // 3. Parcours de tout le graphe
    for (int i = 0; i < adj->N_Verticies; i++) {
        // i est l'index source (0-based). Sa classe est :
        int class_src = class_map[i];

        // On regarde ses voisins
        t_list * neighbors = adj->Verticies[i];
        if (neighbors != NULL) {
            t_cell * curr = neighbors->head;
            while (curr != NULL) {
                // Le voisin est stocké en 1-based (ex: 5) -> index 4
                int neighbor_idx = curr->vertex - 1;
                int class_dst = class_map[neighbor_idx];

                // Si les classes sont valides et différentes
                if (class_src != -1 && class_dst != -1 && class_src != class_dst) {

                    // Si le lien n'existe pas encore, on l'ajoute
                    if (!link_exists(res, class_src, class_dst)) {

                        // Realloc dynamique si tableau plein
                        if (res->count >= res->capacity) {
                            res->capacity *= 2;
                            res->links = (t_link *) realloc(res->links, res->capacity * sizeof(t_link));
                        }

                        res->links[res->count].start_class = class_src;
                        res->links[res->count].end_class = class_dst;
                        res->count++;
                    }
                }
                curr = curr->next;
            }
        }
    }

    free(class_map);
    return res;
}

// 2.3 Export Mermaid
void export_hasse_mermaid(t_link_array * graph, t_list_class * partition, const char * filename) {
    FILE * f = fopen(filename, "w");
    if (f == NULL) return;

    fprintf(f, "graph TD;\n");

    // 1. On définit le texte dans les boites : ex C1("{1}")
    t_class * curr = partition->head;
    while (curr != NULL) {
        // On récupère l'ID (ex: C1 -> 1)
        int id = get_class_id(curr->name);

        // On écrit l'étiquette Mermaid
        fprintf(f, "    C%d(\"{", id);

        // On liste les sommets : {1,2,3}
        t_cell * v = curr->verticies->head;
        while (v != NULL) {
            fprintf(f, "%d", v->vertex);
            if (v->next != NULL) fprintf(f, ",");
            v = v->next;
        }
        fprintf(f, "}\");\n");

        curr = curr->next;
    }

    fprintf(f, "\n");

    // 2. On dessine les flèches
    if (graph->count == 0) {
        fprintf(f, "    %% Aucune transition\n");
    } else {
        for (int i = 0; i < graph->count; i++) {
            fprintf(f, "    C%d-->C%d;\n", graph->links[i].start_class, graph->links[i].end_class);
        }
    }

    fclose(f);
}

//STEP3

// Fonction utilitaire locale pour compter les sommets dans une liste ImportMG
int count_vertices_in_list(t_list * l) {
    if (!l) return 0;
    int c = 0;
    t_cell * curr = l->head;
    while (curr) {
        c++;
        curr = curr->next;
    }
    return c;
}

void display_graph_characteristics(t_list_class * partition, t_link_array * links) {
    printf("\n=== STEP 3: Graph Characteristics ===\n");

    if (!partition || !partition->head) {
        printf("Partition vide.\n");
        return;
    }

    int total_classes = 0;
    int is_irreducible = 0;

    t_class * curr_class = partition->head;

    while (curr_class != NULL) {
        total_classes++;

        // 1. Identification de l'ID de la classe (ex: C4 -> 4)
        int class_id = get_class_id(curr_class->name);

        // 2. Vérification : Est-ce qu'on peut sortir de cette classe ?
        int is_transient = 0;
        for (int i = 0; i < links->count; i++) {
            if (links->links[i].start_class == class_id) {
                is_transient = 1;
                break; // On a trouvé une sortie, pas besoin de chercher plus
            }
        }

        // 3. Affichage des propriétés
        printf("Class %s is ", curr_class->name);

        if (is_transient) {
            printf("Transient.\n");
        } else {
            printf("Persistent.\n");

            // Vérification état absorbant (Persistant + 1 seul sommet)
            if (count_vertices_in_list(curr_class->verticies) == 1) {
                printf("   -> State %d is Absorbing.\n", curr_class->verticies->head->vertex);
            }
        }

        curr_class = curr_class->next;
    }

    printf("-------------------------------------\n");

    // 4. Irréductibilité
    if (total_classes == 1) {
        printf("The Markov graph IS IRREDUCIBLE (only 1 class).\n");
    } else {
        printf("The Markov graph is NOT irreducible (%d classes found).\n", total_classes);
    }

}
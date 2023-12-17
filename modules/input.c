#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../header_files/input.h"
#include "../header_files/utils.h"
#include "../header_files/output.h"

/**
 * @brief Read a graph from a text file and save it in either an
 * adjascent matrix or an adjascent list
 * 
 * @param filename name of the text file to be read
 * @param graph pointer to a graph object
 * @param option either 1 or 2: 1-adjascent matrix; 2-adjascent list
 * @param has_weight boolean 
 */
void read_graph(char* filename, Graph* graph, int option, int has_weight) {
  FILE *file = fopen(filename, "r");

  if(file == NULL) {
    printf("Error opening the file.\n");
    exit(EXIT_FAILURE);
  }

  int n;
  fscanf(file, "%d", &n);

  graph->n = n;

  if(graph->n == 0) {
    fclose(file);
    return;
  }

  int e1, e2;
  int w;
  int m = 0;

  if(option == 1 && has_weight == 0) {
    char** adj_matrix = (char**)calloc(n, sizeof(char*));

    for(int i=0; i<n; i++) {
      adj_matrix[i] = (char*)calloc(n, sizeof(char));
    }

    while(fscanf(file, "%d %d", &e1, &e2) != EOF) {
      adj_matrix[e1-1][e2-1] = '1';
      adj_matrix[e2-1][e1-1] = '1';  
      
      m++;
    }

    graph->adj_matrix = adj_matrix;
    graph->adj_list = NULL;

  } else if(option == 2) {
    List** adj_list = (List**)malloc(n * sizeof(List*));

    for(int i=0; i<n; i++) {
      adj_list[i] = create_list(constructor_char, destructor_char);
    }  

    if(has_weight) {

      while(fscanf(file, "%d %d %d", &e1, &e2, &w) != EOF) {
        char* aux = int_to_char(e2);
        char* aux2 = int_to_char(e1);

        if(!is_in_list(adj_list[e1-1], aux)) {
          append(adj_list[e1-1], aux, w);
          append(adj_list[e2-1], aux2, w);  
        }

        free(aux);
        free(aux2);
        
        m++;
      }

    } else {
      while(fscanf(file, "%d %d", &e1, &e2) != EOF) {
        char* aux = int_to_char(e2);
        char* aux2 = int_to_char(e1);

        if(!is_in_list(adj_list[e1-1], aux)) {
          append(adj_list[e1-1], aux, 1.0);
          append(adj_list[e2-1], aux2, 1.0);  
        }

        free(aux);
        free(aux2);
        
        m++;
      }
    }

    graph->adj_list = adj_list;
    graph->adj_matrix = NULL;
  }

  graph->m = m;

  fclose(file);

  generate_graph_info(graph);
}
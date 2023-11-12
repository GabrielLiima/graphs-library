#include <stdio.h>
#include <stdlib.h>

#include "../header_files/output.h"

/**
 * @brief Get the vertex degrees from adjascent matrix
 * 
 * @param file pointer to a text file
 * @param graph pointer to a graph object
 */
static void get_degrees_from_adj_matrix(FILE* file, Graph* graph) {
  int degree = 0;

  for(int i=0; i<graph->n; i++) {

    for(int j=0; j<graph->n; j++) {

      if(graph->adj_matrix[i][j] == '1') {
        degree++;
      }
    }

    fprintf(file, "%d %d\n", i+1, degree);
    degree = 0;
  }
}

/**
 * @brief Get the vertex degrees from adjascent list
 * 
 * @param file pointer to a file
 * @param graph pointer to a graph object
 */
static void get_degrees_from_adj_list(FILE* file, Graph* graph) {

  for(int i=0; i<graph->n; i++) {
    fprintf(file, "%d %d\n", i+1, graph->adj_list[i]->size);
  }
}

/**
 * @brief Generate the output text file
 * 
 * @param graph pointer to a graph object
 */
void generate_graph_info(Graph* graph) {
  FILE *file = fopen("./outputs/output.txt", "w");

  if(file == NULL) {
    printf("Error creating output file.\n");
    exit(EXIT_FAILURE);
  }

  fprintf(file, "# n = %d\n", graph->n);
  fprintf(file, "# m = %d\n", graph->m);

  if(graph->adj_matrix != NULL) {
    get_degrees_from_adj_matrix(file, graph);

  } else if(graph->adj_list != NULL) {
    get_degrees_from_adj_list(file, graph);
  }

  fclose(file);
}

/**
 * @brief Generate the search output text file
 * 
 * @param parent string array containing the vertexes parents
 * @param height string array containing the vertexes heights
 * @param n graph size
 * @param option either 1 or 2: 1-bfs output; 2-dfs output
 */
void generate_search_output(char** parent, char** height, int n, int option) {
  FILE *file = NULL;

  if(option == 1) {
    file = fopen("./outputs/output_bfs.txt", "w");

  } else if(option == 2) {
    file = fopen("./outputs/output_dfs.txt", "w");
  }

  if(file == NULL) {
    printf("Error creating output file.\n");
    exit(EXIT_FAILURE);
  }

  for(int i=0; i<n; i++) {
    fprintf(file, "%d <- %s (%s)\n", i+1, parent[i], height[i]);
  }

  fclose(file);
}

/**
 * @brief Print an adjascent matrix
 * 
 * @param adj_matrix adjascent matrix
 * @param n size
 */
void print_adj_matrix(char** adj_matrix, int n) {
  for(int i=0; i<n; i++) {
    
    for(int j=0; j<n; j++) {

      if(adj_matrix[i][j] == '\0') {
        printf("[%d][%d] = 0\n", i+1, j+1);

      } else {
        printf("[%d][%d] = %c\n", i+1, j+1, adj_matrix[i][j]);
      }
    }
  }
}

/**
 * @brief Print an adjascent list
 * 
 * @param adj_list adjascent list
 * @param n size
 */
void print_adj_list(List** adj_list, int n) {
  for(int i=0; i<n; i++) {
    printf("%d: ", i+1);

    print_list(adj_list[i]->head);
  }
}
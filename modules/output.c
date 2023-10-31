#include <stdio.h>
#include <stdlib.h>

#include "../header_files/output.h"

void generate_graph_info(Graph* graph) {
  FILE *file = fopen("./outputs/output.txt", "w");

  if(file == NULL) {
    printf("Error creating output file.\n");
    exit(EXIT_FAILURE);
  }

  fprintf(file, "# n = %d\n", graph->n);
  fprintf(file, "# m = %d\n", graph->m);

  int degree = 0;

  if(graph->adj_matrix != NULL) {

    for(int i=0; i<graph->n; i++) {

      for(int j=0; j<graph->n; j++) {

        if(graph->adj_matrix[i][j] == '1') {
          degree++;
        }
      }

      fprintf(file, "%d %d\n", i+1, degree);
      degree = 0;
    }

  } else if(graph->adj_list != NULL) {
    for(int i=0; i<graph->n; i++) {
      fprintf(file, "%d %d\n", i+1, graph->adj_list[i]->size);
    }
  }

  fclose(file);
}

void generate_bfs_output(char** parent, char** height, int n) {
  FILE *file = fopen("./outputs/output_bfs.txt", "w");

  if(file == NULL) {
    printf("Error creating output file.\n");
    exit(EXIT_FAILURE);
  }

  for(int i=0; i<n; i++) {
    fprintf(file, "%d <- %s (%s)\n", i+1, parent[i], height[i]);
  }

  fclose(file);
}

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

void print_adj_list(List** adj_list, int n) {
  for(int i=0; i<n; i++) {
    printf("%d: ", i+1);

    printList(adj_list[i]->head);
  }
}
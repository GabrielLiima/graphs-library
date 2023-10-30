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
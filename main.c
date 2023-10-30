#include <stdio.h>
#include <stdlib.h>

#include "./header_files/input.h"
#include "./header_files/output.h"
#include "./header_files/search.h"

int main(int argc, char *argv[]) {
  FILE *file = fopen(argv[1], "r");

  if(file == NULL) {
    printf("Error opening the file.\n");
    exit(EXIT_FAILURE);
  }

  Graph graph;
  
  read_graph(&graph, file, 1);

  fclose(file);

  // print_adj_list(graph.adj_list, graph.n);

  bfs(&graph, 1);

  generate_graph_info(&graph);

  // print_adj_matrix(graph.adj_matrix, graph.n);
  
  // for(int i=0; i<graph.n; i++) {
  //   deleteList(graph.adj_list[i]);
  // }

  // free(graph.adj_list);

  for(int i=0; i<graph.n; i++) {
    free(graph.adj_matrix[i]);
  }

  free(graph.adj_matrix);

  return 0;
}
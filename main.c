#include <stdio.h>
#include <stdlib.h>

#include "./header_files/input.h"
#include "./header_files/search.h"

int main(int argc, char *argv[]) {
  Graph graph;
  
  read_graph(argv[1], &graph, 1);

  search(&graph, 1, 1);
  search(&graph, 1, 2);

  find_connected_components(&graph);
  
  // for(int i=0; i<graph.n; i++) {
  //   delete_list(graph.adj_list[i]);
  // }

  // free(graph.adj_list);

  for(int i=0; i<graph.n; i++) {
    free(graph.adj_matrix[i]);
  }

  free(graph.adj_matrix);

  return 0;
}
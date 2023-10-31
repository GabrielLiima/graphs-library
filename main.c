#include <stdio.h>
#include <stdlib.h>

#include "./header_files/input.h"
#include "./header_files/search.h"

int main(int argc, char *argv[]) {
  Graph graph;
  
  read_graph(argv[1], &graph, 1);

  bfs(&graph, 1);
  
  //for(int i=0; i<graph.n; i++) {
    //deleteList(graph.adj_list[i]);
  //}

  //free(graph.adj_list);

  for(int i=0; i<graph.n; i++) {
    free(graph.adj_matrix[i]);
  }

  free(graph.adj_matrix);

  return 0;
}
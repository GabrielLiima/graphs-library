#include <stdio.h>
#include <stdlib.h>

#include "./header_files/input.h"
#include "./header_files/search.h"

int main(int argc, char *argv[]) {
  Graph graph;
  
  // Adjascent Matrix
  // read_graph(argv[1], &graph, 1, 0);

  // Adjascent List
  read_graph(argv[1], &graph, 2, 1);

  // BFS
  // search(&graph, 1, 100, 1);

  // DFS
  // search(&graph, 1, graph.n, 2);

  // find_connected_components(&graph);
  
  // Find path
  // find_path(&graph, 34, 80);

  dijkstra(&graph, 1, 5);

  // Only when using adjascent list
  for(int i=0; i<graph.n; i++) {
    delete_list(graph.adj_list[i]);
  }

  free(graph.adj_list);

  //Only when using adjascent matrix
  // for(int i=0; i<graph.n; i++) {
  //   free(graph.adj_matrix[i]);
  // }

  // free(graph.adj_matrix);

  return 0;
}
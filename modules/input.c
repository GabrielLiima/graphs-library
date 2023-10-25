#include <stdio.h>
#include <stdlib.h>

#include "../header_files/input.h"

Graph read_graph(FILE *file) {
  int n;
  fscanf(file, "%d", &n);

  Graph graph;
  graph.n = n;

  char** adj_matrix = (char**)calloc(n, sizeof(char*));

  for(int i=0; i<n; i++) {
    adj_matrix[i] = (char*)calloc(n, sizeof(char));
  }

  int e1, e2;
  int m = 0;

  while(fscanf(file, "%d %d", &e1, &e2) != EOF) {
    if(e1 < e2) {
      adj_matrix[e1-1][e2-1] = '1';

    } else {
      adj_matrix[e2-1][e1-1] = '1';  
    }

    m++;
  }

  graph.adj_matrix = adj_matrix;
  graph.m = m;

  return graph;
}
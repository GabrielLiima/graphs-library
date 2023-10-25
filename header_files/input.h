#ifndef INPUT_H
#define INPUT_H

typedef struct Graph {
  char** adj_matrix;
  int n;
  int m;
} Graph;

Graph read_graph(FILE *file);

#endif
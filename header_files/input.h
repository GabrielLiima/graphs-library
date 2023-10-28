#ifndef INPUT_H
#define INPUT_H

#include "./linked_list.h"

typedef struct Graph {
  char** adj_matrix;
  List** adj_list;
  int n;
  int m;
} Graph;

void read_graph(Graph* graph, FILE *file, int option);

#endif
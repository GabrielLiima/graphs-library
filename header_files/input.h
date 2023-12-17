#ifndef INPUT_H
#define INPUT_H

#include "./linked_list.h"

typedef struct Graph {
  char** adj_matrix;
  List** adj_list;
  int n;
  int m;
} Graph;

void read_graph(char* filename, Graph* graph, int option, int has_weight);

#endif
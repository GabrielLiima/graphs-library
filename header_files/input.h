#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>
#include "./linked_list.h"

typedef struct Graph {
  char** adj_matrix;
  List** adj_list;
  int n;
  int m;
} Graph;

void read_graph(Graph* graph, FILE *file, int option);
void print_adj_matrix(char** adj_matrix, int n);
void print_adj_list(List** adj_list, int n);
void deleteHead(List* l);

char* constructor_char(char* data);
void destructor_char(char* data);

#endif
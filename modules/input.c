#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../header_files/input.h"

static char* constructor_char(char* data) {
  char* p = malloc(sizeof(char));
  memcpy(p, data, sizeof(char));

  return p;
}

static void destructor_char(char* data) {
  free(data);
}

void read_graph(Graph* graph, FILE *file, int option) {
  int n;
  fscanf(file, "%d", &n);

  graph->n = n;

  int e1, e2;
  int m = 0;

  if(option == 1) {
    char** adj_matrix = (char**)calloc(n, sizeof(char*));

    for(int i=0; i<n; i++) {
      adj_matrix[i] = (char*)calloc(n, sizeof(char));
    }

    while(fscanf(file, "%d %d", &e1, &e2) != EOF) {
      adj_matrix[e1-1][e2-1] = '1';
      adj_matrix[e2-1][e1-1] = '1';  
      
      m++;
    }

    rewind(file);

    graph->adj_matrix = adj_matrix;

  } else if(option == 2) {
    List** adj_list = (List**)malloc(n * sizeof(List*));

    for(int i=0; i<n; i++) {
      adj_list[i] = createList(constructor_char, destructor_char);
    }

    char value = ' ';  

    while(fscanf(file, "%d %d", &e1, &e2) != EOF) {
      value = '0' + e2;
      append(adj_list[e1-1], &value);

      value = '0' + e1;
      append(adj_list[e2-1], &value);
      
      m++;
    }

    rewind(file);

    graph->adj_list = adj_list;

    for(int i=0; i<n; i++) {
      printList(adj_list[i]->head);
    }
  }

  graph->m = m;
}
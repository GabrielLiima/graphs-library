#include <stdlib.h>
#include <string.h>

#include "../header_files/input.h"
#include "../header_files/utils.h"

char* constructor_char(char* data) {
  int n = len(data);

  char* p = malloc(n * sizeof(char));
  memcpy(p, data, n * sizeof(char));

  return p;
}

void destructor_char(char* data) {
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
    graph->adj_list = NULL;

  } else if(option == 2) {
    List** adj_list = (List**)malloc(n * sizeof(List*));

    for(int i=0; i<n; i++) {
      adj_list[i] = createList(constructor_char, destructor_char);
    }  

    while(fscanf(file, "%d %d", &e1, &e2) != EOF) {
      char* aux = int_to_char(e2);
      char* aux2 = int_to_char(e1);

      if(!isInList(adj_list[e1-1], aux)) {
        append(adj_list[e1-1], aux);
        append(adj_list[e2-1], aux2);  
      }

      free(aux);
      free(aux2);
      
      m++;
    }

    rewind(file);

    graph->adj_list = adj_list;
    graph->adj_matrix = NULL;
  }

  graph->m = m;
}

void print_adj_matrix(char** adj_matrix, int n) {
  for(int i=0; i<n; i++) {
    
    for(int j=0; j<n; j++) {

      if(adj_matrix[i][j] == '\0') {
        printf("[%d][%d] = 0\n", i+1, j+1);

      } else {
        printf("[%d][%d] = %c\n", i+1, j+1, adj_matrix[i][j]);
      }
    }
  }
}

void print_adj_list(List** adj_list, int n) {
  for(int i=0; i<n; i++) {
    printf("%d: ", i+1);

    printList(adj_list[i]->head);
  }
}
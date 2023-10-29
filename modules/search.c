#include <stdlib.h>

#include "../header_files/search.h"

void bfs(Graph* graph, int start) {
  List* queue = createList(constructor_char, destructor_char);

  char* visited = (char*)malloc(graph->n * sizeof(char));

  visited[start-1] = '1';

  char node = '0' + start;
  append(queue, &node);

  char* parent = (char*)malloc(graph->n * sizeof(char));

  while(queue->size != 0) {
    char current_vertex_char = *(queue->head->data);
    int current_vertex_int = current_vertex_char - '0';

    deleteHead(queue);

    printf("%c -> ", current_vertex_char);

    for(int i=1; i<=graph->n; i++) {

      if(graph->adj_matrix[current_vertex_int-1][i-1] == '1' && visited[i-1] != '1') {
        visited[i-1] = '1';
        parent[i-1] = current_vertex_char;

        char vertex = '0' + i;
        append(queue, &vertex);
      }
    }
  }

  free(visited);
  free(parent);
  deleteList(queue);
}
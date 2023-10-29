#include <stdlib.h>

#include "../header_files/search.h"
#include "../header_files/utils.h"

void bfs(Graph* graph, int start) {
  List* queue = createList(constructor_char, destructor_char);

  char* visited = (char*)calloc(graph->n, sizeof(char));

  visited[start-1] = '1';

  append(queue, int_to_char(start));

  char** parent = (char**)calloc(graph->n, sizeof(char*));

  while(queue->size != 0) {
    char* current_vertex_char = queue->head->data;
    int current_vertex_int = char_to_int(current_vertex_char);

    deleteHead(queue);

    printf("%d -> ", current_vertex_int);

    for(int i=1; i<=graph->n; i++) {

      if(graph->adj_matrix[current_vertex_int-1][i-1] == '1' && visited[i-1] != '1') {
        visited[i-1] = '1';
        parent[i-1] = current_vertex_char;

        append(queue, int_to_char(i));
      }
    }
  }

  free(visited);
  free(parent);
  deleteList(queue);
}
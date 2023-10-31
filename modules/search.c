#include <stdlib.h>

#include "../header_files/search.h"
#include "../header_files/utils.h"
#include "../header_files/output.h"

void bfs(Graph* graph, int start) {
  List* queue = createList(constructor_char, destructor_char);

  char* visited = (char*)calloc(graph->n, sizeof(char));

  visited[start-1] = '1';

  char* start_char = int_to_char(start);
  append(queue, start_char);
  free(start_char);

  char** parent = (char**)calloc(graph->n, sizeof(char*));

  char** height = (char**)calloc(graph->n, sizeof(char*));
  height[start-1] = constructor_char("0\0");

  while(queue->size != 0) {
    char* current_vertex_char = constructor_char(queue->head->data);
    int current_vertex_int = char_to_int(current_vertex_char);

    deleteHead(queue);

    if(graph->adj_matrix != NULL) {
      for(int i=1; i<=graph->n; i++) {

        if(graph->adj_matrix[current_vertex_int-1][i-1] == '1' && visited[i-1] != '1') {
          visited[i-1] = '1';
          parent[i-1] = constructor_char(current_vertex_char);

          int cur_height = char_to_int(height[current_vertex_int-1]) + 1;
          height[i-1] = int_to_char(cur_height);

          char* i_char = int_to_char(i);
          append(queue, i_char);
          free(i_char);
        } 
      }

    } else if(graph->adj_list != NULL) {
      Node* cur = graph->adj_list[current_vertex_int-1]->head;

      while(cur != NULL) {
        if(visited[char_to_int(cur->data)-1] != '1') {
          visited[char_to_int(cur->data)-1] = '1';
          parent[char_to_int(cur->data)-1] = constructor_char(current_vertex_char);
          
          int cur_height = char_to_int(height[current_vertex_int-1]) + 1;
          height[char_to_int(cur->data)-1] = int_to_char(cur_height);
          
          append(queue, cur->data);
        }

        cur = cur->next;
      }
    }

    free(current_vertex_char);
  }

  free(visited);

  generate_bfs_output(parent, height, graph->n);

  for(int i=0; i<graph->n; i++) {
    free(parent[i]);
    free(height[i]);
  }

  free(parent);
  free(height);
  deleteList(queue);
}
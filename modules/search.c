#include <stdlib.h>

#include "../header_files/search.h"
#include "../header_files/utils.h"
#include "../header_files/output.h"

static void search_helper(Graph* graph, int start, char* visited, char** parent, char** height, int search_type) {
  List* queue = create_list(constructor_char, destructor_char);
  char* start_char = int_to_char(start);

  append(queue, start_char);

  free(start_char);

  while(queue->size != 0) {
    char* cur_vertex_char = constructor_char(queue->head->data);
    int cur_vertex_int = char_to_int(cur_vertex_char);

    delete_head(queue);

    if(graph->adj_matrix != NULL) {

      for(int i=1; i<=graph->n; i++) {

        if(graph->adj_matrix[cur_vertex_int-1][i-1] == '1' && visited[i-1] != '1') {
          visited[i-1] = '1';
          parent[i-1] = constructor_char(cur_vertex_char);

          int cur_height = char_to_int(height[cur_vertex_int-1]) + 1;
          height[i-1] = int_to_char(cur_height);

          if(search_type == 1) {
            char* i_char = int_to_char(i);
            append(queue, i_char);

            free(i_char);

          } else if(search_type == 2) {
            search_helper(graph, i, visited, parent, height, 2);
          }
        }
      }

    } else if(graph->adj_list != NULL) {
      Node* cur = graph->adj_list[cur_vertex_int-1]->head;

      while(cur != NULL) {

        if(visited[char_to_int(cur->data)-1] != '1') {
          visited[char_to_int(cur->data)-1] = '1';
          parent[char_to_int(cur->data)-1] = constructor_char(cur_vertex_char);

          int cur_height = char_to_int(height[cur_vertex_int-1]) + 1;
          height[char_to_int(cur->data)-1] = int_to_char(cur_height);

          if(search_type == 1) {
            char* i_char = int_to_char(char_to_int(cur->data));
            append(queue, i_char);

            free(i_char);

          } else if(search_type == 2) {
            search_helper(graph, char_to_int(cur->data), visited, parent, height, 2);
          }
        }
        cur = cur->next;
      }
    }
    free(cur_vertex_char);
  }
  delete_list(queue);
}

void search(Graph* graph, int start, int option) {
  char* visited = (char*)calloc(graph->n, sizeof(char));
  char** parent = (char**)calloc(graph->n, sizeof(char*));
  char** height = (char**)calloc(graph->n, sizeof(char*));

  height[start - 1] = constructor_char("0\0");
  visited[start-1] = '1';

  if(option == 1) {
    search_helper(graph, start, visited, parent, height, 1);
    generate_search_output(parent, height, graph->n, 1);

  } else if(option == 2) {
    search_helper(graph, start, visited, parent, height, 2);
    generate_search_output(parent, height, graph->n, 2);
  }

  free(visited);

  for(int i=0; i<graph->n; i++) {
    free(parent[i]);
    free(height[i]);
  }

  free(parent);
  free(height);
}
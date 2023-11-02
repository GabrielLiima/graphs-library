#include <stdlib.h>

#include "../header_files/search.h"
#include "../header_files/utils.h"
#include "../header_files/output.h"

void bfs(Graph* graph, int start) {
  List* queue = createList(constructor_char, destructor_char);

  char** parent = (char**)calloc(graph->n, sizeof(char*));
  char** height = (char**)calloc(graph->n, sizeof(char*));
  char* visited = (char*)calloc(graph->n, sizeof(char));

  height[start-1] = constructor_char("0\0");
  visited[start-1] = '1';

  char* start_char = int_to_char(start);
  append(queue, start_char);
  free(start_char);

  while(queue->size != 0) {
    char* cur_vertex_char = constructor_char(queue->head->data);
    int cur_vertex_int = char_to_int(cur_vertex_char);

    deleteHead(queue);

    if(graph->adj_matrix != NULL) {
      for(int i=1; i<=graph->n; i++) {

        if(graph->adj_matrix[cur_vertex_int-1][i-1] == '1' && visited[i-1] != '1') {
          visited[i-1] = '1';
          parent[i-1] = constructor_char(cur_vertex_char);

          int cur_height = char_to_int(height[cur_vertex_int-1]) + 1;
          height[i-1] = int_to_char(cur_height);

          char* i_char = int_to_char(i);
          append(queue, i_char);
          free(i_char);
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
          
          append(queue, cur->data);
        }

        cur = cur->next;
      }
    }

    free(cur_vertex_char);
  }

  free(visited);

  generate_search_output(parent, height, graph->n, 1);

  for(int i=0; i<graph->n; i++) {
    free(parent[i]);
    free(height[i]);
  }

  free(parent);
  free(height);
  deleteList(queue);
}

static void dfsHelper(Graph* graph, char* vertex, char* visited, char** parent, char** height) {
  int vertex_int = char_to_int(vertex);

  visited[vertex_int-1] = '1';

  if(graph->adj_matrix != NULL) {

    for(int i=1; i<=graph->n; i++) {
      if(graph->adj_matrix[vertex_int-1][i-1] == '1' && visited[i-1] != '1') {
        parent[i-1] = constructor_char(vertex);
        
        int cur_height = char_to_int(height[vertex_int - 1]) + 1;
        height[i-1] = int_to_char(cur_height);

        char* next_vertex = int_to_char(i);

        dfsHelper(graph, next_vertex, visited, parent, height);

        free(next_vertex);
      }
    }

  } else if(graph->adj_list != NULL) {
    Node* cur = graph->adj_list[vertex_int-1]->head;

    while(cur != NULL) {
      if(visited[char_to_int(cur->data) - 1] != '1') {
        parent[char_to_int(cur->data) - 1] = constructor_char(vertex);

        int cur_height = char_to_int(height[vertex_int - 1]) + 1;
        height[char_to_int(cur->data) - 1] = int_to_char(cur_height);

        dfsHelper(graph, cur->data, visited, parent, height);
      }

      cur = cur->next;
    }
  }
}

void dfs(Graph* graph, int start) {
  char* visited = (char*)calloc(graph->n, sizeof(char));
  char** parent = (char**)calloc(graph->n, sizeof(char*));
  char** height = (char**)calloc(graph->n, sizeof(char*));

  height[start - 1] = constructor_char("0\0");

  char* vertex = int_to_char(start);

  dfsHelper(graph, vertex, visited, parent, height);
  generate_search_output(parent, height, graph->n, 2);

  free(vertex);
  free(visited);

  for(int i=0; i<graph->n; i++) {
    free(parent[i]);
    free(height[i]);
  }

  free(parent);
  free(height);
}

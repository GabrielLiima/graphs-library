#include <stdlib.h>
#include <stdio.h>

#include "../header_files/search.h"
#include "../header_files/utils.h"
#include "../header_files/output.h"

/**
 * @brief Helper function for traversing a graph
 * 
 * @param graph pointer to a graph object
 * @param search_info pointer to a search_info object
 * @param start starting vertex
 * @param search_type either 1 or 2: 1-bfs; 2-dfs
 */
static void search_helper(Graph* graph, SearchInfo* search_info, int start, int end, int search_type) {
  search_info->visited[start-1] = '1';

  char* start_char = int_to_char(start);

  append(search_info->queue, start_char, 0);

  free(start_char);

  while(search_info->queue->size != 0) {
    char* cur_vertex_char = constructor_char(search_info->queue->head->data);
    int cur_vertex_int = char_to_int(cur_vertex_char);

    delete_head(search_info->queue);

    if(graph->adj_matrix != NULL) {

      for(int i=1; i<=graph->n; i++) {

        if(graph->adj_matrix[cur_vertex_int-1][i-1] == '1' && search_info->visited[i-1] != '1') {
          search_info->visited[i-1] = '1';
          search_info->parent[i-1] = constructor_char(cur_vertex_char);

          int cur_height = char_to_int(search_info->height[cur_vertex_int-1]) + 1;
          search_info->height[i-1] = int_to_char(cur_height);

          if(search_type == 1) {
            if(cur_vertex_int == end) {
              search_info->queue->size = 0;
              break;
            }

            char* i_char = int_to_char(i);
            append(search_info->queue, i_char, 0);

            free(i_char);

          } else if(search_type == 2) {
            search_helper(graph, search_info, i, end, 2);
          }
        }
      }

    } else if(graph->adj_list != NULL) {
      Node* cur = graph->adj_list[cur_vertex_int-1]->head;

      while(cur != NULL) {
        if(search_info->visited[char_to_int(cur->data)-1] != '1') {
          search_info->visited[char_to_int(cur->data)-1] = '1';
          search_info->parent[char_to_int(cur->data)-1] = constructor_char(cur_vertex_char);

          int cur_height = char_to_int(search_info->height[cur_vertex_int-1]) + 1;
          search_info->height[char_to_int(cur->data)-1] = int_to_char(cur_height);

          if(search_type == 1) {
            if(cur_vertex_int == end) {
              search_info->queue->size = 0;
              break;
            }

            char* i_char = int_to_char(char_to_int(cur->data));
            append(search_info->queue, i_char, 0);

            free(i_char);

          } else if(search_type == 2) {
            search_helper(graph, search_info, char_to_int(cur->data), end, 2);
          }
        }
        cur = cur->next;
      }
    }
    free(cur_vertex_char);
  }
}

/**
 * @brief Traverse a graph using either bfs or dfs
 * 
 * @param graph pointer to a graph object
 * @param start starting vertex
 * @param option either 1 or 2: 1-bfs; 2-dfs
 */
void search(Graph* graph, int start, int end, int option) {
  if(graph->n == 0) {
    return;
  }

  SearchInfo search_info;

  search_info.parent = (char**)calloc(graph->n, sizeof(char*));
  search_info.height = (char**)calloc(graph->n, sizeof(char*));
  search_info.visited = (char*)calloc(graph->n, sizeof(char));
  search_info.queue = create_list(constructor_char, destructor_char);

  search_info.height[start-1] = constructor_char("0\0");

  if(option == 1) {
    search_helper(graph, &search_info, start, end, 1);
    generate_search_output((&search_info)->parent, (&search_info)->height, end, 1);

  } else if(option == 2) {
    search_helper(graph, &search_info, start, end, 2);
    generate_search_output((&search_info)->parent, (&search_info)->height, end, 2);
  }

  delete_list(search_info.queue);
  free(search_info.visited);

  for(int i=0; i<graph->n; i++) {
    free(search_info.parent[i]);
    free(search_info.height[i]);
  }

  free(search_info.parent);
  free(search_info.height);
}

/**
 * @brief Get the amount of connected components in a graph
 * 
 * @param graph pointer to a graph object
 */
void find_connected_components(Graph* graph) {
  if(graph->n == 0) {
    return;
  }

  SearchInfo search_info;

  search_info.visited = (char*)calloc(graph->n, sizeof(char));
  search_info.queue = create_list(constructor_char, destructor_char);

  char** sizes = (char**)calloc(graph->n, sizeof(char*));
  int component_count = 0;
  int size = 0;

  for(int i=1; i<=graph->n; i++) {
    if(!search_info.visited[i-1]) {
      size++;

      search_info.visited[i-1] = '1';

      char* start_char = int_to_char(i);
      append(search_info.queue, start_char, 0);
      free(start_char);

      while(search_info.queue->size != 0) {
        char* cur_vertex_char = constructor_char(search_info.queue->head->data);
        int cur_vertex_int = char_to_int(cur_vertex_char);

        delete_head(search_info.queue);

        if(graph->adj_matrix != NULL) {

          for(int i=1; i<=graph->n; i++) {

            if(graph->adj_matrix[cur_vertex_int-1][i-1] == '1' && search_info.visited[i-1] != '1') {
              search_info.visited[i-1] = '1';

              char* i_char = int_to_char(i);
              append(search_info.queue, i_char, 0);

              free(i_char);

              size++;
            }
          }

        } else if(graph->adj_list != NULL) {
          Node* cur = graph->adj_list[cur_vertex_int-1]->head;

          while(cur != NULL) {

            if(search_info.visited[char_to_int(cur->data)-1] != '1') {
              search_info.visited[char_to_int(cur->data)-1] = '1';
              
              char* i_char = int_to_char(char_to_int(cur->data));
              append(search_info.queue, i_char, 0);

              free(i_char);

              size++;
            }

            cur = cur->next;
          }
        }
        free(cur_vertex_char);
      }

      sizes[component_count] = int_to_char(size);
      component_count++;
      size = 0;
    }
  }

  for(int i=0; i<component_count; i++) {
    printf("Component %d: %s vertexes.\n", i+1, sizes[i]);
  }

  delete_list(search_info.queue);
  free(search_info.visited);

  for(int i=0; i<graph->n; i++) {
    free(sizes[i]);
  }

  free(sizes);
}

void find_path(Graph* graph, int start, int end) {
  SearchInfo search_info;

  search_info.parent = (char**)calloc(graph->n, sizeof(char*));
  search_info.height = (char**)calloc(graph->n, sizeof(char*));
  search_info.visited = (char*)calloc(graph->n, sizeof(char));
  search_info.queue = create_list(constructor_char, destructor_char);

  search_info.height[start-1] = constructor_char("0\0");

  search_helper(graph, &search_info, start, end, 1);
  generate_path(&search_info, start, end, 0);

  delete_list(search_info.queue);
  free(search_info.visited);

  for(int i=0; i<graph->n; i++) {
    free(search_info.parent[i]);
    free(search_info.height[i]);
  }

  free(search_info.parent);
  free(search_info.height);
}

static void calculate_neighbor_distances(int cur_vertex, List* list, SearchInfo* search_info) {
  Node* cur = list->head;

  while(cur != NULL) {

    if(!search_info->visited[char_to_int(cur->data)-1]) {

      if(!search_info->distance[char_to_int(cur->data)-1]) {
        search_info->distance[char_to_int(cur->data)-1] = int_to_char(char_to_int(search_info->distance[cur_vertex-1]) + cur->weight);
        search_info->parent[char_to_int(cur->data)-1] = int_to_char(cur_vertex);
        

      } else if((char_to_int(search_info->distance[cur_vertex-1]) + cur->weight) < char_to_int(search_info->distance[char_to_int(cur->data)-1])) {
        search_info->distance[char_to_int(cur->data)-1] = int_to_char(char_to_int(search_info->distance[cur_vertex-1]) + cur->weight);
        search_info->parent[char_to_int(cur->data)-1] = int_to_char(cur_vertex);
      }
    }

    cur = cur->next;
  }
}

static int get_min_distance_vertex(SearchInfo* search_info) {
  Node* cur = search_info->queue->head;

  int min_distance_vertex = char_to_int(cur->data);
  int min_distance = char_to_int(search_info->distance[char_to_int(cur->data)-1]);

  cur = cur->next;

  while(cur != NULL) {
    if(search_info->distance[char_to_int(cur->data)-1]) {

      if(char_to_int(search_info->distance[char_to_int(cur->data)-1]) < min_distance) {
        min_distance = char_to_int(search_info->distance[char_to_int(cur->data)-1]);
        min_distance_vertex = char_to_int(cur->data);
      }
    }

    cur = cur->next;
  }

  return min_distance_vertex;
}

void dijkstra(Graph* graph, int start, int end) {
  SearchInfo search_info;

  search_info.parent = (char**)calloc(graph->n, sizeof(char*));
  search_info.visited = (char*)calloc(graph->n, sizeof(char));
  search_info.distance = (char**)calloc(graph->n, sizeof(char*));
  search_info.queue = create_list(constructor_char, destructor_char);

  for(int i=1; i<=graph->n; i++) {
    char* i_char = int_to_char(i);

    append(search_info.queue, i_char, 0);

    free(i_char);
  }

  search_info.distance[start-1] = constructor_char("0\0");

  int cur_vertex = start;

  while(1) {
    if(cur_vertex == end) {
      break;
    }

    calculate_neighbor_distances(cur_vertex, graph->adj_list[cur_vertex-1], &search_info);

    search_info.visited[cur_vertex-1] = '1';

    char* cur_vertex_char = int_to_char(cur_vertex);

    delete(search_info.queue, cur_vertex_char);

    free(cur_vertex_char);

    cur_vertex = get_min_distance_vertex(&search_info);
  }

  generate_path(&search_info, start, end, 1);

  delete_list(search_info.queue);
  free(search_info.visited);

  for(int i=0; i<graph->n; i++) {
    free(search_info.parent[i]);
    free(search_info.distance[i]);
  }

  free(search_info.distance);
  free(search_info.parent);
}
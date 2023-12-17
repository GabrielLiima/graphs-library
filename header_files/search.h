#ifndef SEARCH_H
#define SEARCH_H

#include "./input.h"

typedef struct SearchInfo {
  char** parent;
  char** height;
  char** distance;
  char* visited;
  List* queue;
} SearchInfo;

void search(Graph* graph, int start, int end, int option);
void find_connected_components(Graph* graph);
void find_path(Graph* graph, int start, int end);
void dijkstra(Graph* graph, int start, int end);

#endif
#ifndef SEARCH_H
#define SEARCH_H

#include "./input.h"

typedef struct SearchInfo {
  char** parent;
  char** height;
  char* visited;
  List* queue;
} SearchInfo;

void search(Graph* graph, int start, int option);
void find_connected_components(Graph* graph);

#endif
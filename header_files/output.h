#ifndef OUTPUT_H
#define OUTPUT_H

#include "./input.h"

void generate_graph_info(Graph* graph);
void generate_search_output(char** parent, char** height, int n, int option);
void generate_path(char** parent, char** height, int start, int end, int option);
void print_adj_matrix(char** adj_matrix, int n);
void print_adj_list(List** adj_list, int n);

#endif
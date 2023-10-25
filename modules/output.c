#include <stdio.h>

#include "../header_files/output.h"

void generate_graph_info(char** adj_matrix, int n, int m) {
  printf("# n = %d\n", n);
  printf("# m = %d\n", m);

  int degree = 0;

  for(int i=0; i<n; i++) {

    for(int j=0; j<n; j++) {

      if(adj_matrix[i][j] == '1' || adj_matrix[j][i] == '1') {
        degree++;
      }
    }

    printf("%d %d\n", i+1, degree);
    degree = 0;
  }
}
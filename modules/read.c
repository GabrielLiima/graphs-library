#include <stdio.h>
#include <stdlib.h>

#include "../header_files/read.h"

void read_graph() {  
  int n;
  scanf("%d", &n); 

  char** adjascent_matrix = (char**)calloc(n, sizeof(char*));

  for(int i=0; i<n; i++) {
    adjascent_matrix[i] = (char*)calloc(n, sizeof(char));
  }  

  int e1, e2;

  for(int i=0; i<n; i++) {
    scanf("%d %d", &e1, &e2);

    if(e1 < e2) {
      adjascent_matrix[e1-1][e2-1] = '1';

    } else {
      adjascent_matrix[e2-1][e1-1] = '1';  
    }
  }

  for(int i=0; i<n; i++) {

    for(int j=0; j<n; j++) {
      printf("[%d][%d] = %c\n", i, j, adjascent_matrix[i][j]);
    }
  }

  for(int i=0; i<n; i++) {
    free(adjascent_matrix[i]);
  }

  free(adjascent_matrix);
}
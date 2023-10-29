#include <stdlib.h>

#include "../header_files/utils.h"

int len(char* str) {
  int i=0;

  while(str[i] != '\0') {
    i++;
  }
  i++;

  return i;
}

char* int_to_char(int num) {
  int i = 0;
  int aux = num;

  while(aux > 0) {
    aux /= 10;
    i++;
  }
  i++;

  char *str = (char *)malloc(i * sizeof(char));

  i = 0;

  do {
    str[i++] = '0' + (num % 10);
    num /= 10;
  } while(num > 0);

  str[i] = '\0';

  int len = i;

  for(int j = 0; j < len / 2; j++) {
    char temp = str[j];
    
    str[j] = str[len - j - 1];
    str[len - j - 1] = temp;
  }

  return str;
}
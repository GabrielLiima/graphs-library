#include <stdlib.h>
#include <string.h>

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

int char_to_int(char* str) {
  int result = 0;

  while(*str != '\0') {
    result = result * 10 + (*str - '0');
    str++;
  }

  return result;
}

char* constructor_char(char* data) {
  int n = len(data);

  char* p = malloc(n * sizeof(char));
  memcpy(p, data, n * sizeof(char));

  return p;
}

void destructor_char(char* data) {
  free(data);
}
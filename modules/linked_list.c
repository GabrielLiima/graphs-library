#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../header_files/linked_list.h"

/**
 * @brief Create and initialize a node object
 * 
 * @param data string
 * @param constructor string constructor function 
 * @return Node* pointer to the node object
 */
static Node* createNode(char* data, constructor_fn constructor) {
  Node* new_node = malloc(sizeof(Node));

  new_node->data = constructor(data);
  new_node->next = NULL;

  return new_node;
}

static void deleteNode(Node* n, destructor_fn destructor) {
  destructor(n->data);

  free(n);
}

/**
 * @brief Create and initialize a list
 * 
 * @param constructor string constructor function
 * @param destructor string destructor function
 * @return List* pointer to the list object
 */
List* create_list(constructor_fn constructor, destructor_fn destructor) {
  List* l = malloc(sizeof(List));

  l->head = NULL;
  l->tail = NULL;
  l->size = 0;

  l->constructor = constructor;
  l->destructor = destructor;

  return l;
}

/**
 * @brief Append a string to a list object
 * 
 * @param l pointer to a list object
 * @param data string to be appended
 */
void append(List* l, char* data) {
  Node* new_node = createNode(data, l->constructor);

  if(l->size == 0) {
    l->head = new_node;

  } else {
    l->tail->next = new_node;
  }

  l->tail = new_node;
  l->size++;
}

/**
 * @brief Print a list object
 * 
 * @param n pointer to the starting node
 */
void print_list(Node* n) {
  char* data = NULL;

  while(n != NULL) {
    data = n->data;
    printf("%s ", data);
    
    n = n->next;
  }

  printf("\n");
}

/**
 * @brief Delete the list head
 * 
 * @param l pointer to a list object
 */
void delete_head(List* l) {
  Node* aux = l->head;

  if(l->size == 1) {
    l->tail = NULL;
  }

  l->head = l->head->next;

  deleteNode(aux, l->destructor);
  l->size--;
}

/**
 * @brief Delete a list object
 * 
 * @param l pointer to a list object
 */
void delete_list(List* l) {

  while(l->size > 0) {
    delete_head(l);
  }

  free(l);
}

/**
 * @brief Check if a string is in a list
 * 
 * @param l pointer to a list object
 * @param n string to be checked
 * @return boolean value
 */
int is_in_list(List* l, char* n) {
  Node* cur = l->head;

  while(cur != NULL) {
    if(strcmp(cur->data, n) == 0) {
      return 1;
    }

    cur = cur->next;
  }

  return 0;
}
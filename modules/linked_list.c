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
static Node* createNode(char* data, int weight, constructor_fn constructor) {
  Node* new_node = malloc(sizeof(Node));

  new_node->data = constructor(data);
  new_node->weight = weight;
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
 * @param weight weight of the node
 */
void append(List* l, char* data, int weight) {
  Node* new_node = createNode(data, weight, l->constructor);

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
  int weight = 0;

  while(n != NULL) {
    data = n->data;
    weight = n->weight;

    printf("%s (%d) ", data, weight);
    
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
 * @brief Delete the list tail
 * 
 * @param l pointer to a list object
 */
void deleteTail(List* l) {
  Node* aux = l->tail;

  if(l->size == 1) {
    l->head = NULL;
    l->tail = NULL;

  } else {
    Node* it = l->head;

    while(it->next != l->tail) {
      it = it->next;
    }

    it->next = NULL;
    l->tail = it;
  }

  deleteNode(aux, l->destructor);
  l->size--;
}

/**
 * @brief Delete an specific node
 * 
 * @param l pointer to a list object
 * @param n node to be deleted
 */
void delete(List* l, char* n) {
  Node* cur = l->head;

  int i=0;

  while(cur != NULL) {
    
    if(strcmp(cur->data, n) == 0) {
      break;
    }

    i++;
    cur = cur->next;
  }

  if(l->head == cur) {
    delete_head(l);

  } else if(l->tail == cur) {
    deleteTail(l);

  } else {
    cur = l->head;

    for(int j=0; j<i-1; j++) {
      cur = cur->next;
    }

    Node* aux = cur->next;
    cur->next = aux->next;

    deleteNode(aux, l->destructor);
    l->size--;
  }
  
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
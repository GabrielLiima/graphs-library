#include <stdlib.h>
#include <stdio.h>

#include "../header_files/linked_list.h"

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

List* createList(constructor_fn constructor, destructor_fn destructor) {
  List* l = malloc(sizeof(List));

  l->head = NULL;
  l->tail = NULL;
  l->size = 0;

  l->constructor = constructor;
  l->destructor = destructor;

  return l;
}

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

void printList(Node* n) {
  char* data = NULL;

  while(n != NULL) {
    data = n->data;
    printf("%c ", *data);
    
    n = n->next;
  }

  printf("\n");
}

static void deleteHead(List* l) {
  Node* aux = l->head;

  if(l->size == 1) {
    l->tail = NULL;
  }

  l->head = l->head->next;

  deleteNode(aux, l->destructor);
  l->size--;
}

void deleteList(List* l) {

  while(l->size > 0) {
    deleteHead(l);
  }

  free(l);
}
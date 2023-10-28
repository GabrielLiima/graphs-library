#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef char* (*constructor_fn) (char*);
typedef void (*destructor_fn) (char*);

typedef struct Node {
  char* data;
  struct Node* next;
} Node;

typedef struct List {
  Node* head;
  Node* tail;
  int size;
  constructor_fn constructor;
  destructor_fn destructor;
} List;

List* createList(constructor_fn constructor, destructor_fn destructor);
void append(List* l, char* data);
void printList(Node* n);
void deleteList(List* l);

#endif
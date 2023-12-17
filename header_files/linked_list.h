#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef char* (*constructor_fn) (char*);
typedef void (*destructor_fn) (char*);

typedef struct Node {
  char* data;
  int weight;
  struct Node* next;
} Node;

typedef struct List {
  Node* head;
  Node* tail;
  int size;
  constructor_fn constructor;
  destructor_fn destructor;
} List;

List* create_list(constructor_fn constructor, destructor_fn destructor);
void print_list(Node* n);
void delete_list(List* l);
void append(List* l, char* data, int weight);
void delete_head(List* l);
void deleteTail(List* l);
void delete(List* l, char* n);
int is_in_list(List* l, char* n);

#endif
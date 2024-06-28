#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define LEVEL 7

typedef int T;

typedef struct Node Node;
struct Node {
  Node *next;
  T value;
};

Node *pop(Node **list) {
  assert(*list);
  Node * head = *list;
  *list = head->next;
  head->next = NULL;
  return head;
}

void free_node(Node *node) {
  assert(!node || !node->next);
  free(node);
}

void destroy_list(Node **list) {
  // if (*list)
  //   destroy_list(&(*list)->next);
  // free(*list);
  // *list = NULL;
  while (*list) free_node(pop(list));
}

Node *create_node(T value) {
  Node * a = (Node*) malloc(sizeof(Node));
  a->next = NULL;
  a->value = value;
  return a;
}

size_t length(Node **list) {
  size_t len = 0;
  Node * tmp = *list;
  while(tmp) {
    len++;
    tmp = tmp->next;
  }
  return len;
}

void push(Node **list, Node *node) {
  assert(node->next == NULL);
  node->next = *list;
  (*list) = node;
}

Node** push_back(Node **list, Node *node) {
  // Node * tmp = *list;
  // while (tmp) {
  //   tmp = tmp->next;
  // }
  // tmp->next = node;
  // return list;

  while (*list) {
    list = &(*list)->next;
  }
  push(list, node);
  return list;
}

void dup(Node **dest, Node **src) {
  // Node * tmp = *src;
  // while(tmp) {
  //   *dest = create_node(tmp->value);
  //   (*dest)->next = tmp->next;
  //   tmp = tmp->next;
  // }
  Node ** tmp = dest;
  for (Node *i = *src; i; i = i->next) {
    push_back(tmp, create_node(i->value));
  }
}

Node **max(Node **list) {
  assert(*list);
  if ((*list)->next == NULL) { // len(list) = 1
    return list;
  }
  Node ** tmp = max(&(*list)->next);
  return (*tmp)->value > (*list)->value ? tmp : list;
}

Node **at(Node **list, size_t i) {
  while (i--) {
    assert(*list);
    list = &(*list)->next;
  }
  return list;

  // if (i == 0) {
  //   return list;
  // }
  // assert(*list != NULL);
  // return at(&(*list)->next, i - 1);
}

void reverse(Node **list) {
  Node * tmp = NULL;
  while (*list) {
    push(&tmp, pop(list));
  }
  *list = tmp;
}

void print(Node **list) {
  for (Node *n = *list; n; n = n->next)
    printf("%d%s", n->value, n->next ? " -> " : "\n");
}

void sort (Node ** list) {
  Node * tmp = NULL;
  while (*list) {
    push(&tmp, pop(max(list)));
  }
  *list = tmp;
}

int main() {
  Node *a = NULL, *b = NULL, *c = NULL;

  // Push && create_node
# if LEVEL >= 1
  push(&a, create_node(1));
  push(&a, create_node(2));
  push(&a, create_node(3));
  push(&a, create_node(4));

  // 4 -> 3 -> 2 -> 1
  print(&a);

  push(&c, create_node(1));
  push(&c, create_node(2));
  push(&c, create_node(3));
  push(&c, create_node(4));
  sort(&c);
  print(&c);
# endif

  // at & length
#if LEVEL >= 3
  assert(length(&a) == 4);
  assert(at(&a, 0)[0]->value == 4);
  assert(at(&a, 1)[0]->value == 3);
  assert(at(&a, 2)[0]->value == 2);
  assert(at(&a, 3)[0]->value == 1);
  assert(at(&a, 4)[0] == NULL);
# endif

  // reverse
# if LEVEL >= 4
  reverse(&a);
  // 1 -> 2 -> 3 -> 4
  print(&a);
# endif

  // pop
# if LEVEL >= 5
  push(&b, pop(&a));
  push(&b, pop(&a));

  // 3 -> 4
  print(&a);
  // 2 -> 1
  print(&b);
# endif

  // dup
# if LEVEL >= 8
  while (b) push(&a, pop(&b));
  dup(&b, &a);
  // 1 -> 2 -> 3 -> 4
  print(&a);
  // 1 -> 2 -> 3 -> 4
  print(&b);
  assert(length(&a) == 4);
  assert(length(&b) == 4);
# endif

  // Pomalý push_back
# if LEVEL >= 6
  int values[] = { 165, 552, 460, 913, 7, 225, 456, 267, 764, 802 };
  for (size_t i = 0; i < sizeof(values)/sizeof(*values); i++)
    push_back(&a, create_node(values[i]));

  assert(max(&a)[0]->value == 913);
# endif

  // Rychlý push_back
# if LEVEL >= 7
  {
    Node **end = &a;
    for (int i = 0; i < 1000*1000; i++)
      end = push_back(end, create_node(i));
  }
# endif

  // Příliš velká data pro rekurzivní implementaci
# if LEVEL >= 999
  for (int i = 0; i < 1000*1000*10; i++) push(&a, create_node(i));
  reverse(&a);
  // at(&a, 3) = 9999996
  printf("at(&a, %d) = %d\n", 3, at(&a, 3)[0]->value);
  // max: 9999999
  printf("max: %d\n", max(&a)[0]->value);
  // lenght: 11000014
  printf("lenght: %d\n", (int)length(&a));
# endif

# if LEVEL >= 2
  destroy_list(&b);
  destroy_list(&a);
# endif
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

typedef struct NODE {
    struct NODE * next;
    int data;
} node;

// add node to end of linked list and return last node
node * createNode (node * next, int data) {
    node * tmp = (node*) malloc(sizeof(*tmp));
    tmp->data = data;
    tmp->next = next;
    return tmp;
}

// free linked list
void freeNode (node * a) {
    if (!a) {
        return;
    }
    node * tmp = a->next;
    free(a);
    freeNode(tmp);
}

// delete node at 'pos' 
node * deleteNode (node * a, int pos) {
    node * head = a;
    if (pos == 0) {
        head = a->next;
        free(a);
        return head;
    }
    node * prev = NULL;
    for (int i = 0; i < pos; i++) {
        prev = a;
        a = a->next;
    }
    prev->next = a->next;
    free(a);
    return head;
}

// add node to end of linked list and return first node
node * insert_tail (node * a, int data) {
    node * head = a;
    while (a) {
        if (a->next == NULL) {
            node * tmp = (node*) malloc(sizeof(*tmp));
            tmp->data = data;
            tmp->next = NULL;
            a->next = tmp;
            break;
        }
        a = a->next;
    }
    return head;
}

// add node to position
node * insert_at_position (node * a, int data, int pos) {
    node * head = a;
    if (pos == 0) {
        a = createNode(head, data);
        return a;
    }
    node * prev = NULL;
    for (int i = 0; i < pos; i++) {
        prev = a;
        a = a->next;
    }
    node * tmp = a;
    a = createNode(tmp, data);
    prev->next = a;
    return head;
}

// print linked list
void print_nodes (node * a) {
    while(a) {
        if (a->next == NULL) {
            printf("%d", a->data);
        } else {
            printf("%d - ", a->data);
        }
        a = a->next;
    }
    printf("\n");
}

// print linked list in reverse order
void print_reverse (node * a) {
    int arr[100];
    int size = 0;
    while (a) {
        arr[size++] = a->data;
        a = a->next;
    }
    for (int i = size-1; i >= 0; --i) {
        if (i == 0) {
            printf(" %d", arr[i]);
        } else {
            printf("%d - ", arr[i]);
        }
    }
    printf("\n");
}

int main (void) {
    node * a = NULL;
    //                        index
    a = createNode(NULL, 4); // 3
    a = createNode(a, 3);    // 2
    a = createNode(a, 2);    // 1
    a = createNode(a, 1);    // 0
    // pointer to first node
    node * head = a;
    // a = 1 - 2 - 3 - 4
    print_nodes(head);

    a = head;
    a = deleteNode(a, 2);
    // a = 1 - 2 - 4
    print_nodes(a);
    
    a = head;
    a = insert_at_position(a, 5, 1);
    // a = 1 - 5 - 2 - 4
    print_nodes(a);

    a = head;
    a = insert_tail(a, 6);
    // a = 1 - 5 - 2 - 4 - 6
    print_nodes(a);

    // insert_tail returns first node -> no need to a = head;
    print_reverse(a);    
    // a = 6 - 4 - 2 - 5 - 1

    a = head;
    a = insert_at_position(a, 7, 0);
    head = a;
    // a = 7 - 1 - 5 - 2 - 4 - 6
    print_nodes(a);

    a = head;
    a = deleteNode(a, 0);
    // a = 1 - 5 - 2 - 4 - 6
    print_nodes(a);

    freeNode(a);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

// C version if struct
typedef struct {
    int * vector;
    int size, end;
} Array;

void array_init (Array * a) {
    a->vector = NULL;
    a->size = 0;
    a->end = 0;
}

void array_alloc (Array * a, int n) {
    a->size = n;
    // sizeof(*vector) -> no need to worry about datatype
    a->vector = (int*) malloc(n * sizeof(int));
}

void array_resize (Array * a) {
    a->size *= 2;
    a->vector = (int*) realloc(a->vector, a->size * sizeof(int));
}

void array_push_back (Array * a, int n) {
    if (a->size < (a->end + 1)) {
        array_resize(a);
    }
    a->vector[a->end++] = n;
}

void array_push_front (Array * a, int n) {
    if (a->size < (a->end + 1)) {
        array_resize(a);
    }
    for (int i = a->end; i > 0; i--) {
        a->vector[i] = a->vector[i-1];
    }
    a->vector[0] = n;
    a->end++;
}

void array_print (Array * a) {
    for (int i = 0; i < a->end; i++) {
        if (i == (a->end - 1))
            printf("%d\n", a->vector[i]);
        else
            printf("%d, ", a->vector[i]);
    }
}

int array_empty (Array * a) {
    if (a->size > 0)
        return 0;
    return 1;
}

void array_free_arr (Array * a) {
    free(a->vector);
}

int main (void) {
    Array arr;
    array_init(&arr);
    int n = 6;
    array_alloc(&arr, n);
    printf("empty\nsize: %d, end: %d\n", arr.size, arr.end);
    printf("--------------\n");

    for (int i = 0; i < 10; i++) {
        array_push_back(&arr, i);
    }

    printf("push_back\n");
    array_print(&arr);
    printf("size: %d, end: %d\n", arr.size, arr.end);
    printf("--------------\n");

    array_push_front(&arr, 66);
    printf("push_front\n");
    array_print(&arr);
    printf("size: %d, end: %d\n", arr.size, arr.end);

    array_free_arr(&arr);

    return 0;
}
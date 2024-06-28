#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

// C++ version of struct
typedef struct {
    int * vector;
    int size = 0;
    int end = 0;

    int * array_alloc (int n) {
        size = n;
        // sizeof(*vector) -> no need to worry about datatype
        vector = (int*) malloc(size * sizeof(int));
        return vector;
    }

    void array_resize () {
        size *= 2;
        vector = (int*) realloc(vector, size * sizeof(int));
    }
    
    int * array_push_back (int n) {
        if (size < (end + 1)) {
            array_resize();
        }

        vector[end++] = n;
        return vector;
    }
    
    int * array_push_front (int n) {
        if (size < (end + 1)) {
            array_resize();
        }

        for (int i = end; i > 0; i--) {
            vector[i] = vector[i-1];
        }
        vector[0] = n;
        end++;
        return vector;
    }

    void array_print () {
        for (int i = 0; i < end; i++) {
            if (i == (end - 1))
                printf("%d\n", vector[i]);
            else
                printf("%d, ", vector[i]);
        }
    }

    int array_empty () {
        if (size > 0)
            return 0;
        return 1;
    }
    
    void array_free () {
        free(vector);
    }
} Array;


int main (void) {
    Array arr;
    int n = 6;
    arr.array_alloc(n);
    printf("empty\nsize: %d, end: %d\n", arr.size, arr.end);
    printf("--------------\n");

    for (int i = 0; i < 10; i++) {
        arr.array_push_back(i);
    }

    printf("push_back\n");
    arr.array_print();
    printf("size: %d, end: %d\n", arr.size, arr.end);
    printf("--------------\n");

    arr.array_push_front(66);
    printf("push_front\n");
    arr.array_print();
    printf("size: %d, end: %d\n", arr.size, arr.end);

    arr.array_free();

    return 0;
}
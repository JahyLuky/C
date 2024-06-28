#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>

typedef struct {
    long double x;
    long double y;
    size_t size;
    size_t end; // Number of used size
    char name[200];
} Plane;

typedef struct {
    size_t x;
    size_t y;
} Pair;

/*
    Prints plane names with coordinates
*/
void print_plane (Plane * a) {
    printf("Size: %ld, end: %ld\n", a->size, a->end);
    for (size_t i = 0; i < a->end; i++) {
        printf("Name: %s\n x: %Lf, y: %Lf\n", a[i].name, a[i].x, a[i].y);
    }
}

/*
    Counts distance between X (x1, x2) and Y (y1, y2)
*/
long double get_distance (long double x1, long double x2, 
                          long double y1, long double y2) {
    long double result = 0;
    result = sqrt(pow((y1-x1), 2) + pow((y2-x2), 2));
    return result;
}

// Taken from my laboratory (cv05: 01-kruznice.c)
int equal (long double x, long double y) {
    return fabs(x - y) <= 1e-9 * (fabs(x) + fabs(y));
}

/*
    Finds closest distancec between planes and prints their names
*/
void get_closest (Plane * a) {
    long double distance = 0, min = 0;
    size_t id = 0, size_arr = a->end;
    Pair * arr = (Pair*) malloc(size_arr * sizeof(Pair));

    for (size_t i = 0; i < a->end-1; i++) {
        for (size_t j = i+1; j < a->end; j++) {
            distance = get_distance(a[i].x, a[i].y, a[j].x, a[j].y);
            // Set min to fisrt distance
            if (i == 0 && j == 1) {
                min = distance;
            }
            
            // New pair
            if (equal(min, distance)) {
                if (size_arr <= id) {
                    size_arr *= 2;
                    arr = (Pair*) realloc(arr, size_arr * sizeof(Pair));
                }
                // Save positions of names (in "planes")
                arr[id].x = i; // TODO: array.init
                arr[id].y = j;
                // Number of pairs
                id++;
            }
            // Found new min, reset id
            else if (min > distance) {
                min = distance;
                id = 0;
                // Save positions of names (in "planes")
                arr[id].x = i;
                arr[id].y = j;
                // Number of pairs
                id++;
            }
        }
    }

    printf("Vzdalenost nejblizsich letadel: %Lf\n", min);
    printf("Nalezenych dvojic: %ld\n", id);

    // Print all names of closest planes
    for (size_t i = 0; i < id; i++)
    {
        printf("%s - %s\n", a[arr[i].x].name, a[arr[i].y].name);
    }

    free(arr);
}

/*
    Loads input from stdin
    Returns:
    1 -> True (everything was right)
    0 -> False (wrong input)
*/
void get_input () {
    // At start alloc 128 planes
    Plane * planes = (Plane*) malloc(128 * sizeof(Plane));
    planes->size = 128;
    planes->end = 0;
    int in = 0;
    size_t id = 0;
    printf("Pozice letadel:\n");

    while(1) {
        // End of input occurred
        if (feof(stdin)) {
            // Less than 2 planes
            if (id <= 2) {
                printf("Nespravny vstup.\n");
                break;
            }
            planes->end = id-1;
            get_closest(planes);
            break;
        }

        if (planes->size <= id) {
            planes->size *= 2;
            planes = (Plane*) realloc(planes, planes->size * sizeof(Plane));
        }

        // Save input to "planes"
        in = scanf("%Lf,%Lf: %199s", &planes[id].x, &planes[id].y, planes[id].name);
        
        // Wrong number of inputs, skip new line (-1)
        if (in != 3 && in != -1) {
            printf("Nespravny vstup.\n");
            break;
        }
        // Number of planes
        id++;
    }

    free(planes);
}

int main (void) {
    get_input();
    return 0;
}
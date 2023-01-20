/*
Parafráze zadání
 - identifikátor: retezec o delce max 64
Na vstupu jsou data ve formátu identifikátor [ číslo, číslo, číslo, číslo ] 
Jedná se o unikátní identifikátor kostky domina a 4 čísla, která jsou na dominu v pořadí v záporném směru po obvodu. 
Každá kostka domina má 4 čísla, na každé straně jedno a můžeme s ní libovolně otáčet. 
Proto jsou naříklad kostky [1, 2, 3, 4] a [3, 4, 1, 2] stejné.

Úkolem je načíst na vstupu všechny kostky domina, a vypsat počet unikátních kostek.
Následně vypsat všechny duplikáty. Např vstup.

a [1, 2, 3, 4]
b [2, 3, 4, 5]
c [2, 3, 4, 1]
d [4, 5, 2, 3]
e [5, 2, 3, 4]
f [4, 3, 2, 1]
bude mít výstup

Unikatni: 3
Duplikaty:
a = c
b = d = e
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

typedef struct DOM {
    int n, x, y;
} domi;

typedef struct kostkaT {
    int uniq;
    domi * dom;
    char name[64];
} kostka;

void print_domino (kostka k) {
    printf("[%d,    %d,     %d,     %d]\n", k.dom[0].n, k.dom[1].n, k.dom[2].n, k.dom[3].n);
    printf("(%d, %d)|(%d, %d)|(%d, %d)|(%d, %d)\n", k.dom[0].x, k.dom[0].y, k.dom[1].x, k.dom[1].y, k.dom[2].x, k.dom[2].y, k.dom[3].x, k.dom[3].y);
}

int isDom (kostka k1, kostka k2) {
    int match = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (k1.dom[i].n == k2.dom[j].n) {
                if ((k1.dom[i].x == k2.dom[j].x)
                    &&
                    (k1.dom[i].y == k2.dom[j].y)) {
                        match++;
                    }
            }
        }
    }
    if (match == 4) {
        return 1;
    }
    return 0;
}

void free_kostka (kostka * k, int n) {
    for (int i = 0; i < n; i++) {
        free(k[i].dom);
    }
    free(k);
}

int main (void) {
    kostka * k;
    k = (kostka*) malloc(1 * sizeof(kostka));
    int n = 0, size = 1, in = 0, a = 0, b = 0, c = 0, d = 0;
    char input;
    while (1) {
        if (feof(stdin)) {
            break;
        }
        k[n].dom = (domi*) malloc (4 * sizeof(domi));
        in = scanf("%s [ %d , %d , %d , %d %c ",k[n].name,&a,&b,&c,&d, &input);
        if (in == -1) {
            if (n == 0) {
                free(k[0].dom);
                free(k);
                return 0;
            }
            continue;
        }
        if (strlen(k[n].name) > 64 || in != 6) {
            printf("err1\n");
            if (n == 0) {
                free(k[0].dom);
                free(k);
            } else {
            free_kostka(k, n);
            }
            return 1;
        }      
        if (input != ']') {
            printf("err2\n");
            if (n == 0) {
                free(k[0].dom);
                free(k);
            } else {
                free_kostka(k, n);
            }
            return 1;
        }
        
        k[n].dom[0].n = a;
        k[n].dom[0].x = b;
        k[n].dom[0].y = d;

        k[n].dom[1].n = b;
        k[n].dom[1].x = c;
        k[n].dom[1].y = a;

        k[n].dom[2].n = c;
        k[n].dom[2].x = d;
        k[n].dom[2].y = b;

        k[n].dom[3].n = d;
        k[n].dom[3].x = a;
        k[n].dom[3].y = c;

        k[n].uniq = 0;

        n++;
        if (n == size) {
            size *= 2;
            k = (kostka*) realloc(k, size * sizeof(kostka));
        }
    }

    int * arr = (int*) malloc (10 * sizeof(int));
    int tmp = 0, idx = 0, cnt = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 1; j < n; j++) {
            if (i == j || k[j].uniq != 0) { continue; }
            if (isDom(k[i], k[j])) {
                if (tmp != 1) {
                    tmp = 1;
                    arr[idx] = idx+1;
                    idx++;
                }
                k[j].uniq = idx;
                cnt++;
            }
        }
        if (tmp == 1) {
            k[i].uniq = idx;
        }
        tmp = 0;
    }
    arr[idx] = -1;
    printf("Unikatni: %d\n", n - cnt);

    int id = 0;
    tmp = 0;
    printf("Duplikaty:\n");
    for (int i = 0; ; i++) {
        if (k[i].uniq == arr[id]) {
            if (tmp == 0) {
                printf("%s", k[i].name);
                tmp = 1;
            }
            else {
                printf(" = %s", k[i].name);
            }
        }
        if (i+1 == n) {
            if (arr[id+1] == -1) {
                break;
            }
            i = 0;
            id++;
            if (tmp == 1) {
                tmp = 0;
                printf("\n");
            }
        }
    }
    printf("\n");
    
    free_kostka(k, n);
    free(arr);
    
    return 0;
}
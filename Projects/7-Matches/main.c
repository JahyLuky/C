#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

int match_jump (int * arr, int n, int k, int cnt) {
    if (n == 0) {
        return 0;
    }

    int res = match_jump(arr, n, k, cnt++);

    for (int i = 0; i < n; i++) {
        res += 
    }
    return res;
}

void get_matches (int n, int k) {
    int * arr = (int*) malloc(n * sizeof(int));
    // arr -> 2=2matches, 1=1match, 0=0matches
    for (int i = 0; i < n; i++) {
        arr[i] = 1;
    }
    
    printf("res: %d\n", match_jump(arr, n, k, 0));
}

int main (void) {
    int n = 0, k = 0;

    printf("Pocet sirek:\n");
    if (scanf("%d", &n) != 1 || n < 1) {
        printf("Nespravny vstup.\n");
        return 0;
    }

    printf("Velikost skoku:\n");
    if (scanf("%d", &k) != 1 || k < 0) {
        printf("Nespravny vstup.\n");
        return 0;
    }

    get_matches(n, k);

    return 1;
}
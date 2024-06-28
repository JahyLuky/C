#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

int find_substring(char *a, char *b) {
    char *p1 = a;
    char *p2 = b;
    char *tmp;
    size_t len1 = strlen(a);
    size_t len2 = strlen(b);
    printf("%ld a %ld\n", len1, len2);
    size_t i = 0, j = 0;
    
    int flag = 0;

    for (; i < len1; i++) {
        if (tolower(*p1) == tolower(*p2)) {
            tmp = p1;
            for (j = 0; j < len2; j++) {
                if (tolower(*tmp) == tolower(*p2)) {
                    printf("%c == %c\n", *tmp, *p2);
                    tmp++;
                    p2++;
                    flag++;
                } else {
                    break;
                }
            }
            printf("%d\n", flag);
            flag = 0;
            printf("j %ld == %ld len2\n", j, len2);
            if (j == len2) {
                if (len1 == len2) {
                    return 2;
                }
                return 1;
            }
        }
        p1++;
    }
    return 0;
}

int find_substring2(char *a, char *b) {
    size_t len1 = strlen(a);
    size_t len2 = strlen(b);
    //printf("%s %s\n", a, b);
    //printf("%ld a %ld\n", len1, len2);
    size_t i = 0, j = 0;
    size_t flag = 0;

    for (; i < len1; i++) {
        if (tolower(a[i]) == tolower(b[0])) {
            flag = 0;
            for (j = 0; j < len2; j++) {
                //printf("%c == %c\n", a[j], b[j]);
                if (tolower(a[i+j]) == tolower(b[j])) {
                    flag++;
                    if (flag == len2) {
                        break;
                    }
                } else {
                    break;
                }
            }
            printf("\n");
            if (flag == len2) {
                if (len1 == len2) {
                    return 2;
                }
                return 1;
            }
        }
    }
    return 0;
}

int main (void) {
    
    printf("res: %d\n", find_substring2("tenrandomtypekjekekw...", "kekw"));
    return 1;
}
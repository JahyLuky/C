#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

typedef struct {
    char *name;
    int shelf;
    size_t size;
    size_t end;
} item;

typedef struct {
    char *shop_name;
    char *item_name;
    size_t size;
    size_t end;
    int shelf;
    size_t list;
    size_t match;
} shopping_list;

void create_shelf(item **a, char **str, size_t id, int num_shelf) {
    size_t len = strlen(*str) + 1;
    (*a)[id].name = (char *) malloc(len * sizeof(char));
    strncpy((*a)[id].name, *str, len - 2);
    (*a)[id].name[len - 2] = '\0';
    (*a)[id].shelf = num_shelf;

    // id idex from 0, size index from 1
    if (id == ((*a)->size - 1)) {
        (*a)->size *= 2;
        (*a) = (item *) realloc((*a), (*a)->size * sizeof(item));
    }
}

void create_shopping_list(shopping_list **a, char **str, size_t id, size_t list) {
    size_t len = strlen(*str) + 1;
    size_t del = 1;

    // last char is new line
    if ((*str)[len - 2] == '\n') {
        del = 2;
    }

    (*a)[id].item_name = (char *) malloc(len * sizeof(char));
    strncpy((*a)[id].item_name, *str, len - del);
    (*a)[id].item_name[len - del] = '\0';
    (*a)[id].shop_name = NULL;
    (*a)[id].list = list;
    (*a)[id].match = 0;

    // id idex from 0, size index from 1
    if (id == ((*a)->size - 1)) {
        (*a)->size *= 2;
        (*a) = (shopping_list *) realloc((*a), (*a)->size * sizeof(shopping_list));
    }
}

int get_digit (char ** str) {
    char * p = *str;
    int len = strlen(*str);
    int i = len-2, cnt = 0, j = 0;
    while (i != 0) {
        if (isdigit(p[i]) == 0) {
            return -1;
        }
        cnt += (p[i] - '0') * (int)pow(10, j);
        j++;
        i--;
    }
    return cnt;
}

int read_input(item **shelf, shopping_list **shop_list) {
    shop_list[0]->end = 0;
    shelf[0]->end = 0;
    int in = 0, first_hash = 0, id_shelf = -1, last_shelf = -1;
    size_t cap = 0, list = 0;
    size_t id_s = 0, id_l = 0;
    int get_shelfs = 1, cnt = 0;
    char *str = NULL;
    while (1) {
        if (feof(stdin)) {
            free(str);
            // if (in != -1) {
            //     return 0;
            // }
            
            shop_list[0]->end = id_l;
            return 1;
        }

        in = getline(&str, &cap, stdin);
        //printf("in: %d\n", in);
        if (str[0] == '#') {
            
            id_shelf = get_digit(&str);
            //printf("shelf: %d\n", id_shelf);
            if (id_shelf != -1 && id_shelf != (last_shelf+1)) {
                free(str);
                return 0;
            }
            if (id_shelf <= last_shelf || (last_shelf == -1 && id_shelf != 0) || id_shelf == -1) {
                free(str);
                return 0;
            }
            last_shelf++;
            first_hash++;
            continue;
        }
        // new line as last input (ctrl+D)
        if (in == -1) {
            if (cnt == 0) {
                free(str);
                return 0;
            }
            continue;
        }

        // new line that indicates end of shelf input
        if (in == 1) {
            get_shelfs = 0;
            shelf[0]->end = id_s;
            list++;
        }

        if (get_shelfs) {
            if (last_shelf == -1) {
                free(str);
                return 0;
            }
            create_shelf(shelf, &str, id_s++, id_shelf);
            shelf[0]->end += 1;
        } else if (in != 1 && get_shelfs == 0) {
            if (last_shelf == -1) {
                free(str);
                return 0;
            }
            create_shopping_list(shop_list, &str, id_l++, list);
        }
        cnt++;
    }
}

int find_substring(char *a, char *b) {
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
            //printf("\n");
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

void find_optimal_shopping(item **shelf, shopping_list **shop_list) {
    size_t i = 0, j = 0, len = 0;
    int found = 0;
    for (i = 0; i < (*shop_list)[0].end; i++) {
        for (j = 0; j < (*shelf)[0].end; j++) {
            found = find_substring((*shelf)[j].name, (*shop_list)[i].item_name);
            if (found == 2) {
                //printf("f: %d -> %s jako %s\n", found, (*shop_list)[i].item_name, (*shelf)[j].name);
                if ((*shop_list)[i].shop_name != NULL)
                    free((*shop_list)[i].shop_name);

                len = strlen((*shelf)[j].name) + 1;
                (*shop_list)[i].shop_name = (char *) malloc(len * sizeof(char));
                strcpy((*shop_list)[i].shop_name, (*shelf)[j].name);
                (*shop_list)[i].shelf = (*shelf)[j].shelf;
                (*shop_list)[i].match = 2;

                found = 2;
                break;
            }
            if (found == 1 && (*shop_list)[i].match != 2 && (*shop_list)[i].match != 1) {
                //printf("%s jako %s\n", (*shop_list)[i].item_name, (*shelf)[j].name);
                //printf("f: %d -> %s jako %s\n", found, (*shop_list)[i].item_name, (*shelf)[j].name);
                if ((*shop_list)[i].shop_name != NULL)
                    free((*shop_list)[i].shop_name);
                len = strlen((*shelf)[j].name) + 1;
                (*shop_list)[i].shop_name = (char *) malloc(len * sizeof(char));
                strcpy((*shop_list)[i].shop_name, (*shelf)[j].name);
                (*shop_list)[i].shelf = (*shelf)[j].shelf;
                (*shop_list)[i].match = 1;
                found = 1;
            }
        }
        if ((*shop_list)[i].match != 0) {
            found = 0;
        } else {
            //printf("%s jako N/A\n", (*shop_list)[i].item_name);
            (*shop_list)[i].shop_name = (char *) malloc(4 * sizeof(char));
            strcpy((*shop_list)[i].shop_name, "N/A");
            // max values of int
            (*shop_list)[i].shelf = __INT_MAX__;
        }
    }
}

int compare(const void *s1, const void *s2) {
    const shopping_list *tmp1 = (const shopping_list *) s1;
    const shopping_list *tmp2 = (const shopping_list *) s2;
    if (tmp1->list == tmp2->list) {
        if (tmp1->shelf < tmp2->shelf) return -1;
        if (tmp1->shelf > tmp2->shelf) return 1;
        else return 0;
    }
    return 0;
}

void print_optimal_shoppping(shopping_list **a, size_t len) {
    size_t last_list = 1, cnt = 0;

    qsort((*a), len, sizeof(shopping_list), compare);
    
    printf("Optimalizovany seznam:\n");
    for (size_t i = 0; i < len; i++) {
        //printf("[i]=%ld, list: %ld\n", i, (*a)[i].list);
        if ((*a)[i].list != last_list) {
            last_list++;
            cnt = 0;
            printf("Optimalizovany seznam:\n");
        }
        if ((*a)[i].shelf == __INT_MAX__) {
            printf(" %ld. %s -> %s\n", cnt++, (*a)[i].item_name, (*a)[i].shop_name);
        } else {
            printf(" %ld. %s -> #%d %s\n", cnt++, (*a)[i].item_name, (*a)[i].shelf, (*a)[i].shop_name);
        }
    }
    //printf("\n");
}

void free_shelf(item **a, size_t len) {
    if (len <= 0) {
        free(*a);
        return;
    }
    for (size_t i = 0; i < len; i++) {
        free((*a)[i].name);
    }
    free(*a);
}

void free_shop_list(shopping_list **a, size_t len) {
    if (len <= 0) {
        free(*a);
        return;
    }
    for (size_t i = 0; i < len; i++) {
        if ((*a)[i].item_name != NULL)
            free((*a)[i].item_name);
        if ((*a)[i].shop_name != NULL)
            free((*a)[i].shop_name);
    }
    free(*a);
}

int main (void) {
    size_t tmp = 32;
    item *shelf = (item *) malloc(tmp * sizeof(item));
    shelf->size = tmp;

    shopping_list *shop_list = (shopping_list *) malloc(tmp * sizeof(shopping_list));
    shop_list->size = tmp;

    int in = read_input(&shelf, &shop_list);

    size_t len = shop_list[0].end;
    size_t len_shelf = shelf[0].end;
    //printf("len %ld, len_shelf %ld\n", shop_list[0].end, len_shelf);
    if (in == 0 || (len == 0)) {
        printf("Nespravny vstup.\n");
        free_shop_list(&shop_list, len);
        free_shelf(&shelf, len_shelf);
        return 0;
    }
    // printf("shelf:\n");
    // for (size_t i = 0; i < shelf[0].end; i++) {
    //     printf("%s\n", shelf[i].name);
    // }
    // printf("-----------------------\n");
    // printf("shop_list:\n");
    // shop_list[0].end -= 1;
    // for (size_t i = 0; i < shop_list[0].end; i++) {
    //     printf("(%ld) %s ->#%d\n", shop_list[i].list, shop_list[i].item_name, shop_list[i].shelf);
    // }

    find_optimal_shopping(&shelf, &shop_list);

    // for (size_t i = 0; i < shop_list[0].end; i++) {
    //     printf("(%ld) %s ->#%d", shop_list[i].list, shop_list[i].item_name, shop_list[i].shelf);
    //     printf(", list: %ld\n", shop_list[i].list);
    // }

    print_optimal_shoppping(&shop_list, len);

    free_shop_list(&shop_list, len);
    free_shelf(&shelf, len_shelf);
    return 1;
}
#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct TItem {
    struct TItem *m_Next;
    char *m_Name;
    char m_Secret[24];
} TITEM;
#endif /* __PROGTEST__ */

void print_list (TITEM * a) {
    while (a) {
        printf("%s\n", a->m_Name);
        a = a->m_Next;
    }
}

TITEM *newItem(const char *name,
               TITEM *next) {
    TITEM * tmp = (TITEM*) malloc(sizeof(TITEM));
    tmp->m_Name = strdup(name);
    tmp->m_Next = next;
    strcpy(tmp->m_Secret, "\0");
    return tmp;
}

TITEM * sort_merged_lists(TITEM *x, TITEM *y, int ascending) {
    if (x == NULL) {
        return y;
    }
    if (y == NULL) {
        return x;
    }

    TITEM * tmp = NULL;
    
    // asc order
    if (ascending != 0) {
        if (strcmp(x->m_Name, y->m_Name) <= 0) {
            tmp = x;
            tmp->m_Next = sort_merged_lists(x->m_Next, y, ascending);
        } else {
            tmp = y;
            tmp->m_Next = sort_merged_lists(x, y->m_Next, ascending);
        }
    // desc order
    } else {
        if (strcmp(x->m_Name, y->m_Name) >= 0) {
            tmp = x;
            tmp->m_Next = sort_merged_lists(x->m_Next, y, ascending);
        } else {
            tmp = y;
            tmp->m_Next = sort_merged_lists(x, y->m_Next, ascending);
        }
    }
    return tmp;
}

void split_list (TITEM * l, TITEM **x, TITEM **y) {
    // 0 or 1 element to split
    if (l == NULL || l->m_Next == NULL) {
        *x = l;
        *y = NULL;
        return;
    }

    TITEM * fast = l->m_Next;
    TITEM * slow = l;

    // slow.next is in the "middle" of l
    while (fast) {
        fast = fast->m_Next;
        if (fast) {
            fast = fast->m_Next;
            slow = slow->m_Next;
        }
    }

    // x points to start of l
    *x = l;
    // y points to middle of l
    *y = slow->m_Next;
    // to split l into halfs
    slow->m_Next = NULL;
}

void merge_sort (TITEM ** l, int ascending) {
    // l is empty or there is single elemnt
    if (*l == NULL || (*l)->m_Next == NULL) {
        return;
    }

    TITEM *x, *y;

    split_list(*l, &x, &y);

    merge_sort(&x, ascending);
    merge_sort(&y, ascending);

    *l = sort_merged_lists(x, y, ascending);
}

TITEM *sortList(TITEM *l, int ascending) {
    // empty or 1 element -> already sorted
    if (l == NULL || l->m_Next == NULL) {
        return l;
    }

    merge_sort(&l, ascending);
    //print_list(l);
    return l;
}

void freeList(TITEM *src) {
    if (src == NULL) {
        return;
    }
    TITEM *tmp = src->m_Next;
    free(src->m_Name);
    free(src);
    return freeList(tmp);
}

#ifndef __PROGTEST__
int main(int argc, char *argv[]) {
    TITEM *l;
    char tmp[50];

    l = NULL;
    l = newItem("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", l);
    l = newItem("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab", l);
    l = newItem("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaac", l);
    l = newItem("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaC", l);
    l = newItem("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaB", l);
    l = newItem("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaA", l);
    assert(l
           && !strcmp(l->m_Name, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaA"));
    assert(l->m_Next
           && !strcmp(l->m_Next->m_Name, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaB"));
    assert(l->m_Next->m_Next
           && !strcmp(l->m_Next->m_Next->m_Name, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaC"));
    assert(l->m_Next->m_Next->m_Next
           && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaac"));
    assert(l->m_Next->m_Next->m_Next->m_Next
           && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab"));
    assert(l->m_Next->m_Next->m_Next->m_Next
           && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Name, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"));
    assert(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
    l = sortList(l, 1);
    //print_list(l);
    assert(l
           && !strcmp(l->m_Name, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaA"));
    assert(l->m_Next
           && !strcmp(l->m_Next->m_Name, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaB"));
    assert(l->m_Next->m_Next
           && !strcmp(l->m_Next->m_Next->m_Name, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaC"));
    assert(l->m_Next->m_Next->m_Next
           && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"));
    assert(l->m_Next->m_Next->m_Next->m_Next
           && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab"));
    assert(l->m_Next->m_Next->m_Next->m_Next->m_Next
           && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Name, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaac"));
    freeList(l);

    l = NULL;
    l = newItem("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", l);
    l = newItem("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab", l);
    l = newItem("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaac", l);
    l = newItem("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaC", l);
    l = newItem("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaB", l);
    l = newItem("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaA", l);
    assert(l
           && !strcmp(l->m_Name, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaA"));
    assert(l->m_Next
           && !strcmp(l->m_Next->m_Name, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaB"));
    assert(l->m_Next->m_Next
           && !strcmp(l->m_Next->m_Next->m_Name, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaC"));
    assert(l->m_Next->m_Next->m_Next
           && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaac"));
    assert(l->m_Next->m_Next->m_Next->m_Next
           && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab"));
    assert(l->m_Next->m_Next->m_Next->m_Next
           && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Name, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"));
    assert(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
    l = sortList(l, 1);
    //print_list(l);
    assert(l
           && !strcmp(l->m_Name, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaA"));
    assert(l->m_Next
           && !strcmp(l->m_Next->m_Name, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaB"));
    assert(l->m_Next->m_Next
           && !strcmp(l->m_Next->m_Next->m_Name, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaC"));
    assert(l->m_Next->m_Next->m_Next
           && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"));
    assert(l->m_Next->m_Next->m_Next->m_Next
           && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab"));
    assert(l->m_Next->m_Next->m_Next->m_Next->m_Next
           && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Name, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaac"));
    freeList(l);

    l = NULL;
    l = newItem("cWTNHtcQPcibDllHjoeZhWTNHtcQPcibDllHjoeZ123345678", l);
    l = newItem("BLwu5DIURQEObZKS6vkSMLwu5DIURQEObZKS6vkS123345678", l);
    l = newItem("yz7Izph3du6IQYeNuFl7vz7Izph3du6IQYeNuFl7123345678", l);
    l = newItem("eT5L97rV9wWvmu8pyGScrT5L97rV9wWvmu8pyGSc123345678", l);
    l = newItem("AoGVK82AnifdpeMEuZ3xKoGVK82AnifdpeMEuZ3x123345678", l);
    l = newItem("EoGVK82AnifdpeMEuZ3xKoGVK82AnifdpeMEuZ3x123345678", l);
    assert(l
           && !strcmp(l->m_Name, "EoGVK82AnifdpeMEuZ3xKoGVK82AnifdpeMEuZ3x123345678"));
    assert(l->m_Next
           && !strcmp(l->m_Next->m_Name, "AoGVK82AnifdpeMEuZ3xKoGVK82AnifdpeMEuZ3x123345678"));
    assert(l->m_Next->m_Next
           && !strcmp(l->m_Next->m_Next->m_Name, "eT5L97rV9wWvmu8pyGScrT5L97rV9wWvmu8pyGSc123345678"));
    assert(l->m_Next->m_Next->m_Next
           && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "yz7Izph3du6IQYeNuFl7vz7Izph3du6IQYeNuFl7123345678"));
    assert(l->m_Next->m_Next->m_Next->m_Next
           && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "BLwu5DIURQEObZKS6vkSMLwu5DIURQEObZKS6vkS123345678"));
    assert(l->m_Next->m_Next->m_Next->m_Next
           && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Name, "cWTNHtcQPcibDllHjoeZhWTNHtcQPcibDllHjoeZ123345678"));
    assert(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
    l = sortList(l, 1);
    //print_list(l);
    assert(l
           && !strcmp(l->m_Name, "AoGVK82AnifdpeMEuZ3xKoGVK82AnifdpeMEuZ3x123345678"));
    assert(l->m_Next
           && !strcmp(l->m_Next->m_Name, "BLwu5DIURQEObZKS6vkSMLwu5DIURQEObZKS6vkS123345678"));
    assert(l->m_Next->m_Next
           && !strcmp(l->m_Next->m_Next->m_Name, "EoGVK82AnifdpeMEuZ3xKoGVK82AnifdpeMEuZ3x123345678"));
    assert(l->m_Next->m_Next->m_Next
           && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "cWTNHtcQPcibDllHjoeZhWTNHtcQPcibDllHjoeZ123345678"));
    assert(l->m_Next->m_Next->m_Next->m_Next
           && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "eT5L97rV9wWvmu8pyGScrT5L97rV9wWvmu8pyGSc123345678"));
    assert(l->m_Next->m_Next->m_Next->m_Next->m_Next
           && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Name, "yz7Izph3du6IQYeNuFl7vz7Izph3du6IQYeNuFl7123345678"));
    freeList(l);

    l = NULL;
    l = sortList(l, 0);
    assert(l == NULL);

    l = newItem("PA1", l);
    l = newItem("pa1", l);
    l = newItem("UOS", l);
    l = newItem("LIN", l);
    l = newItem("AG1", l);
    assert(l
           && !strcmp(l->m_Name, "AG1"));
    assert(l->m_Next
           && !strcmp(l->m_Next->m_Name, "LIN"));
    assert(l->m_Next->m_Next
           && !strcmp(l->m_Next->m_Next->m_Name, "UOS"));
    assert(l->m_Next->m_Next->m_Next
           && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "pa1"));
    assert(l->m_Next->m_Next->m_Next->m_Next
           && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "PA1"));
    assert(l->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
    l = sortList(l, 1);
    //print_list(l);
    assert(l
           && !strcmp(l->m_Name, "AG1"));
    assert(l->m_Next
           && !strcmp(l->m_Next->m_Name, "LIN"));
    assert(l->m_Next->m_Next
           && !strcmp(l->m_Next->m_Next->m_Name, "PA1"));
    assert(l->m_Next->m_Next->m_Next
           && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "UOS"));
    assert(l->m_Next->m_Next->m_Next->m_Next
           && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "pa1"));

    freeList(l);



    assert(sizeof(TITEM) == sizeof(TITEM *) + sizeof(char *) + 24 * sizeof(char));

    l = NULL;
    l = newItem("PA1", l);
    l = newItem("PA2", l);
    l = newItem("UOS", l);
    l = newItem("LIN", l);
    l = newItem("AG1", l);
    //print_list(l);
    assert(l
           && !strcmp(l->m_Name, "AG1"));
    assert(l->m_Next
           && !strcmp(l->m_Next->m_Name, "LIN"));
    assert(l->m_Next->m_Next
           && !strcmp(l->m_Next->m_Next->m_Name, "UOS"));
    assert(l->m_Next->m_Next->m_Next
           && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "PA2"));
    assert(l->m_Next->m_Next->m_Next->m_Next
           && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "PA1"));
    assert(l->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
    l = sortList(l, 1);
    assert(l
           && !strcmp(l->m_Name, "AG1"));
    assert(l->m_Next
           && !strcmp(l->m_Next->m_Name, "LIN"));
    assert(l->m_Next->m_Next
           && !strcmp(l->m_Next->m_Next->m_Name, "PA1"));
    assert(l->m_Next->m_Next->m_Next
           && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "PA2"));
    assert(l->m_Next->m_Next->m_Next->m_Next
           && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "UOS"));
    assert(l->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
    l = newItem("programming and algorithmic I", l);
    l = newItem("AAG", l);
    assert(l
           && !strcmp(l->m_Name, "AAG"));
    assert(l->m_Next
           && !strcmp(l->m_Next->m_Name, "programming and algorithmic I"));
    assert(l->m_Next->m_Next
           && !strcmp(l->m_Next->m_Next->m_Name, "AG1"));
    assert(l->m_Next->m_Next->m_Next
           && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "LIN"));
    assert(l->m_Next->m_Next->m_Next->m_Next
           && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "PA1"));
    assert(l->m_Next->m_Next->m_Next->m_Next->m_Next
           && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Name, "PA2"));
    assert(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next
           && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Name, "UOS"));
    assert(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
    l = sortList(l, 0);
    //printf("--------------\n");
    //print_list(l);
    assert(l
           && !strcmp(l->m_Name, "programming and algorithmic I"));
    assert(l->m_Next
           && !strcmp(l->m_Next->m_Name, "UOS"));
    assert(l->m_Next->m_Next
           && !strcmp(l->m_Next->m_Next->m_Name, "PA2"));
    assert(l->m_Next->m_Next->m_Next
           && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "PA1"));
    assert(l->m_Next->m_Next->m_Next->m_Next
           && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "LIN"));
    assert(l->m_Next->m_Next->m_Next->m_Next->m_Next
           && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Name, "AG1"));
    assert(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next
           && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Name, "AAG"));
    assert(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
    freeList(l);
    l = NULL;
    strncpy(tmp, "PA1", sizeof(tmp) - 1);
    tmp[sizeof(tmp) - 1] = '\0';
    l = newItem(tmp, l);
    strncpy(tmp, "PA2", sizeof(tmp) - 1);
    tmp[sizeof(tmp) - 1] = '\0';
    l = newItem(tmp, l);
    strncpy(tmp, "UOS", sizeof(tmp) - 1);
    tmp[sizeof(tmp) - 1] = '\0';
    l = newItem(tmp, l);
    strncpy(tmp, "LIN", sizeof(tmp) - 1);
    tmp[sizeof(tmp) - 1] = '\0';
    l = newItem(tmp, l);
    strncpy(tmp, "AG1", sizeof(tmp) - 1);
    tmp[sizeof(tmp) - 1] = '\0';
    l = newItem(tmp, l);
    assert(l
           && !strcmp(l->m_Name, "AG1"));
    assert(l->m_Next
           && !strcmp(l->m_Next->m_Name, "LIN"));
    assert(l->m_Next->m_Next
           && !strcmp(l->m_Next->m_Next->m_Name, "UOS"));
    assert(l->m_Next->m_Next->m_Next
           && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "PA2"));
    assert(l->m_Next->m_Next->m_Next->m_Next
           && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "PA1"));
    assert(l->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
    l = sortList(l, 1);
    assert(l
           && !strcmp(l->m_Name, "AG1"));
    assert(l->m_Next
           && !strcmp(l->m_Next->m_Name, "LIN"));
    assert(l->m_Next->m_Next
           && !strcmp(l->m_Next->m_Next->m_Name, "PA1"));
    assert(l->m_Next->m_Next->m_Next
           && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "PA2"));
    assert(l->m_Next->m_Next->m_Next->m_Next
           && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "UOS"));
    assert(l->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
    strncpy(tmp, "programming and algorithmic I", sizeof(tmp) - 1);
    tmp[sizeof(tmp) - 1] = '\0';
    l = newItem(tmp, l);
    strncpy(tmp, "AAG", sizeof(tmp) - 1);
    tmp[sizeof(tmp) - 1] = '\0';
    l = newItem(tmp, l);
    assert(l
           && !strcmp(l->m_Name, "AAG"));
    assert(l->m_Next
           && !strcmp(l->m_Next->m_Name, "programming and algorithmic I"));
    assert(l->m_Next->m_Next
           && !strcmp(l->m_Next->m_Next->m_Name, "AG1"));
    assert(l->m_Next->m_Next->m_Next
           && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "LIN"));
    assert(l->m_Next->m_Next->m_Next->m_Next
           && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "PA1"));
    assert(l->m_Next->m_Next->m_Next->m_Next->m_Next
           && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Name, "PA2"));
    assert(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next
           && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Name, "UOS"));
    assert(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
    l = sortList(l, 0);
    assert(l
           && !strcmp(l->m_Name, "programming and algorithmic I"));
    assert(l->m_Next
           && !strcmp(l->m_Next->m_Name, "UOS"));
    assert(l->m_Next->m_Next
           && !strcmp(l->m_Next->m_Next->m_Name, "PA2"));
    assert(l->m_Next->m_Next->m_Next
           && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "PA1"));
    assert(l->m_Next->m_Next->m_Next->m_Next
           && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "LIN"));
    assert(l->m_Next->m_Next->m_Next->m_Next->m_Next
           && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Name, "AG1"));
    assert(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next
           && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Name, "AAG"));
    assert(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
    freeList(l);
    return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
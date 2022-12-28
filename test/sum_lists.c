#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
 
typedef struct TItem {
    struct TItem * m_Next;
    char m_Digit;
} TITEM;
 
TITEM * createItem(char digit, TITEM * next) {
    TITEM *n = (TITEM *) malloc(sizeof(*n));
    n->m_Digit = digit;
    n->m_Next = next;
    return n;
}
 
void deleteList(TITEM * l) {
    while (l) {
        TITEM *tmp = l->m_Next;
        free(l);
        l = tmp;
    }
}

int toInt (char a) {
    int tmp = a - '0';
    if (tmp < 0 || tmp > 9) {
        return 10;
    }
    return tmp;
}

char toChar (int a) {
    return a + '0';
}

int check (TITEM * a, int start) {
    if (a != NULL) {
        int tmp = toInt(a->m_Digit);
        if (tmp == 10) {
            printf("tu1 %c -> %d\n", a->m_Digit, tmp);
            return 1;
        }
        if (tmp == 0 && a->m_Next == NULL
            && start != 1) {
            printf("tu2 %c -> %d\n", a->m_Digit, tmp);
            return 1;
        }
    }
    return 0;
}

TITEM * addList ( TITEM * a, TITEM * b ) {
    if (a == NULL || b == NULL) return NULL;
    TITEM * aa = a;
    TITEM * bb = b;
    int start = 0;
    
    while (aa != NULL || bb != NULL) {
        start++;
        if (check(aa, start)) {
            printf("ac\n");
            return NULL;
        }
        if (check(bb, start)) {
            printf("b\n");
            return NULL;
        }
        if (aa == NULL) {
            bb = bb->m_Next;
            continue;
        }
        if (bb == NULL) {
            aa = aa->m_Next;
            continue;
        }
        if (aa != NULL && bb != NULL) {
            aa = aa->m_Next;
            bb = bb->m_Next;
        }
    }

    TITEM * res = (TITEM*) malloc(sizeof(*res));
    TITEM * head = res;
    int sum = 0, carry = 0;
    
    while (a || b) {
        if (a == NULL) {
            res->m_Digit = b->m_Digit;
            if (b->m_Next == NULL) {
                res->m_Next = NULL;
            } else {
                res->m_Next = (TITEM*) malloc(sizeof(*res));
                res = res->m_Next;
            }
            b = b->m_Next;
            continue;
        }
        
        if (b == NULL) {
            res->m_Digit = a->m_Digit;
            if (a->m_Next == NULL) {
                res->m_Next = NULL;
            } else {
                res->m_Next = (TITEM*) malloc(sizeof(*res));
                res = res->m_Next;
            }
            a = a->m_Next;
            continue;
        }
        printf("aa\n");
        sum = toInt(a->m_Digit) + toInt(b->m_Digit);
        printf("sum: %d\n", sum);
        if (sum > 9) {
            carry = 1;
            sum = 0;
        }
        res->m_Digit = toChar(sum);

        if (a->m_Next == NULL && b->m_Next == NULL) {
            res->m_Next = NULL;
        } else {
            res->m_Next = (TITEM*) malloc(sizeof(*res));
            res = res->m_Next;
        }
        a = a->m_Next;
        b = b->m_Next;
        continue;
    }

    if (carry) {
        res->m_Next = (TITEM*) malloc(sizeof(*res));
        res = res->m_Next;
        res->m_Digit = '1';
        res->m_Next = NULL;
    }

    return head;
}

int main(int argc, char *argv[]) {
    TITEM * a, * b, * res;
 /*
    a = createItem('x', NULL);
    b = createItem('3', NULL);
    res = addList(a, b);
    assert (res == NULL);
    deleteList(a);
    deleteList(b);
 
    a = createItem('5',
         createItem('0',
          createItem('0', NULL)));
    b = createItem('3', NULL);
    res = addList(a, b);
    assert (res == NULL);
    deleteList(a);
    deleteList(b);
    */
 
    a = createItem('3',
         createItem('4',
          createItem('5', NULL)));
    b = createItem('0', NULL);
    res = addList(a, b);
    //printf("res: %c\n", res->m_Digit);
    
    assert (res->m_Digit == '3');
    assert (res->m_Next->m_Digit == '4');
    assert (res->m_Next->m_Next->m_Digit == '5');
    assert (res->m_Next->m_Next->m_Next == NULL);
    
    deleteList(res);
    deleteList(a);
    deleteList(b);

    //--------------------------------------------
    a = createItem('2', createItem('3', createItem('3', NULL)));
    b = createItem('5', createItem('3', createItem('1', NULL)));
    res = addList(a, b);
    assert (res->m_Digit == '7');
    assert (res->m_Next->m_Digit == '6');
    assert (res->m_Next->m_Next->m_Digit == '4');
    assert (res->m_Next->m_Next->m_Next == NULL);
    deleteList(res);
    deleteList(a);
    deleteList(b);
 
    a = createItem('2', createItem('3', createItem('9', NULL)));
    b = createItem('5', createItem('3', createItem('1', NULL)));
    res = addList(a, b);
    assert (res->m_Digit == '7');
    assert (res->m_Next->m_Digit == '6');
    assert (res->m_Next->m_Next->m_Digit == '0');
    assert (res->m_Next->m_Next->m_Next->m_Digit == '1');
    assert (res->m_Next->m_Next->m_Next->m_Next == NULL);
    deleteList(res);
    deleteList(a);
    deleteList(b);

    return 0;
}
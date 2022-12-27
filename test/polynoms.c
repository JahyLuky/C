#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
 
typedef struct TItem
{
    struct TItem * m_Next;
    int m_Mul;
    int m_Pow;
} TITEM;
 
TITEM * createItem ( int mul, int p, TITEM * next )
{
    TITEM * n = (TITEM *) malloc (sizeof ( *n ));
    n -> m_Mul = mul;
    n -> m_Pow = p;
    n -> m_Next = next;
    return n;
}
 
void deleteList (TITEM * l)
{
    while (l)
    {
        TITEM * tmp = l -> m_Next;
        free (l);
        l = tmp;
    }
}
#endif /* __PROGTEST__ */

void deleteList1 (TITEM * l)
{
    //if (l == NULL) {return;}
    while (l)
    {
        printf("free: %d ^ %d\n", l->m_Mul, l->m_Pow);
        TITEM * tmp = l -> m_Next;
        free (l);
        l = tmp;
    }
}

int check (TITEM * a, int start, int last) {
    if (a->m_Pow <= last) {
        //printf("a) mul: %d, pow: %d, start: %d, last: %d\n", a->m_Mul, a->m_Pow, start, last);
        return 0;
    }
    if (a->m_Mul == 0 && a->m_Pow == 0 && last == -1 && a->m_Next == NULL) return 1;
    if (a->m_Mul == 0) {
        //printf("b) mul: %d, pow: %d, start: %d, last: %d\n", a->m_Mul, a->m_Pow, start, last);
        return 0;
    }
    //printf("good) mul: %d, pow: %d, start: %d, last: %d\n", a->m_Mul, a->m_Pow, start, last);
    return 1;
}

TITEM * addPoly ( TITEM * x , TITEM * y ) {
    TITEM * a = x;
    TITEM * b = y;
    if (a == NULL || b == NULL) return NULL;

    TITEM * c = NULL;
    TITEM * head_c = NULL;
    int sum = 0, start = 1, a_last = -1, b_last = -1;
    
    while (a != NULL || b != NULL) {
        //-------------------------------
        if (a == NULL) {
            if (check(b, start, b_last) == 0) {
                printf("ahoj\n");
                deleteList1(head_c);
                return NULL;
            }
            b_last = b->m_Pow;
            sum = b->m_Mul;
            c = createItem(sum, b_last, NULL);
            printf("c: %d ^ %d\n", c->m_Mul, c->m_Pow);
            b = b->m_Next;
            c = c->m_Next;
            continue;
        }
        //-------------------------------
        if (b == NULL) {
            if (check(a, start, a_last) == 0) {
                deleteList1(head_c);
                return NULL;
            }
            a_last = a->m_Pow;
            c = createItem(a->m_Mul, a->m_Pow, NULL);
            a = a->m_Next;
            c = c->m_Next;
            continue;
        }
        //-------------------------------
        if (a != NULL && b != NULL) {
            if (check(a, start, a_last) == 0) {
                deleteList1(head_c);
                return NULL; 
            }
            if (check(b, start, b_last) == 0) {
                deleteList1(head_c);
                return NULL;
            }
            sum = a->m_Mul + b->m_Mul;
            if (sum == 0) {
                if (sum == 0 && start == 1 &&
                 a->m_Next == NULL && b->m_Next == NULL) {
                    c = createItem(0, 0, NULL);
                    return c;
                }
                a_last = a->m_Pow;
                b_last = b->m_Pow;
                a = a->m_Next;
                b = b->m_Next;
                continue;
            }
            a_last = a->m_Pow;
            b_last = b->m_Pow;
            c = createItem(sum, a->m_Pow, NULL);
            a = a->m_Next;
            b = b->m_Next;

            if (start == 1) {
                start = 0;
                head_c = c;
                //printf("head: %d ^ %d\n", head_c->m_Mul, head_c->m_Pow);
            }
            c = c->m_Next;
        }
    }
    return head_c;
}
 
#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
    TITEM * a, * b;
    TITEM * res = NULL;
/*
    a = createItem (3,1,createItem (-2,2,createItem (4,3,NULL)));
    b = createItem (-3,1,createItem (2,2,createItem (-4,3,NULL)));
    res = addPoly(a,b);
    assert ( res -> m_Mul == 0 );
    assert ( res -> m_Pow == 0 );
    assert ( res -> m_Next == NULL );
    deleteList ( a );
    deleteList ( b );
    deleteList ( res );
*/
/*
    a = createItem (2,1,NULL);
    b = createItem (0,0,NULL);
    res = addPoly(a,b);
    assert ( res -> m_Mul == 2 );
    assert ( res -> m_Pow == 1 );
    assert ( res -> m_Next == NULL );
    deleteList ( a );
    deleteList ( b );
    deleteList ( res );
 */
 
    TITEM * c = NULL;
    c = createItem(1,1, NULL);
    TITEM * h = c;
    c = c->m_Next;
    c = createItem(2,2 , NULL);
    deleteList1(h);

/*
    a = createItem (2,1,NULL);
    b = createItem (3,1,createItem (4,2,createItem (2,3,createItem(1,0,NULL))));
    res = addPoly(a,b);
    assert ( res == NULL );
    deleteList ( a );
    deleteList ( b );
    deleteList ( res );
*/
/*
    a = createItem (2,1,NULL);
    b = createItem (3,1,createItem (4,1,NULL));
    res = addPoly(a,b);
    assert ( res == NULL );
    deleteList ( a );
    deleteList ( b );
    deleteList ( res );
    */
/*
    a = createItem (3,0,createItem (2,1,createItem (9,3,NULL)));
    b = createItem (0,0,createItem (4,2,createItem (-1,3,NULL)));
    res = addPoly(a,b);
    assert ( res == NULL );
    deleteList ( a );
    deleteList ( b );
    deleteList ( res );
    */
 /*
    a = createItem (3,0,createItem (2,1,createItem (5,3,NULL)));
    b = createItem (-7,0,createItem (-2,1,createItem (-5,3,NULL)));
    res = addPoly(a,b);
    assert ( res -> m_Mul == -4 );
    assert ( res -> m_Pow == 0 );
    assert ( res -> m_Next == NULL );
    deleteList ( a );
    deleteList ( b );
    deleteList ( res );
*/
    return 0;
}
#endif /* __PROGTEST__ */

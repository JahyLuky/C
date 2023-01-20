/*
Jsou zadané 2 spojové seznamy. A a B. Oba spojové seznamy reprezentují nějaký polynom. Vaším cílem je oba spojové seznamy sečíst a z jejich součtu vytvořit nový spojový seznam. Spojový seznam obsahuje 2 prvky. Int, který reprezentuje mocninu (m_moc) a základ té mocniny (m_num) a také m_Next (Odkaz na následující prvek).

Vytvořte tedy funkci, která má za parametry 2 spojové seznamy a jejím výstupem budou sečtené polynomy jako spojový seznam. (Funkce na free a základní struct implementace byla zahrnuta v zadání (stejně tak asserty), to už nemám)

Vstupní spojové seznamy musí splnit podmínky:

- Polynomy musí být řazeny dle jejich mocnin vzestupně. Pokud toto nebude splněno vraťte NULL. (Nevracejte žádný spojový seznam)

- Pokud výsledný polynom je 0 (Všechny se odečtou např.), tak vraťte spojový seznam realizován jedním prvkem, kde m_num = 0 a m_moc = 0

- Oba spojové seznamy nesmí být prázdné, jestliže nějaký je vraťte NULL
*/

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
        printf("a): %d ^ %d\n", l->m_Mul, l->m_Pow);
        TITEM * tmp = l -> m_Next;
        free (l);
        l = tmp;
    }
}

void deleteList1 (TITEM * l)
{
    while (l)
    {
        printf("b): %d ^ %d\n", l->m_Mul, l->m_Pow);
        TITEM * tmp = l -> m_Next;
        free (l);
        l = tmp;
    }
}

int check (TITEM * a, int last) {
    if (a != NULL) {
        if (a->m_Pow <= last) {printf("a\n");return 1;}
        if (a->m_Mul == 0 && a->m_Pow == 0 
            && a->m_Next == NULL) {return 0;}
        if (a->m_Mul == 0) {printf("b\n"); return 1;}
    }
    return 0; 
}

TITEM * addPoly ( TITEM * x , TITEM * y ) {
    TITEM * a = x;
    TITEM * b = y;
    if (!a || !b) return NULL;
    TITEM *aa = x;
    TITEM *bb = y;
    int a_last = -1, b_last = -1, sum = 0;
    while (aa != NULL || bb != NULL) {
        if (check(aa, a_last)) {
            return NULL;
        }
        if (check(bb, b_last)) {
            return NULL;
        }
        if (aa != NULL && bb == NULL) {
            a_last = aa->m_Pow;
            aa = aa->m_Next;
        }
        if (bb != NULL && aa == NULL) {
            b_last = bb->m_Pow;
            bb = bb->m_Next;
        }
        if (aa != NULL && bb != NULL) {
            a_last = aa->m_Pow;
            aa = aa->m_Next;
            b_last = bb->m_Pow;
            bb = bb->m_Next;
        }
    }

    TITEM * c = (TITEM*) malloc(sizeof(*c));
    TITEM * head = c;
    while (a || b) {
        if (!a) {
            sum = b->m_Mul;
            b_last = b->m_Pow;
            c->m_Mul = sum;
            c->m_Pow = b_last;
            if (b->m_Next == NULL) {
                c->m_Next = NULL;
                b = b->m_Next;
                continue;
            }
            c->m_Next = (TITEM*) malloc(sizeof(*c));
            c = c->m_Next;
            b = b->m_Next;
            continue;
        }
        if (!b) {
            sum = a->m_Mul;
            c->m_Mul = sum;
            a_last = a->m_Pow;
            c->m_Pow = a_last;
            if (a->m_Next == NULL) {
                c->m_Next = NULL;
                a = a->m_Next;
                continue;
            }
            c->m_Next = (TITEM*) malloc(sizeof(*c));
            c = c->m_Next;
            a = a->m_Next;
            continue;
        }
        if (a->m_Pow == b->m_Pow) {
            sum = a->m_Mul + b->m_Mul;
            if (sum == 0) {
                // empty -> 0^0
                if (a->m_Next == NULL && b->m_Next == NULL) {
                        c->m_Mul = 0;
                        c->m_Pow = 0;
                        c->m_Next = NULL;
                        return c;
                }
                a_last = a->m_Pow;
                b_last = b->m_Pow;
                a = a->m_Next;
                b = b->m_Next;
                continue;
            }
            c->m_Mul = sum;
            a_last = a->m_Pow;
            b_last = b->m_Pow;
            c->m_Pow = a_last;
            if (a->m_Next == NULL && b->m_Next == NULL) {
                c->m_Next = NULL;
                a = a->m_Next;
                b = b->m_Next;
                continue;
            }
            c->m_Next = (TITEM*) malloc(sizeof(*c));
            c = c->m_Next;
            a = a->m_Next;
            b = b->m_Next;
            continue;
        }
        if (a->m_Pow < b->m_Pow) {
            if (a->m_Mul == 0 && a->m_Pow == 0 
            && a->m_Next == NULL) {
                b_last = b->m_Pow;
                b = b->m_Next;
                continue;
            } else {
                sum = a->m_Mul;
                c->m_Mul = sum;
                a_last = a->m_Pow;
                c->m_Pow = a_last;
                if (a->m_Next == NULL) {
                    c->m_Next = NULL;
                    a = a->m_Next;
                    continue;
                }
                c->m_Next = (TITEM*) malloc(sizeof(*c));
                c = c->m_Next;
            }
            a = a->m_Next;
            continue;
        }
        if (b->m_Pow < a->m_Pow) {
            if (b->m_Mul == 0 && b->m_Pow == 0 
            && b->m_Next == NULL) {
                b_last = b->m_Pow;
                b = b->m_Next;
                continue;
            } else {
                sum = b->m_Mul;
                c->m_Mul = sum;
                b_last = b->m_Pow;
                c->m_Pow = b_last;
                if (b->m_Next == NULL) {
                    c->m_Next = NULL;
                    b = b->m_Next;
                    continue;
                }
                c->m_Next = (TITEM*) malloc(sizeof(*c));
                //printf("%d ^ %d\n", c->m_Mul, c->m_Pow);
                c = c->m_Next;
            }
            b = b->m_Next;
            continue;
        }
    }
    return head;
}
 
int main ( int argc, char * argv [] )
{
    TITEM * a, * b;
    TITEM * res;

    a = createItem (3,1,createItem (-2,2,createItem (4,3,NULL)));
    b = createItem (-3,1,createItem (2,2,createItem (-4,3,NULL)));
    res = addPoly(a,b);
    if (res == NULL) {
        printf("nul\n");
    }
    //printf("%d ^ %d\n", res->m_Mul, res->m_Pow);
    assert ( res -> m_Mul == 0 );
    assert ( res -> m_Pow == 0 );
    assert ( res -> m_Next == NULL );
    deleteList ( a );
    deleteList ( b );
    deleteList ( res );
   



    a = createItem (2,1,NULL);
    b = createItem (0,0,NULL);
    res = addPoly(a,b);
    //printf("res: %d ^ %d\n", res->m_Mul, res->m_Pow);
    assert ( res -> m_Mul == 2 );
    assert ( res -> m_Pow == 1 );
    assert ( res -> m_Next == NULL );
    deleteList ( a );
    deleteList ( b );
    deleteList ( res );

    a = createItem (2,1,NULL);
    b = createItem (3,1,createItem (4,2,createItem (2,3,createItem(1,0,NULL))));
    res = addPoly(a,b);
    if (res == NULL) {
        printf("nul\n");
    }
    assert ( res == NULL );
    deleteList ( a );
    deleteList ( b );
    deleteList ( res );


    a = createItem (2,1,NULL);
    b = createItem (3,1,createItem (4,1,NULL));
    res = addPoly(a,b);
    assert ( res == NULL );
    deleteList ( a );
    deleteList ( b );
    deleteList ( res );
    

    a = createItem (3,0,createItem (2,1,createItem (9,3,NULL)));
    b = createItem (0,0,createItem (4,2,createItem (-1,3,NULL)));
    res = addPoly(a,b);
    assert ( res == NULL );
    deleteList ( a );
    deleteList ( b );
    deleteList ( res );
    

    return 0;
}
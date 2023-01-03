/*
/*
Úkolem je realizovat funkci, která dokáže spojit spojové seznamy do jednoho. Předpokládejme jednosměrné spojové seznamy. Prvek spojového seznamu ukládá int. Prvky v spojovém seznamu jsou uloženy v neklesajícím pořadí. Předpokládaná funkce dostane pole s odkazy na takto organizované spojové seznamy a počet prvků. Výsledkem bude jeden spojový seznam, který bude obsahovat prvky z předaných spojových seznamů přepojené do jednoho spojového seznamu. Ve výsledném spojovém seznamu budou prvky seřazeny vzestupně. Funkce kontroluje že předané spojové seznamy jsou neprázdné a neklesající, jinak vrací NULL.

Příklady podle ukázky:
Vstup:

1 → 7 → 24 → NULL,

3 → 5 → 17 → NULL,

-3 → 19 → NULL

Výstup:

-3 → 1 → 3 → 5 → 7 → 17 → 19 → 24 → NULL

Vstup:

15 → 19 → 23 → 142 → NULL,

17 → 18 → 18 → 21 → NULL,

11 → 18 → 19 → 40 → NULL

Výstup:

11 → 15 → 17 → 18 → 18 → 18 → 19 → 19 → 21 → 23 → 40 → 142 → NULL

Vstup:

1 → NULL,

2 → NULL,

5 → NULL,

4 → NULL

Výstup:

1 → 2 → 4 → 5 → NULL

Vstup:

12 → 18 → NULL,

15 → 7 → NULL

Výstup:

NULL
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
 
typedef struct tnode {
  struct tnode * m_Next;
  int m_Val;
} Tnode;
 
Tnode * createItem ( int i ,Tnode * next ) {
  Tnode * l = (Tnode*) malloc ( sizeof(*l) ); 
  l->m_Val = i;
  l->m_Next = next;
  return l;
}
void delList ( Tnode * l ) {
  if ( l != NULL )
    delList ( l->m_Next );
  free ( l );
}

void delList1 ( Tnode * l ) {
  if ( l != NULL ) {
    printf("del = %d\n", l->m_Val);
    delList1( l->m_Next );
  }
  free ( l );
}

Tnode * compareList ( Tnode ** x, int nr ) {
    Tnode * tmp = NULL;
    int last = 0;
    for (int i = 0; i < nr; i++) {
        if (x[i] == NULL) {
            return NULL;
        }
        tmp = x[i];
        last = x[i]->m_Val;
        while (tmp) {
            if (tmp->m_Val < last) {
                return NULL;
            }
            last = tmp->m_Val;
            tmp = tmp->m_Next;
        }
    }

    Tnode ** a = (Tnode**) malloc(nr * sizeof(*a));
    for (int i = 0; i < nr; i++) {
        a[i] = x[i];
    }
    Tnode * res = (Tnode*) malloc(sizeof(*res));
    Tnode * head = res;
    Tnode * prev = NULL;

    int id = 1, min = 0, nul = 0, flag = 0, cc = 0;
    while (1) {
        if (a[min] == NULL) {
            min = id;
        }
        while (a[id] == NULL) {
            id++;
            nul++;
            flag = 1;
        }
        if (nul == nr) {
            break;
        }
        if (flag == 1) {
            flag = 0;
            min = id;
        }

        if (a[min]->m_Val > a[id]->m_Val) {
            min = id;
        }

        if (nul == nr - 1) {
            cc = 1;
            break;
        }
        id++;
        if (id == nr) {
            id = 0;
            res->m_Val = a[min]->m_Val;
            res->m_Next = (Tnode*) malloc(sizeof(*res));
            prev = res;
            res = res->m_Next;
            a[min] = a[min]->m_Next;
        }
    }

    if (cc) {
        while (a[id]) {
            res->m_Val = a[id]->m_Val;
            res->m_Next = (Tnode*) malloc(sizeof(*res));
            prev = res;
            res = res->m_Next;
            a[id] = a[id]->m_Next;
        }
        
    }
    free(res);
    prev->m_Next = NULL;
    //printf("res = %d\n", res->m_Val);
    for (int i = 0; i < nr; ++i) {
        free(a[i]);
    }
    free(a);
    return head;
}
 
int main ( int argc, char * argv [] ) {
 
  Tnode * a[5];
  Tnode * res;

  a[0] = createItem ( 15,
           createItem ( 19,
             createItem ( 19,
               createItem ( 2, NULL ))));
  a[1] = NULL;
  a[2] = createItem ( -2,
           createItem ( 1,
             createItem ( 10,
               createItem ( 11, NULL ))));
  res = compareList ( a, 3 );
  assert ( res == NULL );
  delList ( res );
  for(int i = 0; i < 3;i++){
    delList(a[i]);
  }



  a[0] = createItem ( 3, 
          createItem ( 4, 
            createItem ( 5, NULL )));
  a[1] = createItem ( 1,
           createItem ( 2,
             createItem ( 6,
               createItem ( 7,
                 createItem ( 8,
                   createItem ( 9, NULL ))))));
  res = compareList ( a, 2 );
 
    Tnode * tmp = res;
    while (tmp) {
        printf("%d\n", tmp->m_Val);
        tmp = tmp->m_Next;
    }

  assert(res->m_Val == 1);
  assert(res->m_Next->m_Val == 2);
  assert(res->m_Next->m_Next->m_Val == 3);
  assert(res->m_Next->m_Next->m_Next->m_Val == 4);
  assert(res->m_Next->m_Next->m_Next->m_Next->m_Val == 5);
  assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Val == 6);
  assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Val == 7);
  assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Val == 8);
  assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Val == 9);
  assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
 
 
  delList ( res );
  for(int i = 0; i < 2;i++){
    delList1(a[i]);
  }
  
 
/*
  a[0] = createItem ( 1,
           createItem ( 7,
             createItem ( 24, NULL )));
  a[1] = createItem ( 3,
           createItem ( 5,
             createItem ( 17, NULL )));
  a[2] = createItem ( -3,
           createItem ( 19, NULL ));
  res = compareList ( a, 3 );
 
    tmp = res;
    while (tmp) {
        printf("%d\n", tmp->m_Val);
        tmp = tmp->m_Next;
    }

  assert(res->m_Val == -3);
  assert(res->m_Next->m_Val == 1);
  assert(res->m_Next->m_Next->m_Val == 3);
  assert(res->m_Next->m_Next->m_Next->m_Val == 5);
  assert(res->m_Next->m_Next->m_Next->m_Next->m_Val == 7);
  assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Val == 17);
  assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Val == 19);
  assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Val == 24);
  assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL); 
 
  delList ( res );
  for(int i = 0; i < 3;i++){
    delList(a[i]);
  }
  */
 /*
  a[0] = createItem ( 15,
           createItem ( 19,
             createItem ( 23,
               createItem ( 192, NULL ))));
  a[1] = createItem ( 17,
           createItem ( 18,
             createItem ( 18,
               createItem ( 21, NULL ))));
  a[2] = createItem ( -3,
          createItem ( 19, NULL ));
  res = compareList ( a, 3 );
 
  assert(res->m_Val == -3);
  assert(res->m_Next->m_Val == 15);
  assert(res->m_Next->m_Next->m_Val == 17);
  assert(res->m_Next->m_Next->m_Next->m_Val == 18);
  assert(res->m_Next->m_Next->m_Next->m_Next->m_Val == 18);
  assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Val == 19);
  assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Val == 19);
  assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Val == 21);
  assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Val == 23);
  assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Val == 192);
  assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
 
  delList ( res );
  for(int i = 0; i < 3;i++){
    delList(a[i]);
  }
 
  a[0] = createItem ( -4,
           createItem ( 2,
             createItem ( 4,
               createItem ( 7, NULL ))));
  a[1] = createItem ( 12,
           createItem ( 18,
             createItem ( 20, NULL )));
  a[2] = createItem ( -6,
           createItem ( 3,
             createItem ( 4,
               createItem ( 11,
                 createItem ( 14,
                   createItem ( 15,
                     createItem ( 19, NULL )))))));
  res = compareList ( a, 3 );
 
  int vysl[] = {-6,-4,2,3,4,4,7,11,12,14,15,18,19,20};
  Tnode * test = res;
  for(int i = 0; i < 14; i++) {
    assert(test->m_Val == vysl[i]);
    test = test->m_Next;
  }
  assert(test == NULL);
 
  delList ( res );
  for(int i = 0; i < 3;i++){
    delList(a[i]);
  }
 
  a[0] = createItem ( -4,
           createItem ( 2,
             createItem ( 4,
               createItem ( 7, NULL ))));
  a[1] = createItem ( 12,
           createItem ( 18,
             createItem ( 20, NULL )));
  a[2] = createItem ( -6,
           createItem ( 3,
             createItem ( 4,
               createItem ( 11,
                 createItem ( 1,
                   createItem ( 15,
                     createItem ( 19, NULL )))))));
  res = compareList ( a, 3 );
 
  assert ( res == NULL );
 
  delList ( res );
  for(int i = 0; i < 3;i++){
    delList(a[i]);
  }
 
  a[0] = createItem ( -4,
           createItem ( 2,
             createItem ( 4,
               createItem ( 7, NULL ))));
  a[1] = createItem ( 12, NULL );
  a[2] = createItem ( 3, NULL );
  res = compareList ( a, 3 );
 
  assert(res->m_Val == -4);
  assert(res->m_Next->m_Val == 2);
  assert(res->m_Next->m_Next->m_Val == 3);
  assert(res->m_Next->m_Next->m_Next->m_Val == 4);
  assert(res->m_Next->m_Next->m_Next->m_Next->m_Val == 7);
  assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Val == 12);
  assert(res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
 
  delList ( res );
  for(int i = 0; i < 3;i++){
    delList(a[i]);
  }
 
  a[0] = createItem ( 15,
           createItem ( 19,
             createItem ( 19,
               createItem ( 2, NULL ))));
  a[1] = createItem ( 17,
           createItem ( 18,
             createItem ( 18,
               createItem ( 21, NULL ))));
  res = compareList ( a, 2 );
  assert ( res == NULL );
  delList ( res );
  for(int i = 0; i < 2;i++){
    delList(a[i]);
  }
 

 
  a[0] = createItem ( 5, NULL);
  a[1] = createItem ( 1, NULL);
  a[2] = createItem ( -2, NULL);
  a[3] = createItem ( 69, NULL);
  a[4] = createItem ( 4, NULL);
 
  res = compareList ( a, 5 );
 
  assert(res->m_Val == -2);
  assert(res->m_Next->m_Val == 1);
  assert(res->m_Next->m_Next->m_Val == 4);
  assert(res->m_Next->m_Next->m_Next->m_Val == 5);
  assert(res->m_Next->m_Next->m_Next->m_Next->m_Val == 69);
  assert(res->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
 
  delList ( res );
  for(int i = 0; i < 5;i++){
    delList(a[i]);
  }
 */
  return 0;
}
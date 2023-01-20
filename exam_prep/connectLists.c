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

int compare_ints (const void * a, const void * b) {
    int x = *(const int*) a;
    int y = *(const int*) b;
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

Tnode * compareList ( Tnode ** a, int nr ) {
    Tnode * tmp = NULL;
    int last = 0, n = 1, size = 0;
    int * arr = (int*) malloc(n * sizeof(int));
    for (int i = 0; i < nr; i++) {
        if (a[i] == NULL) {
            free(arr);
            return NULL;
        }
        tmp = a[i];
        last = a[i]->m_Val;
        while (tmp) {
            if (tmp->m_Val < last) {
                free(arr);
                return NULL;
            }
            last = tmp->m_Val;
            printf("last = %d\n", last);
            arr[size] = last;
            size++;
            if (size > n) {
                n *= 2;
                arr = (int*) realloc(arr, n * sizeof(int));
            }
            tmp = tmp->m_Next;
        }
    }

    Tnode * res = (Tnode*) malloc(sizeof(*res));
    Tnode * head = res;
    
    qsort(arr, size, sizeof(int), compare_ints);
    for (int i = 0; i < size; i++) {
        printf("%d\n", arr[i]);
        res->m_Val = arr[i];
        if (i == (size - 1)) {
            res->m_Next = NULL;
            break;
        }
        res->m_Next = (Tnode*) malloc(sizeof(*res));
        res = res->m_Next;
    }
    free(arr);
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
    delList(a[i]);
  }
 
  a[0] = createItem ( 1,
           createItem ( 7,
             createItem ( 24, NULL )));
  a[1] = createItem ( 3,
           createItem ( 5,
             createItem ( 17, NULL )));
  a[2] = createItem ( -3,
           createItem ( 19, NULL ));
  res = compareList ( a, 3 );
 
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
 
  return 0;
}
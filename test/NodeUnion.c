#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

typedef struct Titem
{
  struct Titem * m_Next;
  int m_Val;
} TITEM;

TITEM * createItem ( int val, TITEM * next )
{
  TITEM * a = (TITEM*) malloc ( sizeof(TITEM) );
  a->m_Val = val;
  a->m_Next = next;
  return a;
}

void delList ( TITEM * a )
{
  if ( a == NULL )
  {
    return;
  }
  TITEM * tmp = a->m_Next;
  free(a);
  delList(tmp);
}

TITEM * compareList ( TITEM ** x, int nr )
{
  


  return NULL;
}

int main ( int argc, char * argv [] )
{
  TITEM * a[5];
  TITEM * res;
  
  a[0] = createItem ( 1,
           createItem ( 7,
             createItem ( 24, NULL )));
  a[1] = createItem ( 3,
           createItem ( 5,
             createItem ( 17, NULL )));
  a[2] = createItem ( -3,
           createItem ( 19, NULL ));
  res = compareList ( a, 3 );
  delList ( res );

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
  delList ( res );
  
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
  delList(a[0]);
  delList(a[2]);

  return 0;
}
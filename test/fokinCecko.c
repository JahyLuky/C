#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

int getNum ( char digit )
{
    if ( digit >= '0' || digit <= '9' )
    {
        digit = digit - '0';
        return digit;
    }
    else if ( digit <= 'F' )
    {
        return digit;
    }
}

int main ( int argc, char * argv [] )
{
  char a[] = "A";
  int array[100];
  for (int i = 0; i < strlen(a); i++)
  {
    array[i] = getNum(a[i]);
    printf("%d", array[i]);
  }
  
  int hex = 1, num = 0;
  for (int i = 0; i < strlen(a); i++)
  {
    num += array[i] * hex;
    hex *= 16;
  }
  printf("\ndec: %d\n", num);
  return 0;
}
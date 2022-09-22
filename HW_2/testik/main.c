#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main (void)
{
  printf("Zadejte dve cisla:\n");
  
  int a = 0, b = 0, c = 0;
  scanf("%d %d", &a, &b);
  c = a / b;
  printf(" %d : %d = %d\n", a, b, c );
  
  if(c<=0)
  {
    printf("0\n%d zbytek\n", a);

  }





  return 0;
}
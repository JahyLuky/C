#include <stdio.h>
int foo (int a [42], int b [42])
{
    return sizeof(a)-sizeof(b);
}

int main (void)
{
    /*
    char str[10]="abcd";
    char * p1, *p2;
    p1=str;
    p2=str;
    *p2='A';
    printf("%s %s \n", p1,p2);
    */
   int a[21];
   int b[14];
   printf("%d\n", foo (a,b));
    return 0;
}
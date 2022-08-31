#include <stdio.h>
#include <stdlib.h>

//  https://en.cppreference.com/w/c/algorithm/qsort
int compare(const void* a, const void* b)
{
    int arg1 = *(const int*)a;
    int arg2 = *(const int*)b;

    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

int isSum (int *array, int find)
{
    qsort(array, 5, sizeof(int), compare);
    int l = 0, r = 4;
    for (int i = 0; i <= 4; i++)
    {
        if ( array[l] + array[r] == find )
        {
            return 1;
        }
        else if ( array[l] + array[r] > find )
        {
            r--;
        }
        else
        {
            l++;
        }
        if ( l == r )
        {
            return 0;
        }
    }
    return 0;
}

int NumberSum ()
{
    //int *array = (int *) malloc( 100 * sizeof(int) );
    int array[5];
    char end=',';
    int num = 0,n = 0, find = 0;
    while ( end == ',' ) // na vstupu ?1
    {
        if ( scanf("%d %c", &num, &end) < 2 )
        {
            printf("Nespravny vstup.\n");
            return 1;
        }
        array[n] = num;
        n++;
    }

    if ( n < 2)
    {
        printf("Nespravny vstup.\n");
        return 1;
    }

    printf("Testovane hodnoty:\n");
    while ( end == '?' )
    {
        if ( scanf("%d", &find) != 1 )
        {
            if( feof (stdin) )
            {
                return 0;
            }
            printf("Nespravny vstup.\n");
            break;
        }
        if ( isSum(array,find) == 1 )
        {
            printf("> Soucet %d lze dosahnout.\n", find);
        }
        else
        {
            printf("> Soucet %d nelze dosahnout.\n", find);
        }

    }
    
    return 0;
}

int main (void)
{

    printf("Vstupni posloupnost:\n");
    NumberSum();

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

//  https://en.cppreference.com/w/c/algorithm/qsort
int compare_ints(const void* a, const void* b)
{
    int arg1 = *(const int*)a;
    int arg2 = *(const int*)b;

    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

// finding if number is sum of 2 elements of array
int isSum (int *array, int find, int size)
{
    // sorting array from lowest to highest
    qsort(array, size, sizeof(int), compare_ints);
    int l = 0, r = size-1;
    for (int i = 0; i <=size-1; i++)
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

// filling array and checking if number is sum of 2 elements of array
int NumberSum ()
{
    int size = 100;
    int *array = (int *) malloc( size * sizeof(int) );
    char end=',';
    int num = 0, n = 0, find = 0;

    printf("Vstupni posloupnost:\n");
    while ( end == ',' )
    {
        if ( scanf(" %d %c ", &num, &end) < 2 )
        {
            printf("Nespravny vstup.\n");
            free(array);
            return 1;
        }
        if (end != '?' && end != ',')
        {
            printf("Nespravny vstup.\n");
            free(array);
            return 1;
        }
        array[n] = num;
        n++;
        
        if ( n > size-1 )
        {
            size *= 2;
            array = (int *) realloc( array, size * sizeof(int) );
        }
    }

    // check if input is at least 2
    if ( n < 2)
    {
        printf("Nespravny vstup.\n");
        free(array);
        return 1;
    }

    printf("Testovane hodnoty:\n");
    while ( end == '?' )
    {
        if ( scanf("%d", &find) != 1 )
        {
            if( feof (stdin) )
            {
                free(array);
                return 0;
            }
            printf("Nespravny vstup.\n");
            break;
        }
        if ( isSum(array, find, n) == 1 )
        {
            printf("> Soucet %d lze dosahnout.\n", find);
        }
        else
        {
            printf("> Soucet %d nelze dosahnout.\n", find);
        }
    }
    free(array);
    return 0;
}

int main (void)
{
    NumberSum();
    return 0;
}
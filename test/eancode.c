#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct ean{
    int count;
    int order;
    char * num;
}Tea;

int compare_ints(const void* a, const void* b){
    if (a > b) return -1;
    if (a < b) return 1;
    return 0;
}

Tea * newEan ( Tea * b, char * ean )
{
    Tea * a = (Tea*) malloc (sizeof(Tea));
    a->num = strdup(ean);
    a->count = 1;
    a->next = b;
    return a;
}

int duplicate ( Tea * array, int j, char * ean )
{
    for (int i = 0; i < j; i++)
    {
        if ( strcmp(array[i].num,ean) == 0 )
        {
            return i;
        }
    }
    return -1;
}

void freeBostonTea (Tea * a )
{
    if (a == NULL)
    {
        return;
    }
    Tea * tmp = a->next;
    free(a->num);
    free(a);
    freeBostonTea(tmp);
}

void findEAN( Tea * array, int len){
    qsort(array,len,sizeof(Tea),compare_ints);
    if ( len > 10 )
    {
        len = 10;
    }
    for (int i = 0; i < len; i++)
    {
        printf("%s %dx\n", array[i].num, array[i].count);
    }
}

int main ()
{
    char * ean = (char*) malloc(101*sizeof(char));
    int i = 0, len = 3, dup = 0, stringLen = 0;
    Tea * a = NULL;
    Tea * array = (Tea*) malloc ( len * sizeof(Tea) );

    while ( fgets(ean,sizeof(ean),stdin) != NULL )
    {   
        stringLen = strlen(ean);
        if ( stringLen < 6 || stringLen > 101 )
        {
            printf("Nespravy vstup.\n");
            free(ean);
            free(array);
            freeBostonTea(a);
            return 0;
        }
        if ( feof(stdin) )
        {
            printf("Nespravy vstup.\n");
            free(ean);
            free(array);
            freeBostonTea(a);
            return 0;
        }
        if ( (dup = duplicate(array,i,ean)) >= 0 )
        {
            array[dup].count += 1;
            i--;
        }
        else
        {
            a = newEan(a,ean);
            array[i].num = a->num;
            array[i].count = a->count;
            //free(ean);
            ean = NULL;
        }
        i++;
        if ( i > (len-1) )
        {
            len *= 2;
            array = (Tea*)realloc(array, len*sizeof(Tea));
            //printf("realoc\n");
        }
    }
    free(ean);
    printf("\n");
    findEAN(array, i);
    for ( int j = 0; j < i; j++){
        free(array[j].num);
    }
    freeBostonTea(a);
    return 1;
}
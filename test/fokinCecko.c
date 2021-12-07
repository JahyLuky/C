#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

int sameWords ( const char * a, const char * b )
{
    int len = strlen(a);
    char * p = strdup(a);
    //newA = strdup(a);
    //strcpy(newA,a);
    char tmp[100];
    char * newA;
    
    for (int i = 0; i < len; i++)
    {
        if ( isalpha(*p) != 0 )
        {
            newA = p;
            tmp = p[i];
            //printf("%s\n", newA);
            //printf("%s\n", tmp);
        }
        else
        {
            //word comapare
            printf("%s\n", tmp);
            //printf("2 %s\n", p);
        }
        p++;
    }
    //printf("newa: %s\n", newA);
    //free(tmp);
    return 0;
}

int main ( int argc, char * argv [] )
{
  sameWords ( "9 Hello: a students", "HELLO studEnts" );
}
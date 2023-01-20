#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

typedef struct nameCount {
    char name[100] = "0";
    size_t duplicates = 0;
} NAMES;

int sortFoo ( const void *a, const void *b )
{
    NAMES * arg1 = ( NAMES * ) a;
    NAMES * arg2 = ( NAMES * ) b;

    return ( arg1 -> duplicates > arg2 -> duplicates ) - ( arg2 -> duplicates > arg1 -> duplicates );
}

int findName ( NAMES * jmena, char temp[100], size_t count )
{
    for ( size_t i = 0; i <= count; i++ )
    {
        if ( strcmp ( jmena[i].name, temp ) == 0 )
        {
            //printf("NALEZENO %lu\n", i);
            return i;
        }
    }
    return -1;
}

int main ( void )
{
    char letter;
    size_t count = 0;
    size_t cap = 50;
    NAMES * jmena = ( NAMES * ) malloc ( sizeof ( NAMES ) * cap );
    while ( 1 )
    {
        letter = getchar();

        if ( letter == EOF ) 
        {
            break;
        }    

        if ( isalpha ( letter ) )
        {
            char temp[100];
            size_t end = 0;
            for ( size_t i = 0; isalpha ( letter ); i++ )
            {
                temp[i] = letter;
                letter = getchar();
                end = i;
            }

            if ( letter == '\n' ) 
            {
                continue;
            }  

            temp[end + 1] = '\0';
            int found = findName ( jmena, temp, count );

            if ( found >= 0 )
            {
                //printf("zvysujeme\n");
                jmena[found] . duplicates++;
                continue;
            }

            strcpy ( jmena[count] . name, temp );
            //printf("ZAPSANO %s\n", temp);
            jmena[count] . duplicates++;
            count++;
        }
    }

    qsort ( jmena, count , sizeof ( NAMES ), sortFoo );

    for ( size_t i = 0; i < count; i++ )
    {
        //printf("%lu. %s\n", i, jmena[i] . name );
    }
    
    size_t max = jmena[count - 1] . duplicates;
    printf("Nejčastější jméno: %lux\n", max);
    for ( size_t i = count - 1; jmena[i] . duplicates == max; i-- )
    {
        printf("%s\n", jmena[i] . name );
    }
    free ( jmena );


    return 0;
}
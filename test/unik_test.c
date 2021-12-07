#include <stdio.h>
#include <stdlib.h>

#define ARRAY_LENGHT 99999



int main ( int argc, char * argv [] )
{
    char what;
    int from=0, to=0, id=0, times=0, unq=0, all=0;

    int visits[ARRAY_LENGHT];
    int data[ARRAY_LENGHT];

    printf("Pozadavky:\n");
    while ( scanf(" %1c", &what) == 1 )
    {
        
        switch (what)
        {
            case '+':
                if ( scanf("%d", &id) != 1 || id<0 || id > 99999 ){
                    printf("Nespravny vstup.\n");
                    return 1;
                } 

                if ( data[id] != id )
                {
                    data[id]=id;
                    visits[id] = 1; // pocet navstev

                    unq++;
                    printf("> prvni navsteva\n");
                }
                else{
                    
                    times = visits[id] + 1; // pocet vice navstev
                    visits[id] = times; // prepsani poctu navstev
                    printf("> navsteva #%d\n", visits[id]);  

                    times = 0;
                }
                break;
            
            case '?':
                if ( scanf("%d %d", &from, &to) != 2 
                || from < 0 || to >= all || from > to )
                {
                    printf("Nespravny vstup.\n");
                    return 1;
                } 
                

                all = to - from + 1;
                printf("> %d / %d\n", 1 , all);
                break;
            
            default :
                printf("Nespravny vstup.\n");
                return 1;
                
        }
    }
    
    if( feof (stdin) && 
    (id<0 || id > 99999 || from < 0 || to >= all || from > to) )
    {
        return 0;
    }
    else{
        printf("Nespravny vstup.\n");
        return 1;
    }
}
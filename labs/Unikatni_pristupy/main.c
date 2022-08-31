#include <stdio.h>
#include <stdlib.h>

#define ARRAY_LENGHT 100000

int main ( int argc, char * argv [] )
{
    char what;
    int from=0, to=0, id=0, n=0;
    int times=0, all=0, tmp=0,a,i,j;

    int visits[ARRAY_LENGHT]={0};
    int data[ARRAY_LENGHT]={0};
    int search[ARRAY_LENGHT]={0};

    int speed[ARRAY_LENGHT];

    printf("Pozadavky:\n");
    while ( (scanf(" %c", &what)) == 1 )
    {
        if(what=='+')
        {
                if ( scanf("%d", &id) != 1 || id<0 || id > 99999 ){
                    printf("Nespravny vstup.\n");
                    return 1;
                } 
                
                if ( data[id] != id )//novy id
                {
                    
                    data[id]=id;
                    visits[id] = 1; // pocet navstev

                    printf("> prvni navsteva\n");
                }
                else{    
                    times = visits[id] + 1; // vice navstev
                    visits[id] = times; // prepsani poctu navstev
                    printf("> navsteva #%d\n", visits[id]);  
                }
                search[n]=id;
                n++;
                
                if (n>1000000)
                {
                    printf("Nespravny vstup.\n");
                    return 1;
                }
        }
        else if(what=='?')
        {
            a=0;
            speed[ARRAY_LENGHT]={0};
                if ( scanf("%d %d", &from, &to) != 2 
                || from < 0 || to >= n || from > to )
                {
                    printf("Nespravny vstup.\n");
                    return 1;
                }               
                for ( i = from; i < to+1; i++)
                { 
                    if (speed[i] == 1){
                        //printf("%d\n",i);
                        break;}
                    
                    for ( j = i+1; j < to+1; j++)
                    {
                        if ( search[i] == search[j] )
                        {
                            speed[j]=1;
                            speed[i]=1;
                            a++;
                            //break;
                        }
                        //else if(search[to+1] == )
                    }
                }
                all = to - from + 1;
                tmp=all-a;
                printf("> %d / %d\n", tmp , all);
                all=0;
                tmp=0;
        }
        else{
                printf("Nespravny vstup.\n");
                return 1;
            }
    }
    if( feof (stdin) )
    {
        return 0;
    }
}
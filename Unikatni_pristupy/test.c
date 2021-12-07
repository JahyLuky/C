#include <stdio.h>

#define ARRAY_LENGHT 1000000

int main ( int argc, char * argv [] )
{
    char what;
    int from=0, to=0, id=0, n=0;
    int times=0, all=0, tmp=0,a=0,i=0,j=0;

    static int visits[ARRAY_LENGHT]={0};
    
    static int search[ARRAY_LENGHT]={0};
    

    printf("Pozadavky:\n");
    while ( (scanf(" %c", &what)) == 1 )
    {
        switch(what){
            case '+':
                if ( scanf("%d", &id) != 1 || id<0 || id > 99999 ){
                    printf("Nespravny vstup.\n");
                    return 1;
                }
                if (n > 1000000)
                {
                    printf("Nespravny vstup.\n");
                    return 1;
                }
                if ( visits[id] == 0 )//novy id
                {
                    
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
                break;
            case '?':
                static int data[ARRAY_LENGHT]={0};
                a=0;
                all=0;
                tmp=0;
                if ( scanf("%d %d", &from, &to) != 2
                || from < 0 || to >= n || from > to )
                {
                    printf("Nespravny vstup.\n");
                    return 1;
                }
                if(from < 6){
                for(i=from; i<=to; i++)
                {
                    if ( data[i] != 0 ){
                        break;}
                    for(j=i+1; j<=to; j++)
                    {
                        if(search[i] == search[j] )
                        {   
                            data[j]=1;
                            a++;
                        }
                    }
                }
                }
                else{
                for(i=from; i<=to; i++)
                {
                    if ( data[i] != 0 ){
                        break;}
                    for(j=i+1; j<=to; j++)
                    {
                        if(search[i] == search[j] )
                        {   
                            data[j]=1;
                            a++;
                        }
                    }
                }
                a=a+1;
                }
                all = to - from + 1;
                tmp = all - a;
                printf("> %d / %d\n", tmp , all);
                break;
        default:
                printf("Nespravny vstup.\n");
                return 1;
        }
    }
    if( feof (stdin) )
    {
        return 0;
    }
}
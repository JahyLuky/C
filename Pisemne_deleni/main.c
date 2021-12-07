#include <stdio.h>
#include <math.h>
void spaces(int sp)// printf pocet mezer
{
    for (int i = 0; i < sp+1; i++)
    {
        printf(" ");
    }   
}

int number (int div)// int pocet cifer
{
    int x=0;
    while(div>0)
    {
        div/=10;
        x++;
    }
    return x;
}

int loop(int div, int del)
{
    int remaider=0, sp=0;
    printf(" %d : %d = %d\n", div, del, div/del);

    if(div <= del)
    {
        sp=number(div);
        spaces(sp-1);
        printf("%d\n", remaider);
        spaces(0);
        printf("%d zbytek\n", div);
    }

    else
    {
        
    }

    return 0;
}

int main (void){
    int delenec, delitel;
    printf("Zadejte dve cisla:\n");
    if(scanf("%d %d\n", &delenec, &delitel) != 2 || delenec<0 || delitel<=0)
    {
        printf("Nespravny vstup.\n");
        return 1;
    }
    loop(delenec,delitel);
    return 0;
}
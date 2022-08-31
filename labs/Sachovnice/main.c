#include <stdio.h>
void okraj(int pole, int vel)
{
    printf("+");
    for(int i=0; i<pole*vel; i++)
    {
        printf("-");
    }
    printf("+");
}
void mezera(int vel)
{
    for(int i=1; i <= vel; i++)
    {
        printf(" ");
    }
}
void Xradek(int vel)
{
    for(int i=1; i <= vel; i++)
    {
        printf("X");
    }
}

void sachovnice (int pole, int vel)
{
    int swap=1;
    okraj(pole,vel);
    printf("\n");
    for(int i=0; i <= pole*vel-1; i++)
    {
        printf("|");
        if(swap<=vel)
        {
            for (int j = 0; j < pole/2; j++)
            {
                mezera(vel);
                Xradek(vel);
            }
            if(pole%2!=0)
            {
                mezera(vel);
            }
            else{}
            swap++;
        }
        else
        {
            for (int z = 0; z < pole/2; z++)
            {
                Xradek(vel);
                mezera(vel);
            }
            if(pole%2!=0)
            {
                Xradek(vel);
            }
            else{}
            if(swap==(vel*2))
            {
                swap=0;
            }
            swap++;
        }

        printf("|");
        printf("\n");
    }
    okraj(pole,vel);
    printf("\n");
}
int main (void)
{
    int pole, vel;
    printf("Zadejte pocet poli:\n");
    if(scanf("%d", &pole) !=1 || pole<1 )
    {
        printf("Nespravny vstup.\n");
        return 1;
    }
    printf("Zadejte velikost pole:\n");
    if(scanf("%d", &vel) !=1 || vel<1 )
    {
        printf("Nespravny vstup.\n");
        return 1;
    }
    sachovnice(pole, vel);
    return 0;
}
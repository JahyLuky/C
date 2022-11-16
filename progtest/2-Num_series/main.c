#include <stdio.h>
#include <math.h>

void spaces(int sp)
{
    /*
    if(sp==2)
    {
      printf(" ");   
    }
    else{*/
    for (int i = 1; i < sp; i++)
    {
        printf(" ");
    }
    //}
}

void sequence(int pos, int base)
{
    int num=0, lastNum=0, rady=0;
    int cifry=0, lastCifry=0, min=0, minRady=0;
    /*
    if(pos==0)
    {
        printf("0\n");
        printf("^\n");
    }*/
    while(pos >= cifry+1)
    {
        rady++;
        cifry=((base-1)* pow(10,(rady-1))) *rady;
        cifry += lastCifry;
        lastCifry=cifry;
        num = 1*pow(10,(rady-1));
        lastNum += num;
        if(rady<2)
        {
            min=0;
        }
        else
        {
            min=(base-1)*pow(10,(rady-2)) *(rady-1);
            minRady+=min;
        }
    }
    int flag=1, sp=0, a=0;
    /*
    if(pos==minRady)
        {
            printf("%d\n", num-1);
            spaces(sp);
            printf("^\n");
            flag=0;
        }
        */
    while (flag==1)
    {
        a=(minRady-pos);
        
        if(pos<=minRady)
        {
            printf("%d\n", num-1);
            if(a==(-2) )
            {
                printf(" ");
            }
            spaces(sp);
            printf("^\n");
            flag=0;
        }
        else if((pos/rady) <= (minRady/rady))
        {
            printf("%d\n", num);
            if(a==(-2) )
            {
                printf(" ");
            }
            spaces(sp);
            printf("^\n");
            flag=0;
        }
        if(a<0)
        {
            sp=a+(2*a*(-1));
        }
        else
        {
            sp=a;
        }
        if(sp>rady)
        {
            sp=0;
        }
        minRady+=rady;
        num++;
    }
    //printf("sp: %d - %d (%d)= %d\n", minRady, pos, a ,minRady-pos);
}

int main (void)
{
    int pos=0, base=0;
    printf("Pozice a soustava:\n");
	while(scanf("%d %d", &pos, &base) == 2)
    {
        if(pos>=0 && base>1 && base<37){
            if(pos == 0)
            {
                printf("0\n");
                printf("^\n");
            }
            else{
                sequence(pos, base);
            }
        }
        
        else if(scanf("%d %d", &pos, &base) != EOF || (pos<0 || base<0 || base>36 ))
        {
            printf("Nespravny vstup.\n");
            return 1;
        }
        
        else
        {
            printf("Nespravny vstup.\n");
            return 0;
        }
    }
    if( feof (stdin) && (pos>=0 && base>1 && base<37))
    {
        //printf("AAA");
        return 0;
    }
    else
    {
        printf("Nespravny vstup.\n");
        return 1;
    }
}

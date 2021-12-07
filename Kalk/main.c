#include<stdio.h>
//#include <cmath>
#include <math.h>
int main (void)
{
	double a, b, sol;
	char op, rov;
	printf("Zadejte vzorec:\n");
	if (scanf(" %lf %c %lf %c", &a, &op, &b, &rov)!= 4 || rov!='=')
	{
		printf("Nespravny vstup.\n");
	}
	else{
	switch (op)
	{
		case '+':
                sol=a+b;
                printf("%g\n", sol);
		break;
		case '-':
                sol=a-b;
                printf("%g\n", sol);
		break;
		case '*':
                sol=a*b;
                printf("%g\n", sol);
		break;
		case '/':
		if(b==0)
		{
			printf("Nespravny vstup.\n");
		}
		if(a<0 || b<0)
		{
			sol=round(a/b);
		}
		else
		{
		sol=floor(a/b);
		}
		if(fmod(a,b)==0)//std::f
		{
			printf("%.0lf\n", sol);
		}
		else
		{
			printf("%.0g\n", sol);
		}
		break;
		default:
		printf("Nespravny vstup.\n");		
	}
	}
	return 0;
}

#include <stdio.h>

int main() {
    int r=0, g=0, b=0;
    char end;
    printf("Zadejte barvu v RGB formatu:\n");
    
    if( scanf(" rgb ( %3d , %3d , %3d %c", &r, &g, &b, &end) != 4 && end!=')' )
    {
	printf("Nespravny vstup.\n");
    }
	else
	{
        if( (r>255||b>255||g>255) || (r<0||b<0||g<0) )
        {
            printf("Nespravny vstup.\n");

        }
        else if( (r<16||b<16||g<16) )
        {
            printf("#%02X%02X%02X\n",r,g,b);
        }
        else
        {
            printf("#%X%X%X\n",r,g,b);
        }
	}
    return 0;
}

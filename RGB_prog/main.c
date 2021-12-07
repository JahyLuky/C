#include <stdio.h>

int main() {
    int r=0, g=0, b=0;
    printf("Zadejte barvu v RGB formatu:\n");
    if( scanf(" rgb ( %3d , %3d , %3d )", &r, &g, &b) == 3 )
    {
        if( (r>255||b>255||g>255) || (r<0||b<0||g<0) )
        {
            printf("Nespravny vstup.\n");

        }
        else if( (r<10||b<10||g<10) )
        {
            printf("#%02X%02X%02X\n",r,g,b);
        }
        else
        {
            printf("#%X%X%X\n",r,g,b);
        }
    }
    else
    {
        printf("Nespravny vstup.\n");
    }

    return 0;
}

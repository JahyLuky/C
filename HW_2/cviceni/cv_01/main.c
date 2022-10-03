#include <stdio.h>
#include <stdlib.h>

int main ( void )
{
    int h1, m1, s1, ms1, h2, m2, s2, ms2;

    printf("Zadejte cas t1:\n");
    if ( scanf(" %d : %d : %d , %d", &h1, &m1, &s1, &ms1) != 4 )
    {
        printf("Nespravny vstup.\n");
        return 1;
    }

    if ( h1 > 23 || h1 < 0 || m1 > 59 || m1 < 0 || s1 > 59 || s1 < 0 || ms1 > 999 || ms1 < 0 ) 
    {
        printf("Nespravny vstup.\n");
        return 1;
    }

    printf("Zadejte cas t2:\n");
    if ( scanf(" %d : %d : %d , %d", &h2, &m2, &s2, &ms2) != 4)
    {
        printf("Nespravny vstup.\n");
        return 1;
    }

    
    if ( h2 > 23 || h2 < 0 || m2 > 59 || m2 < 0 || s2 > 59 || s2 < 0 || ms2 > 999 || ms2 < 0 )
    {
        printf("Nespravny vstup.\n");
        return 1;
    }

    long long int first_time, second_time;
    first_time = h1 * 3600000 + m1 * 60000 + s1 * 1000 + ms1;
    second_time = h2 * 3600000 + m2 * 60000 + s2 * 1000 + ms2;
    if( first_time > second_time)
    {
        printf("Nespravny vstup.\n");
        return 1;
    }

    long long int final_time = second_time - first_time;
    int hour, min, sec, mils, to_hour, to_min, to_sec;

    hour = final_time / 3600000;
    to_hour = final_time % 3600000;

    min = to_hour / 60000;
    to_min = to_hour % 60000;

    sec = to_min / 1000;
    to_sec = to_min % 1000;

    mils = to_sec;

    printf("Doba: %2d:%02d:%02d,%03d\n", hour, min, sec, mils);

    return 0;
}
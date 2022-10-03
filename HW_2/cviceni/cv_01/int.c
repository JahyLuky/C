#include <stdio.h>

int main() {
    int t11=0, t12=0, t13=0, t14=0,t21=0, t22=0, t23=0, t24=0;
    int a=0, b=0, c=0, d=0;
    int h1=0, h2=0, m1=0, m2=0, ms1=0, ms2=0, s1=0, s2=0, rozdil=0;
    printf("Zadejte cas t1:\n");
    if ( scanf(" %d : %d : %d , %d", &t11, &t12, &t13, &t14) == 4 ) {
        printf("Zadejte cas t2:\n");
        if ( scanf(" %d : %d : %d , %d", &t21, &t22, &t23, &t24) == 4 ) {
            if (t11 < 0 || t12 < 0 || t13 < 0 || t14 < 0 || t21 < 0 || t22 < 0 || t23 < 0 || t24 < 0) {
                printf("Nespravny vstup.\n");
            } else if (t12 > 59 || t13 > 59 || t22 > 59 || t23 > 59) {
                printf("Nespravny vstup.\n");
            } else if (t11 > 23 || t21 > 23) {
                printf("Nespravny vstup.\n");
            }
            else if (t14 > 999 || t24 > 999){
                printf("Nespravny vstup.\n");
            }
            else {
                h1 = t11 * 3600000;//x hodin na msekundy
                m1 = t12 * 60000;//x minut na msekundy
                s1 = t13 * 1000;//x sekund na msekundy
                ms1 = t14 + h1 + m1 + s1;//vse na msek.
                h2 = t21 * 3600000;
                m2 = t22 * 60000;
                s2 = t23 * 1000;
                ms2 = t24 + h2 + m2 + s2;
                if (ms1 > ms2) {
                    printf("Nespravny vstup.\n");
                }
                else {
                    rozdil = ms2 - ms1;
                    a = rozdil / 3600000;
                    b = (rozdil-(a*3600000))/60000;
                    c = (rozdil-(a*3600000)-(b*60000))/1000;
                    d = rozdil-(a*3600000)-(b*60000)-(c*1000);
                    
                    printf("Doba: %2d:%02d:%02d,%03d\n", a, b, c, d);

                }
            }
        }
        else{
            printf("Nespravny vstup.\n");
        }
    }
    else{
        printf("Nespravny vstup.\n");
    }
    return 0;
}


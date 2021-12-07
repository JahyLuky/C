#include <stdio.h>
#include <math.h>
#include <float.h>

double tr_s(double a, double b, double c){
    double obsah, s;
    s=(a+b+c)/2;
    obsah= sqrt(s* ( (s-a) * (s-b) * (s-c) ));
    return obsah;
}

double tr_o(double a, double b, double c){
    double obvod = a+b+c;
    return obvod;
}

double obd_s(double a, double b){
    double obsah = a*b;
    return obsah;
}

double obd_o(double a, double b){
    double obvod = 2*(a+b);
    return obvod;
}

double ctverec_s(double a){
    double obsah = a*a;
    return obsah;
}

double ctverec_o (double a){
    double obvod = 4 * a;
    return obvod;
}

double jeok(double a, double b, double c)
{
    double n= 1;
    if( fabs(a+b - c) <= 100*DBL_EPSILON*c)
    {
        n=0;
    }
    if( fabs(c+b -a) <= 100*DBL_EPSILON*a)
    {
        n=0;
    }
    if( fabs(a+c - b) <= 100*DBL_EPSILON*b)
    {
        n=0;
    }

    return n;
}

int main() {
    char id1, id2;
    double a, b, c;
    double x, y, z;
    double o1, o2, s1, s2;
    double n, m;
    const char *txt1, *txt2;
    printf("Obrazec #1\n");
    scanf(" %c", &id1);
    switch (id1) {
        case 'T':
            if(scanf(" %lf %lf %lf", &a, &b, &c)==3 && a>0 && b>0 && c>0) {
                n= jeok(a,b,c);
                if(n==1) {
                    o1 = tr_o(a, b, c);
                    s1 = tr_s(a, b, c);
                    txt1 = "trojuhelnik #1";
                }
                else
                {
                    printf("Nespravny vstup.\n");
                    return 1;
                }
            }
            else
            {
                printf("Nespravny vstup.\n");
                return 1;
            }
            break;

        case 'R':
            if(scanf(" %lf %lf", &a, &b)==2 && a>0 && b>0) {
                if( fabs(a - b) < 100 * DBL_EPSILON * fabs(b) )
                {
                    printf("Nespravny vstup.\n");
                    return 1;
                }
                o1 = obd_o(a, b);
                s1 = obd_s(a, b);
                txt1 = "obdelnik #1";
            }
            else
            {
                printf("Nespravny vstup.\n");
                return 1;
            }
                break;

        case 'S':
            if(scanf(" %lf", &a)==1 && a>0) {
                o1 = ctverec_o(a);
                s1 = ctverec_s(a);
                txt1 = "ctverec #1";
            }
            else
            {
                printf("Nespravny vstup.\n");
                return 1;
            }
            break;

        default:
            printf("Nespravny vstup.\n");
            return 1;
    }

    printf("Obrazec #2\n");
    scanf(" %c", &id2);
    switch (id2) {
        case 'T':
            if (scanf(" %lf %lf %lf", &x, &y, &z)==3 && x>0 && y>0 && z>0) {
                m= jeok(x,y,z);
                if(m==1) {
                    o2 = tr_o(x, y, z);
                    s2 = tr_s(x, y, z);
                    txt2 = "trojuhelnik #2";
                }
                else{
                    printf("Nespravny vstup.\n");
                    return 1;
                }
            } else {
                printf("Nespravny vstup.\n");
                return 1;
            }
            break;

        case 'R':
            if(scanf(" %lf %lf", &x, &y)==2 && x>0 && y>0) {
                if( fabs(x - y) < 100 * DBL_EPSILON * fabs(y) )
                {
                    printf("Nespravny vstup.\n");
                    return 1;
                }
                o2 = obd_o(x, y);
                s2 = obd_s(x, y);
                txt2 = "obdelnik #2";
            }else {
                printf("Nespravny vstup.\n");
                return 1;
            }
            break;

        case 'S':
            if(scanf(" %lf", &x)==1 && x>0) {
                o2 = ctverec_o(x);
                s2 = ctverec_s(x);
                txt2 = "ctverec #2";
            }
            else
            {
                printf("Nespravny vstup.\n");
                return 1;
            }
                break;

        default:
            printf("Nespravny vstup.\n");
            return 1;
    }
    if (fabs(o1 - o2) < 100 * DBL_EPSILON * fabs(o2)) {
        printf("Obvod: %s = %s\n", txt1, txt2);
    } else if (o1 > o2) {
        printf("Obvod: %s > %s\n", txt1, txt2);
    } else {
        printf("Obvod: %s < %s\n", txt1, txt2);
    }

    if (fabs(s1 - s2) < 100 * DBL_EPSILON * fabs(s2)) {
        printf("Obsah: %s = %s\n", txt1, txt2);
    } else if (s1 > s2) {
        printf("Obsah: %s > %s\n", txt1, txt2);
    } else {
        printf("Obsah: %s < %s\n", txt1, txt2);
    }

    return 0;
}

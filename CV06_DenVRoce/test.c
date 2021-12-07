#ifndef __PROGTEST__
#include <stdio.h>
#include <assert.h>
#endif /* __PROGTEST__ */

int Year_transitional(int year)
{
    if(year%4000==0){return 0 ;}
    else if(year%400==0){return 1 ;}
    else if(year%100==0){return 0 ;}
    else if(year%4==0){return 1 ;}
    else{return 0;}
}

int daytoMonth(int day, int month, int year){
    if( ( month==4 || month==6 || month==9 || month==11 ) && (day>30) ){
        return 0;
    }
    else if (month==2 && !Year_transitional(year) && day>28){
        return 0;
    }
    else if ( month==2 && day > 29 ){return 0;}
    else{
        return 1;
    }
}

int Index(int day,  int month, int year){
    int n=0;
    switch (month)
    {
    case 1:
        n=day;
        break;
    case 2:
        n=31+day;
        break;
    case 3:
        n=59+day;
        break;
    case 4:
        n=90+day;
        break;
    case 5:
        n=120+day;
        break;
    case 6:
        n=151+day;
        break;
    case 7:
        n=181+day;
        break;
    case 8:
        n=212+day;
        break;
    case 9:
        n=243+day;
        break;
    case 10:
        n=273+day;
        break;
    case 11:
        n=304+day;
        break;
    case 12:
        n=334+day;
        break;
    default:
        return 0;
        break;
    }
    if( (Year_transitional(year)) && month>2 )
    {
        //if(day )
        n++;
        return n;
    }
    else{return n;}
}

int dateToIndex(int day, int month, int year, int *idx) {
    if( (day<1 || day>31) || (month<1 || month>12) || (year<2000) ){
        return 0;
    }
    else{
        if(Year_transitional(year)){
            if( !daytoMonth(day,month,year) ){
                return 0;
            }
            *idx=Index(day,month,year);
            return 1;
        }
        else{
            if( !daytoMonth(day,month,year) ){
                return 0;
            }
            *idx=Index(day,month,year);
            return 1;
            }
        }
}

#ifndef __PROGTEST__
int main (int argc, char * argv []) {
    int idx;
    /*
    dateToIndex(  1, 12, 2000, &idx);
    printf("%d\n", idx);
    */

    assert(dateToIndex(1, 0, 2021, &idx) == 0);
    assert(dateToIndex( 31, 2, 705200, &idx) == 0);

    assert(dateToIndex( 1,  1, 2000, &idx) == 1 && idx == 1);
    assert(dateToIndex( 1,  2, 2000, &idx) == 1 && idx == 32);
    assert(dateToIndex(29,  2, 2000, &idx) == 1 && idx == 60);
    assert(dateToIndex(29,  2, 2001, &idx) == 0);
    assert(dateToIndex( 1, 12, 2000, &idx) == 1 && idx == 336);
    assert(dateToIndex(31, 12, 2000, &idx) == 1 && idx == 366);
    assert(dateToIndex( 1,  1, 1999, &idx) == 0);
    assert(dateToIndex( 6,  7, 3600, &idx) == 1 && idx == 188);
    assert(dateToIndex(29,  2, 3600, &idx) == 1 && idx == 60);
    assert(dateToIndex(29,  2, 4000, &idx) == 0);
    
    return 0;
}
#endif /* __PROGTEST__ */
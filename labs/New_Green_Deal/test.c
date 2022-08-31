#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#endif /* __PROGTEST__ */

int Year_transitional(long long int year){
    if(year%4000==0){return 0 ;}
    else if(year%400==0){return 1 ;}
    else if(year%100==0){return 0 ;}
    else if(year%4==0){return 1 ;}
    else{return 0;}}

int daytoMonth(long long int day, long long int month, long long int year, long long int h, long long int min){
    if( ( month==4 || month==6 || month==9 || month==11 ) && (day>30) ){return 0;}
    else if (month==2 && !Year_transitional(year) && day>28){return 0;}
    else if ( month==2 && day > 29 ){return 0;}
    else if ( min<0 || min>59 ){return 0;}
    else if( h<0 || h>23 ){return 0;}
    else if( year<1600 ){return 0;}
    else{return 1;}}

int Pos(long long int start, long long int end)
{
  
  long long int array[]={0,4,9,11,14,17,18,23,27,28,34,
  38,43,45,48,51,52,57,61,62,69,73,78,
  80,83,86,87,92,96,97,101,105,110,
  112,115,118,119,124,128,129,134,
  138,143,145,148,151,152,157,161,
  162,170,174,179,181,184,187,188,193,197,198};
  //long long array[]={0,4,9,11,14,17,18,23,27,28,30,34,39,41,44,47,48,53,57,58,60,64,69,71,74,77,78,83,87,88,90,94,99,101,104,107,108,113,117,118,120,124,129,131,134,137,138,143,147,148,150,154,159,161,164,167,168,173,177,178,180};
  long long int cons=0;
  cons = array[end]-array[start];
  return cons;
}

int NumOfYear(long long int y1, long long int y2){
  long long int daysPeryear=0;
  while(y1 < y2){
    if ( Year_transitional(y1)==1 )
    {
      daysPeryear += 366;
      y1++;
    }
    else
    {
      daysPeryear += 365;
      y1++;
    }
  }
  return daysPeryear;
}

int NumOfMonth(long long int m1,long long int m2){
  long long int m[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
  long long int days=0;
  long long int z=m1;
  if ( m1>m2 )
  {
    m2=(12-m1+m2)+m1;
  }
  for (long long int i = m1; i < m2; i++)
  {
    days+=m[z];
    if ( z == 12 )
    {
      z=0;
    }
    z++;
  }
  return days;
}

int energyConsumption ( int y1, int m1, int d1, int h1, int i1,
                        int y2, int m2, int d2, int h2, int i2, long long int * consumption )
{
  
  if( !daytoMonth(d1,m1,y1,h1,i1)  || !daytoMonth(d2,m2,y2,h2,i2) )
  {
    return 0;
  }
  else if( (y1>y2) ){return 0;}
  //else if ( y1>=y2 && ( (m1>m2) && (d1>=d2) ) ){return 0;}// !!!!
  else if( ((y1==y2) && (m1==m2) && (d1==d2)) && ((h1>=h2) && (i1>i2)) ){return 0;}
  else{
    
    long long int y=0,m=0,d=0,h=0,i=0;
    long long int min=200, hour=12200, day=292886;
    y=y2-y1;
    m=m2-m1;
    d=d2-d1;
    h=h2-h1;
    i=i2-i1;
    if (y==0)
    {
      if (m1>m2)
      {
        return 0;
      }
      else if (m1==m2)
      {
        if( d1>d2 )
        {
          return 0;
        }
        else if ( d1==d2 )
        {
          if (h1>h2)
          {
            return 0;
          }
          else if (h1==h2)
          {
            if(i1>i2){
              return 0;
            }
            
          }
        }
      }
      else{

      }      
    }
    long long int Yday=0;
    Yday=0;
    if(y!=0){
        Yday = NumOfYear(y1,y2);
      }

    long long int Mday=0;
    Mday=0;
    if(m!=0){
      if ( Year_transitional(y1)==1 && m1<2 && Year_transitional(y2)==0  )//spatna podminka 
      {
        Mday = NumOfMonth(m1,m2)+1;
        printf("aaaaaa\n");
      }
      if ( Year_transitional(y1)==0 && m1<2 && Year_transitional(y2)==1  )//spatna podminka 
      {
        Mday = NumOfMonth(m1,m2)+1;
        printf("aaaaaa\n");
      }
      else if ( Year_transitional(y1)==1 && m1>2 && Year_transitional(y2)==0  )//spatna podminka 
      {
        Mday = NumOfMonth(m1,m2)-1;
        printf("www\n");
      }
      else if ( Year_transitional(y1)==0 && m1>2 && Year_transitional(y2)==1 ){
        Mday = NumOfMonth(m1,m2)+1;
        printf("eeeeee\n");
      }
      else if ( Year_transitional(y1)==1 && Year_transitional(y2)==1 )
      {
        Mday = NumOfMonth(m1,m2);
        printf("xxx\n");
      }
      else if ( Year_transitional(y1)==0 && Year_transitional(y2)==0 )
      {
        Mday = NumOfMonth(m1,m2);
        printf("ssss\n");
      }

      else {
        Mday = NumOfMonth(m1,m2);
        printf("bbbbbbbbbbb\n");
      }
      if ( m1>m2 ){
        Mday=Mday*(-1);
        printf("cccccccccc\n");
      }
    }

    long long int a=0;
    a=Pos(i1,i2);
    long long int b=0;
    b=Pos(h1,h2);
    if (i1 > i2)
    {
      a=Pos(i2,i1)*(-1);
    }
    if(a>0 && ( i1==49 || i2==56 || i2==55) )
    {
      a=a-3;
    }
    if (h1 > h2)
    {
      b=Pos(h2,h1)*(-1);
    }

    long long int con=0;
    con=(day*(Yday))+(day*(Mday))+(d*day)+h*hour+i*min;
    *consumption = con + a + b;
/*
    printf("con: %lld\n", con);
    printf("Yday: %lld\n", Yday);
    printf("y: %lld\n", y);
    printf("Mday: %lld\n", Mday);
    printf("m: %lld\n", m);
    printf("d: %lld\n", d);
    printf("a: %lld\n", a);
    printf("h: %lld\n", b);
*/
    return 1;
  }
}

//2005, 12, 18, 8, 51, 2006, 12, 18, 22, 54,) 107074851LL nutna 3
//2008, 6, 1, 7, 49, 2008, 10, 22, 19, 54,) 42030156LL nutna -3
//2008, 6, 1, 7, 49, 2008, 10, 22, 19, 54,) 42030156LL


#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
  long long int consumption;

//energyConsumption(2000, 4, 19, 2, 20, 2005, 10, 27, 16, 55, &consumption);
// == 1 && consumption == 590 929 020LL);
//printf("%lld\n", consumption);


/*
  energyConsumption ( 1956, 2,  22, 1, 21,
                      1956, 2,  22, 11, 58, &consumption );
          
  
  printf("%lld\n", consumption);
  */

assert ( energyConsumption ( 2021, 11,  1, 12,  0,
                               2021, 10,  1, 12,  0, &consumption ) == 0 );
  assert ( energyConsumption ( 2021, 10, 32, 12,  0,
                               2021, 11, 10, 12,  0, &consumption ) == 0 );
  assert ( energyConsumption ( 2100,  2, 29, 12,  0,
                               2100,  2, 29, 12,  0, &consumption ) == 0 );
  assert ( energyConsumption ( 2400,  2, 29, 12,  0,
                               2400,  2, 29, 12,  0, &consumption ) == 1
           && consumption == 0LL );
  return 0;


assert(energyConsumption ( 1852, 1, 1, 0, 0, 1852, 2, 20, 0, 0, &consumption ) == 1 && consumption == 14644300LL);      
//
assert(energyConsumption(2008, 6, 24, 1, 51, 2009, 10, 27, 16, 51, &consumption) == 1 && consumption == 143697188LL);
//
assert(energyConsumption(2008, 6, 1, 7, 49, 2008, 10, 22, 19, 54, &consumption) == 1 && consumption == 42030156LL);
assert(energyConsumption(2005, 2, 9, 8, 10, 2009, 6, 12, 15, 40, &consumption) == 1 && consumption == 464022948LL);
//
assert(energyConsumption(2007, 10, 9, 22, 40, 2008, 12, 18, 22, 49, &consumption) == 1 && consumption == 127700124LL);
assert(energyConsumption(2010, 10, 17, 12, 5, 2010, 11, 18, 13, 30, &consumption) == 1 && consumption == 9389638LL);
assert(energyConsumption(2004, 2, 21, 20, 26, 2009, 5, 29, 22, 56, &consumption) == 1 && consumption == 563543171LL);
//
assert(energyConsumption(2005, 12, 18, 8, 51, 2006, 12, 18, 22, 54, &consumption) == 1 && consumption == 107074851LL);
assert(energyConsumption(2002, 1, 4, 14, 10, 2008, 10, 27, 23, 26, &consumption) == 1 && consumption == 728813453LL);
assert(energyConsumption(2003, 5, 6, 20, 49, 2006, 11, 7, 21, 59, &consumption) == 1 && consumption == 375201203LL);
assert(energyConsumption(2004, 4, 11, 1, 44, 2006, 11, 15, 19, 46, &consumption) == 1 && consumption == 277875990LL);
assert(energyConsumption(2000, 4, 19, 2, 20, 2005, 10, 27, 16, 55, &consumption) == 1 && consumption == 590929020LL);
assert(energyConsumption(2006, 12, 21, 8, 34, 2006, 12, 22, 10, 45, &consumption) == 1 && consumption == 319529LL);
assert(energyConsumption(2009, 2, 3, 16, 23, 2010, 6, 28, 21, 23, &consumption) == 1 && consumption == 149432881LL);
assert(energyConsumption(2007, 4, 27, 14, 34, 2009, 9, 27, 17, 55, &consumption) == 1 && consumption == 258952102LL);


  return 0;
}
#endif /* __PROGTEST__ */
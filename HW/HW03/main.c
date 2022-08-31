#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#endif /* __PROGTEST__ */

int Year_transitional(int year){
    if(year%4000==0){return 0 ;}
    else if(year%400==0){return 1 ;}
    else if(year%100==0){return 0 ;}
    else if(year%4==0){return 1 ;}
    else{return 0;}}

int daytoMonth(int day, int month, int year, int h, int min){
    if( ( month==4 || month==6 || month==9 || month==11 ) && (day>30) ){return 0;}
    else if (month==2 && !Year_transitional(year) && day>28){return 0;}
    else if ( month==2 && day > 29 ){return 0;}
    else if ( min<0 || min>59 ){return 0;}
    else if( h<0 || h>23 ){return 0;}
    else if( year<1600 ){return 0;}
    else{return 1;}}

int Pos(int start, int end)
{
  int array[]={0,4,9,11,14,17,18,23,27,28,34,
  38,43,45,48,51,52,57,61,62,69,73,78,
  80,83,86,87,92,96,97,101,105,110,
  112,115,118,119,124,128,129,134,
  138,143,145,148,151,152,157,161,
  162,170,174,179,181,184,187,188,193,197,198};
  long long int cons=0;
  cons = array[end]-array[start];
  return cons;
}

int NumOfYear(long long int y1, long long int y2, int flag){
  long long int daysPeryear=0;
  if(flag==1){
    daysPeryear+=365;
    y1++;
  }
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

int NumOfMonth(int m1, int m2){
  int m[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
  long long int days=0;
  for (int i = m1; i < m2; i++)
  {
    days+=m[i];
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
  else if( (y1>y2) || (m1>m2) || (d1>d2) ){return 0;}
  else if( ((y1==y2) && (m1==m2) && (d1==d2)) && ((h1>=h2) && (i1>i2)) ){return 0;}
  else{
    long long int y,m,d,h,i;
    long long int min=200, hour=12200, day=292886;
    y=y2-y1;
    if(y<0)
    {
      y*=(-1);
    }
    m=m2-m1;
    if(m<0)
    {
      m*=(-1);
    }
    d=d2-d1;
    if(d<0)
    {
      d=d*(-1);
    }

    h=h2-h1;
    i=i2-i1;

    long long int Yday=0;
    if(y!=0){
      if ( Year_transitional(y1)==1 && ( m1<2 || (m2==2 && d1<28) ) )
      {
        Yday = NumOfYear(y1,y2,0);
      }
        Yday = NumOfYear(y1,y2,1);
      }

    long long int Mday=0;
    if(m!=0){
      if ( Year_transitional(y1)==1 && ( (m1<2 && m2>2)  ) )
      {
        Mday = NumOfMonth(m1,m2)+1;
      }
      else{
       Mday = NumOfMonth(m1,m2);
      }
      
    }

    long long int a=Pos(i1,i2);
    long long int b=Pos(h1,h2);
    if (i1 > i2)
    {
      a=Pos(i2,i1)*(-1);
    }
    if (h1 > h2)
    {
      b=Pos(h2,h1)*(-1);
    }

    long long int con=(day*Yday)+(day*Mday)+(d*day)+h*hour+i*min;
    *consumption = con + a + b ;




    return 1;
  }
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
  long long int consumption;

  

  assert ( energyConsumption ( 2021, 10,  1, 13, 15,
                               2021, 10,  1, 18, 45, &consumption ) == 1
           && consumption == 67116LL );
  assert ( energyConsumption ( 2021, 10,  1, 13, 15,
                               2021, 10,  2, 11, 20, &consumption ) == 1
           && consumption == 269497LL );
  assert ( energyConsumption ( 2021,  1,  1, 13, 15,
                               2021, 10,  5, 11, 20, &consumption ) == 1
           && consumption == 81106033LL );
  assert ( energyConsumption ( 2024,  1,  1, 13, 15,
                               2024, 10,  5, 11, 20, &consumption ) == 1
           && consumption == 81398919LL );
  assert ( energyConsumption ( 1900,  1,  1, 13, 15,
                               1900, 10,  5, 11, 20, &consumption ) == 1
           && consumption == 81106033LL );
  assert ( energyConsumption ( 2021, 10,  1,  0,  0,
                               2021, 10,  1, 12,  0, &consumption ) == 1
           && consumption == 146443LL );
  assert ( energyConsumption ( 2021, 10,  1,  0, 15,
                               2021, 10,  1,  0, 25, &consumption ) == 1
           && consumption == 2035LL );
  assert ( energyConsumption ( 2021, 10,  1, 12,  0,
                               2021, 10,  1, 12,  0, &consumption ) == 1
           && consumption == 0LL );
  assert ( energyConsumption ( 2021, 10,  1, 12,  0,
                               2021, 10,  1, 12,  1, &consumption ) == 1
           && consumption == 204LL );
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
}
#endif /* __PROGTEST__ */
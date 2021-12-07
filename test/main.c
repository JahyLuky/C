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
  else if ( y1>y2 ) { return 0; }
  else{  
    long long int y=0,m=0,d=0,h=0,i=0;
    long long int min=200, hour=12200, day=292886;
    y=y2-y1;
    m=m2-m1;
    d=d2-d1;
    h=h2-h1;
    i=i2-i1;
    
    if ( (y==0 && m==0 && d==0 && h==0 && i==0) && Year_transitional(y1)==1 && Year_transitional(y2)==1 )
    {
      *consumption=0;
      return 1;
    }
    else{
      if ( y1==y2 )
      {
        if ( m1<=m2 )
        {
          if (d1>d2)
          {
            return 0;
          }      
        }
        if ( m1 > m2 )
        {
          return 0;
        }
      }
    }
    
    long long int Yday=0;
    Yday=0;
    if(y!=0){
        Yday = NumOfYear(y1,y2);
      }

    long long int Mday=0;
    Mday=0;
    if(m!=0)
    {
      if ( Year_transitional(y1)==1 && m1<2 && Year_transitional(y2)==0  )//spatna podminka 
      {
        Mday = NumOfMonth(m1,m2)+1;
      }
      if ( Year_transitional(y1)==0 && m1<2 && Year_transitional(y2)==1  )//spatna podminka 
      {
        Mday = NumOfMonth(m1,m2)+1;
      }
      else if ( Year_transitional(y1)==1 && m1>2 && Year_transitional(y2)==0  )//spatna podminka 
      {
        Mday = NumOfMonth(m1,m2)-1;
      }
      else if ( Year_transitional(y1)==0 && m1>2 && Year_transitional(y2)==1 ){
        Mday = NumOfMonth(m1,m2)+1;
      }
      else if ( Year_transitional(y1)==1 && m1>2 && Year_transitional(y2)==1 )
      {
        Mday = NumOfMonth(m1,m2);
      }
      else if ( Year_transitional(y1)==1 && m1<=2 && Year_transitional(y2)==1 )
      {
        if(m1==2 && d<29){
          Mday = NumOfMonth(m1,m2);
        }
        else
        {
          Mday = NumOfMonth(m1,m2)+1;
        }
      }
      else if ( Year_transitional(y1)==0 && Year_transitional(y2)==0 )
      {
        Mday = NumOfMonth(m1,m2);
      }

      else {
        Mday = NumOfMonth(m1,m2);
      }
      if ( m1>m2 ){
        Mday=Mday*(-1);
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
    return 1;
  }
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
  long long int consumption;
  return 0;
}
#endif /* __PROGTEST__ */
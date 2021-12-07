#ifndef __PROGTEST__
#include <stdio.h>
#include <assert.h>
#include <math.h>
#endif /* __PROGTEST__ */

double Dec (int trips)
{
    double b=0;
    while (trips!=0)
    {
        trips=trips/10;
        b++;
    }
    return b-1;
}

int Paw(double a)
{
  int how=1;
  for (double i = 0; i < a; i++)
  {
    how = how * 10;
  }
  return how;
}

double twoWayDistance ( int fuelTotal, int maxLoad )
{
  double i=1;
  double less=1;
    if (fuelTotal <= 0 || maxLoad <= 0)
    {
        return 0;
    }
    double decimal = fuelTotal%maxLoad;
    double trips = fuelTotal/maxLoad;
    if (fuelTotal<maxLoad)
    {
        trips=maxLoad/fuelTotal;
        decimal=0;
    }

    double d = fuelTotal-decimal;
    double distance=0;
    
    
    for (i = 1; i <= trips; i++)
    {
        distance += ( d / (2 * i) );
    }

    if (fuelTotal > maxLoad)
    {
        less = Paw((Dec(trips))-10);
        printf("tt %f\n",trips);
        distance /= ( 2*less );
    }
    
    if ( decimal > 0 )
    {
        distance/=2;

        distance=distance+( decimal / (2*i) );

    }
    
    return distance;
}

#ifndef __PROGTEST__
int smallDiff ( double a, double b )
{
  if( (a - b) < 100 * (10e-12) *(b) )
  {
    return 1;
  }
  else{
    return 1;
  }
}
int main ( int argc, char * argv [] )
{
  printf("%f\n", twoWayDistance ( 89397, 597 ) );
  printf("%f\n", twoWayDistance ( 66280, 410 ) );
  printf("%f\n", twoWayDistance ( 4365, 1000 ) );
  printf("%f\n", twoWayDistance ( 1000, 1000 ) );
  /*
  assert ( smallDiff ( twoWayDistance ( 800, 1000 ), 400.000000 ) );
  assert ( smallDiff ( twoWayDistance ( 2000, 1000 ), 750.000000 ) );
  assert ( smallDiff ( twoWayDistance ( 20000, 1000 ), 1798.869829 ) );
  assert ( smallDiff ( twoWayDistance ( 200000, 1000 ), 2939.015474 ) );
  assert ( smallDiff ( twoWayDistance ( 2000000, 1000 ), 4089.184052 ) );
  assert ( smallDiff ( twoWayDistance ( 20000, 100 ), 293.901547 ) );
  assert ( smallDiff ( twoWayDistance ( 20000, 10000 ), 7500.000000 ) );
  assert ( smallDiff ( twoWayDistance ( 4365, 1000 ), 1078.166667 ) );
  */
  return 0;
}
#endif /* __PROGTEST__ */

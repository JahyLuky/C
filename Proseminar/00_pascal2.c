#include <stdio.h>

/* Program vypise Pascaluv trojuhelnik. Tedy vypise kombinacni cisla:
 * C(0,0)
 * C(1,0) C(1,1)
 * C(2,0) C(2,1) C(2,2)
 * .....
 *
 * V teto verzi bude reseni s rozumnym clenenim do funkci.
 *
 * Program funguje, ale pocita spatne vysledky pocinaje C (13,1)
 */
#define ROWS  20

/*-----------------------------------------------------------------------------------------------*/
int                fact                                    ( int               n )
{
  int i, res = 1;
  for ( i = 1; i <= n; i ++ )
    res *= i;
  return res;
}
/*-----------------------------------------------------------------------------------------------*/
int                comb                                    ( int               n,
                                                             int               k )
{
  return fact ( n ) / fact ( k ) / fact ( n - k );
}
/*-----------------------------------------------------------------------------------------------*/
void               pascalTriangleRow                       ( int               rowNr )
{
  int i;
  for ( i = 0; i <= rowNr; i ++ )
  {
    if ( i > 0 ) printf ( " " );
    printf ( "%d", comb ( rowNr, i ) );
  }
  printf ( "\n" );
}
/*-----------------------------------------------------------------------------------------------*/
void               pascalTriangle                          ( int               rows )
{
  int i;

  for ( i = 0; i < rows; i ++ )
    pascalTriangleRow ( i );
}
/*-----------------------------------------------------------------------------------------------*/
int main ( void )
{
  pascalTriangle ( ROWS );
  return 0;
}

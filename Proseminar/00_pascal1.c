#include <stdio.h>

/* Program vypise Pascaluv trojuhelnik. Tedy vypise kombinacni cisla:
 * C(0,0)
 * C(1,0) C(1,1)
 * C(2,0) C(2,1) C(2,2)
 * .....
 *
 * V teto verzi bude reseni BEZ rozumneho cleneni do funkci.
 *
 * Program funguje, ale:
 * - neni moc prehledny
 * - pocita spatne vysledky pocinaje C (13,1)
 */
#define ROWS  20

int main ( void )
{
  int i, j;
  for ( i = 0; i < ROWS; i ++ )
  {
    for ( j = 0; j <= i; j ++ )
    {
      int num = 1, den = 1, k;
    
      for ( k = 1; k <= i; k ++ )
        num *= k;
    
      for ( k = 1; k <= j; k ++ )
        den *= k;
    
      for ( k = 1; k <= i - j; k ++ )
        den *= k;
      if ( j > 0 ) printf ( " " );
      printf ( "%d", num / den );
    }
    printf ( "\n" );
  }
  return 0;
}

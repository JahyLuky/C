#include <stdio.h>

/* Program vypise Pascaluv trojuhelnik. Tedy vypise kombinacni cisla:
 * C(0,0)
 * C(1,0) C(1,1)
 * C(2,0) C(2,1) C(2,2)
 * .....
 *
 * V teto verzi bude reseni s rozumnym clenenim do funkci. Kombinacni cislo
 * nebude pocitane z definice, ale z jiz zkraceneho zlomku. Tim se snizi
 * velikost citatete a jmenovatele, tedy pri omezenem rozsahu celych cisel se efektivne
 * zvysi pocet spravne vypoctenych radek.
 *
 *                      n!        n (n-1)(n-2)..(n-k+1) (n-k)!     n (n-1)(n-2)..(n-k+1)
 * Plati: C(n,k) = ------------ = ----------------------------- = -----------------------
 *                  k! (n-k)!     k! (n-k)!                         k!
 *
 * Dale vyuzijeme symetrie. Plati: C(n,k) = C(n, n-k). Tedy zvolime mensi ze dvojice (k ; n-k)
 *
 * Program spravne pocita C(13,12), nefunguje pro C(19,8)
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
  int i, num = 1;

  if ( k > n / 2 ) k = n-k;

  for ( i = 0; i < k; i ++ )
    num *= n - i;

  return num / fact ( k );
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

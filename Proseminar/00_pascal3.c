#include <stdio.h>

/* Program vypise Pascaluv trojuhelnik. Tedy vypise kombinacni cisla:
 * C(0,0)
 * C(1,0) C(1,1)
 * C(2,0) C(2,1) C(2,2)
 * .....
 *
 * V teto verzi bude reseni s rozumnym clenenim do funkci. Predchozi verze 
 * spravne pocitala do C(13,1). Pokud bychom zmenili datovy typ na unsigned long long,
 * zvysi se rozsah do C(21,1). Ukazeme si, jak lze pri zachovani typu int rozsah zvysit 
 * jeste vice.
 * Kombinacni cislo nebude pocitane z definice, ale z jiz zkraceneho zlomku. Tim se snizi
 * velikost citatete a jmenovatele, tedy pri omezenem rozsahu celych cisel se efektivne
 * zvysi pocet spravne vypoctenych radek.
 *
 *                      n!        n (n-1)(n-2)..(n-k+1) (n-k)!     n (n-1)(n-2)..(n-k+1)
 * Plati: C(n,k) = ------------ = ----------------------------- = -----------------------
 *                  k! (n-k)!     k! (n-k)!                         k!
 *
 * Program spravne pocita C(13,1), nefunguje pro C(13,12)
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

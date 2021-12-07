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
 * Posledni trik: nepocitame citatele a jmenovatele zvlast. Operace provadime prokladane:
 *

 *                n!        n (n-1)(n-2)..(n-k+1)     n (n-1)(n-2)..(n-k+1)
 * C(n,k) = ------------ = ----------------------- = -----------------------
 *            k! (n-k)!     k!                        1 2 3 4 ... k
 *
 *  C(n,k) = n / 1 * (n-1) / 2 * (n-2) / 3 * (n-3) / 4 .... * (n-k+1) / k
 *
 * Hodnota narusta souciny v citateli a zaroven klesa pri deleni hodnotami ze jmenovate.
 * Navic si vsimnete, ze nikdy nedojde k zaokrouhleni pri celociselnem deleni:
 * jmenovatelem 2 se deli soucin n (n-1)       -> bud n nebo n-1 je sude, deleni projde beze zbytku
 * jmenovatelem 3 se deli soucin n (n-1) (n-2) -> bud n, n-1 nebo n-2 je delitelne 3,
 * jmenovatelem 4 se deli soucin n (n-1) (n-2)(n-3) -> bud n, n-1,n-2 nebo n-3 je delitelne 4,
 *  ...
 * Datovy typ jsme zmenili na neznamenkovy (vyssi rozsah).
 * Program nedokaze vypocitat C(31,15). Pro vetsi rozsah by jiz bylo potreba pouzit vetsi datovy typ.
 */
#define ROWS  32

/*-----------------------------------------------------------------------------------------------*/
unsigned int       comb                                    ( int               n,
                                                             int               k )
{
  int i;
  unsigned int res = 1;

  if ( k > n / 2 ) k = n-k;

  for ( i = 0; i < k; i ++ )
    res = res * (n-i) / (i + 1);
  return res;
}
/*-----------------------------------------------------------------------------------------------*/
void               pascalTriangleRow                       ( int               rowNr )
{
  int i;
  for ( i = 0; i <= rowNr; i ++ )
  {
    if ( i > 0 ) printf ( " " );
    printf ( "%u", comb ( rowNr, i ) );
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

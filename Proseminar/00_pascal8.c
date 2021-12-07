#include <stdio.h>
#include <limits.h>

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
 * Datovy typ jsme zmenili na unsigned 64 bit.
 * Program nedokaze vypocitat C(61,30).
 * Funkce comb dokaze rozpoznat, ze vysledna hodnota je mimo rozsah datoveho typu a
 * problem hlasi volajicimu. Musi pouzivat navratovou hodnotu + vystupni parametr
 */
#define ROWS  70

/*-----------------------------------------------------------------------------------------------*/
int                comb                                    ( int               n,
                                                             int               k,
                                                             unsigned long long * res )
{
  int i;

  *res  = 1;
  if ( k > n / 2 ) k = n-k;

  for ( i = 0; i < k; i ++ )
  {
    /* cheme zajistit, aby se vysledek *res * (n+i) vesel do rozsahu long long
     * podminka:
     *  if ( *res * (n+i) > ULLONG_MAX )
     * je nesmyslna. Vysledek nasobeni bude vzdy mensi nebo roven ULLONG_MAX. Vlastni nasobeni
     * totiz probiha v tomto datovem typu. Proto podminku vydelime (n+i) a prevedeme na tvar,
     * kde vysledek operace vzdy padne do rozsahu unsigned long long. Uprava neni zcela
     * ekvivalentni, deleni v celych cislech zahazuje zbytek.
     */
  
    if ( *res > ULLONG_MAX / (n + i) ) return 0;
    *res = *res * (n-i) / (i + 1);
  }
  return 1;
}
/*-----------------------------------------------------------------------------------------------*/
int                pascalTriangleRow                       ( int               rowNr )
{
  int i;
  for ( i = 0; i <= rowNr; i ++ )
  {
    unsigned long long int c;
    if ( ! comb ( rowNr, i, &c ) )
    {
      fprintf ( stderr, "C(%d,%d) long long overflow\n", rowNr, i );
      return 0; /* hlasime chybu vyse */
    }
    if ( i > 0 ) printf ( " " );
    printf ( "%llu", c );
  }
  printf ( "\n" );
  return 1;
}
/*-----------------------------------------------------------------------------------------------*/
int                pascalTriangle                          ( int               rows )
{
  int i;

  for ( i = 0; i < rows; i ++ )
    if ( ! pascalTriangleRow ( i ) )
      return 0; /* predani chyby vyse */
  return 1;
}
/*-----------------------------------------------------------------------------------------------*/
int main ( void )
{
  if ( ! pascalTriangle ( ROWS ) )
  {
    /* finalni zpracovani chyby. Zde nejspise ukonceni programu */
    fprintf ( stderr, "failed\n" );
    return 1;
  }
  return 0;
}
/*-----------------------------------------------------------------------------------------------*/

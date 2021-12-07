#include <stdio.h>

/* Program nacte cislo o volitelnem zakladu (2-36) a zobrazi je v soustave
 * o zvolenem (jinem) zakladu (2-36)
 *
 * Reseni s pouzitim funkci.
 */

/*---------------------------------------------------------------------------*/
/* Funkce zjisti, jakou hodnotu ma cifra c (0-9,a-z). Pokud cifra c neni platna
 * vraci -1
 */
int digit2num ( char c )
{
  if ( c >= '0' && c <= '9' )
    return c - '0';
  else if ( c >= 'A' && c <= 'Z' )
    return c - 'A' + 10;
  else if ( c >= 'a' && c <= 'z' )
    return c - 'a' + 10;
  else
    return -1;
}
/*---------------------------------------------------------------------------*/
/* Funkce prevede zadanou cifru na jeji znakovou podobu.
 */
char num2digit ( int num )
{
  if ( num <= 9 ) 
    return '0' + num;
  else
    return 'a' + num - 10; 
}
/*---------------------------------------------------------------------------*/
/* funkce zjisti, zda cifra c je platna vsoustave o zakladu radix. Vraci priznak 
 * platna (!=0)/neplatna(0)
 */
int validDigit ( char c, int radix )
{
  int num;
  
  num = digit2num ( c );
  return num >= 0 && num < radix ;
}
/*---------------------------------------------------------------------------*/
/* funkce vyzve uzivatele k zadani zakladu soustavy. Zaklad nacte a zkontroluje.
 * Vraci nacteny zaklad nebo -1 pro chybu
 */ 
int readRadix ( char * prompt )
{
  int radix;
  
  printf ( "%s", prompt );
  if ( scanf ( "%d", &radix ) != 1 || radix <= 1 || radix > 36 ) return -1;
  return radix;
}
/*---------------------------------------------------------------------------*/
/* Funkce nacte ze std. vstupu cislo o zakladu radix. Vraci nactene cislo,
 * pripadne hodnotu -1 pro chybu.
 */
int readNumber ( int radix )
{
  char c;
  int src;

  printf ( "Zadejte cislo v soustave %d:\n", radix );
  /* prvni cifra je povionna, preskakujeme whitespace - " %c"
   */
  if ( scanf ( " %c", &c ) != 1 || ! validDigit ( c, radix ) ) return -1;
  src = digit2num ( c );

  /* dalsi cifry, nepreskakujeme whitespace - "%c"
   */   
  while ( scanf ( "%c", &c ) == 1 && validDigit ( c, radix ) )
  {
    src = src * radix + digit2num ( c );
  }
  ungetc ( c, stdin );
  return src;
}
/*---------------------------------------------------------------------------*/
/* funkce zobrazuje jednotlive cifry prevadeneho cisla
 */
void printDigits ( int num, int radix )
{
  if ( num >= radix )
    printDigits ( num / radix, radix );
  printf ( "%c", num2digit ( num % radix ) );
}
/*---------------------------------------------------------------------------*/
/* funkce zobrazi cislo num v soustave radix
 */
void printNumber ( int num, int radix )
{
  printf ( " = " );
  printDigits ( num, radix );
  printf ( " (%d)\n", radix ); 
}  
/*---------------------------------------------------------------------------*/
int main ( int argc, char * argv [] )
{
  int num, srcRadix, dstRadix;

  srcRadix = readRadix ( "Zadejte zaklad zdrojove soustavy:\n" );
  if ( srcRadix == -1 )
  {
    printf ( "Nespravny vstup.\n" );
    return 1;
  }

  num = readNumber ( srcRadix );
  if ( num == -1 )
  {
    printf ( "Nespravny vstup.\n" );
    return 1;
  }

  dstRadix = readRadix ( "Zadejte zaklad cilove soustavy:\n" );
  if ( srcRadix == -1 )
  {
    printf ( "Nespravny vstup.\n" );
    return 1;
  }

  printNumber ( num, dstRadix );
  return 0;
}

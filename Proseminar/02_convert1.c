#include <stdio.h>

/* Program nacte cislo o volitelnem zakladu (2-36) a zobrazi je v soustave
 * o zvolenem (jinem) zakladu (2-36)
 *
 * Toto reseni nepouziva funkce. Je dlouhe a tezkopadne. Dlouhe casti kodu se opakuji.
 */

int main ( int argc, char * argv [] )
{
  int src, srcRadix, dstRadix, num, start;
  char c;
  
  printf ( "Zadejte zaklad soustavy:\n" );
  if ( scanf ( "%d", &srcRadix ) != 1 || srcRadix <= 1 || srcRadix > 36 )
  {
    printf ( "Nespravny vstup.\n" );
    return 1;
  }

  printf ( "Zadejte cislo v soustave %d:\n", srcRadix );

  /* Musime nacist nejmene 1 cifru cisla v soustave srcRadix
   * Nemuzeme cist vstup jako cislo, musime jej cist po znacich.
   * Konverze " %c" (s mezerou) znamena, ze scanf ma preskocit pripadne bile znaky.
   * Bile znaky pred zacatkem cisla chceme ignorovat.
   */  
  if ( scanf ( " %c", &c ) != 1 )
  {
    printf ( "Nespravny vstup.\n" );
    return 1;
  }
  /* Prevedeme znak na ciselnou reprezentaci
   * znaky 0 - 9  budou cisla 0-9
   * pismena a-z A-Z budou cisla 10 - 35
   */
  if ( c >= '0' && c <= '9' )
    num = c - '0';
  else if ( c >= 'A' && c <= 'Z' )
    num = c - 'A' + 10;
  else if ( c >= 'a' && c <= 'z' )
    num = c - 'a' + 10;
  else
  {
    printf ( "Nespravny vstup.\n" );
    return 1;
  }  
  /* Osetreni, zda cifra neni nad zakladem (napr. cifra 2 ve dvojkovem zapisu)
   */ 
  if ( num >= srcRadix ) 
  {
    printf ( "Nespravny vstup.\n" );
    return 1;
  }  
  src = num;
  
  /* Nyni cteme zbyvajici cifry cisla. Zde je format "%c", tedy NEBUDEME preskakovat 
   * pripadny whitespace. Pokdu se nam znak na vstupu nepodari pridat k vytvarenemu cislu,
   * skoncime s nacitanim a znak vratime zpet.
   */
  while ( scanf ( "%c", &c ) == 1 )
  {
    if ( c >= '0' && c <= '9' )
      num = c - '0';
    else if ( c >= 'A' && c <= 'Z' )
      num = c - 'A' + 10;
    else if ( c >= 'a' && c <= 'z' )
      num = c - 'a' + 10;
    else
    {
      /* zde jsme vyzvedli znak ze vstupu, ktery jiz nelze pridat. Meli bychom jej vratit.
       * to lze pomoci ungetc
       */
      ungetc ( c, stdin ); 
      break;
    }   
    if ( num >= srcRadix ) 
    {
      /* znak jiz nepatri k cislu, vratit
       * pomoci ungetc
       */ 
      ungetc ( c, stdin ); 
      break; 
    }
    src = srcRadix * src + num;
  }

  /* promenna src obsahuje zadani zdrojoveho cisla, ktere je prevedene
   * na binarni reprezentaci
   */
  
  printf ( "Zadejte zaklad cilove soustavy:\n" );
  if ( scanf ( "%d", &dstRadix ) != 1 || dstRadix <= 1 || dstRadix > 36 )
  {
    printf ( "Nespravny vstup.\n" );
    return 1;
  }

  printf ( " = " );

  /* Cislo src chceme vypsat po cifrach, ve spravnem poradi. Najdeme si mocninu 
   * dstRadix takovou, ze je nejblizsi vetsi nez nase cislo src (promenna start)
   * To bude nejvyssi rad zobrazovaneho cisla.
   */    

  start = 1;
  while ( start <= src )
  {
    start *= dstRadix;
  }
  if ( src == 0 )         /* nulu osetrime zvlast */ 
    printf ( "0" );
  else 
    while ( start > 1 )
    {
      start /= dstRadix;
      num = src / start; /* cifra v nejvyssi radu */
      src %= start;      /* a ze src nejvyssi rad odstranime */
    
      if ( num <= 9 ) 
        printf ( "%d", num );
      else
        printf ( "%c", num - 10 + 'a' ); 
    } 
  printf ( " (%d)\n", dstRadix ); 
  return 0;
}

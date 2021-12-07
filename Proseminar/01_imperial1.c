#include <stdio.h>

/*----------------------------------------------------------------------------*/
/* Funkce prepocte imperialni vzdalenost (yard/feet/inch) na metrickou, 
 * kterou vracijako navratovou hodnotu.
 */
double imperial2metric ( int yd, int ft, int in )
{
  return 2.54 * ( in + 12 * ft + 36 * yd );
}
/*----------------------------------------------------------------------------*/
/* Funkce prepocte metrickou vzdalenost na imperialni  (yard/feet/inch).
 * Protoze se vraci 3 hodnoty, jsou predane pomoci out parametru.
 * Pozor, je potreba pridavat znaky *.
 */
void metric2imperial ( int cm, int * yd, int * ft, int * in )
{ 
  int inches;
  
  inches = (int)( cm / 2.54 + 0.5 );
  *yd = inches / 36;
  inches %= 36;
  *ft = inches / 12;
  *in = inches % 12;
}
/*----------------------------------------------------------------------------*/
/* Funkce nacte vstup a pozna, zda je na vstupu udaj metricky nebo imperialni.
 * Podle toho provede potrebnou konverzi. Funkce vraci 0 pro neuspech, != 0
 * pro uspech.
 */
int convert ( void )
{ 
  int conv, yd, ft, in;
  char c;
  
  printf ( "Zadejte vzdalenost:\n" );
  conv = scanf ( "%d yd %d ft %d in%c", &yd, &ft, &in, &c );

  if ( conv == 4 && c == '\n' )
  { 
    /* pokud jsou nactena 3 cisla a ukoncujici \n */
    printf ( " = %f cm\n", imperial2metric ( yd, ft, in ) );
    return 1;
  }
  else if ( conv == 1 && scanf ( " cm%c", &c ) == 1 && c == '\n' )
  {
    /* funkce drive nacetla 1 cislo do promenne yd a pak se ji nepodarilo 
     * nalezt text "yd". Pokud ale zkusime na vstupu hledat cm, funkce uspela.
     * Na vstupu tedy bylo xx cm, mame tedy prevadet na imperialni jednotky.
     */
    metric2imperial ( yd, &yd, &ft, &in );
    printf ( " = %d yd %d ft %d in\n", yd, ft, in );
    return 1;
  } 
  else if ( conv == EOF )
    return 0; 
  /* Na vstupu bylo nejake "smeti". Vycistime vstup.
   */ 
  while ( 1 )
  {
    int x = fgetc ( stdin );      
    if ( x == '\n' || x == EOF ) break;
  }
  return 0; 
}
/*----------------------------------------------------------------------------*/
int main ( int argc, char * argv [] )
{
  while ( 1 )
  {
    if ( ! convert () )
    {
      /* Pokud se nepodarilo nacist vstup, bylo to bud nespravnym 
       * formatem nebo EOF. To zde rozlisime.
       */
      if ( feof ( stdin ) ) break;
      printf ( "Nespravny vstup.\n" );
    }
  }
  return 0; 
}

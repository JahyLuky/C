#ifndef __PROGTEST__
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#endif /* __PROGTEST__ */

int toWords( char * text )
{
  char * newText;
  int spaces = 0;
  const char * space = " "; 
  while ( * text )
  {
    newText = (char*) malloc( 100 * sizeof(char) );
    if( isalpha(*text) != 0 )
    {
      strcpy(newText,text);
      newText++;
      spaces = 0;
    }
    else
    {
      spaces++; // cout nonalpha chars
      if ( spaces == 1 )
      {
        // add 1 space if 1 char is nonalpha
        strcpy(newText,space);
        newText++;
      }
    }
    text++;
  }
  printf("%s\n", text);
  printf("%s\n", newText);
  free(newText);
  return 1;
}

int sameWords ( const char * a, const char * b )
{
  int flag = 0;
  char * x = strdup(a);
  char * y = strdup(b);
  /*
  int lenA = strlen(x);
  char * newA = (char*) malloc( lenA * sizeof(char) );
  int lenB = strlen(y);
  char * newB = (char*) malloc( lenB * sizeof(char) );
  */
  toWords(x);
  toWords(y);

  if ( flag == 0 )
  {
    printf("0\n");
    free(x);
    free(y);
    return 0;
  }
  else
  {
    printf("1\n");
    free(x);
    free(y);
    return 1;
  }
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
  sameWords ( "a!", "ta" );
  sameWords ( "a", "ta" );
  sameWords ( "ta", "a" );
  /*
  assert ( sameWords ( "Hello students.", "HELLO studEnts!" ) == 1 );
  assert ( sameWords ( " He said 'hello!'", "'Hello.' he   said." ) == 1 );
  assert ( sameWords ( "He said he would do it.", "IT said: 'He would do it.'" ) == 1 );
  assert ( sameWords ( "one two three", "one two five" ) == 0 );
  */
  return 0;
}
#endif /* __PROGTEST__ */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
/*
int compare ( char * s1, char * s2, int len )
{
  while ( len -- )
  {
    if ( tolower ( *s1 ) != tolower ( *s2 ) )
    {
      return 0;
    }
    else
    {
      s1++;
      s2++;
    }
  }
  if ( isalpha(*s1) != 0 )
  {
    return 0;
  }
  return 1;
}

int strcasestr ( char * text, char * pattern )
{
  int patternLen = strlen ( pattern );

  while ( * text )
  {
    if ( compare(text, pattern, patternLen) ) 
    {
      //printf("patern: %s\n",pattern);
      //printf("text: %s\n",text);
      return 1;
    }
    else
    {
      text ++;
    }
  }
  return 0;
}
*/
char * cut_to_aplha ( char * string, int len )
{
  for (int i = 0; i < len; i++)
  {
    if( isalpha(string[i]) == 0 )
    {
      string[i] = ' ';
    }
    string[i] = tolower(string[i]);
  }
  return string;
}


int sameWords ( const char * a, const char * b )
{
  int len1 = strlen(a);
  int len2 = strlen(b);

  char * x = strdup(a);
  char * y = strdup(b);
  x = cut_to_aplha(x, len1);
  y = cut_to_aplha(y, len2);

  const char * s = " ";
  char * token1 = strtok(x, s);
  char * token2 = strtok(y, s);
  int n = 0;
  int right = 0;
  while( token1 != NULL )
  {
    n++;
    while ( token2 != NULL )
    {
        if ( strcmp(token1, token2) == 0 )
        {
            printf("t1: %s\n", token1);
            printf("t2: %s\n", token2);
            right++;
        }
        token2 = strtok(NULL, s); 
    }
    token1 = strtok(NULL, s);
    token2 = strtok(y, s);
  }
  if ( right < n )
  {
    printf("!RIGHT\n");
    free(x);
    free(y);
    return 0;
  }
  free(x);
  free(y);
  printf("Jupii\n");
    
  return 1;
}

int main ( int argc, char * argv [] )
{
  //sameWords ( "Hello abc", "abc !Hello " );
  //sameWords ( "Hello a", "HELLO a" );
  //sameWords ( "a!", "ta" );
  //sameWords ( "at", "t" );
  sameWords ( "Hello!! a", "at. HELLO" );
  //sameWords ( "Hello! .,.,.,. a", "HELLO a." );
  sameWords ( "Hello a", "a HELLO" );
  //sameWords ( "9 Hello: a students", "HELLO studEnts" );
  /*
  sameWords ( "Hello students.", "HELLO studEnts!" );
  sameWords ( " He said 'hello!'", "'Hello.' he   said." ) ;
  sameWords ( "He said he would do it.", "IT said: 'He would do it.'" );
  sameWords ( "one two three", "one two five" );
  */
}
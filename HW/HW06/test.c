#ifndef __PROGTEST__
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#endif /* __PROGTEST__ */

/*!
 * Read string and replace every char (isalpha=0) for new line.
 *
 * \param[in] string Loaded sting.
 * \param[in] len Loaded string lenght.
 *
 * \return replaced string.
 */
char * cut_to_aplha ( char * string, int len )
{
  for (int i = 0; i < len; i++)
  {
    if( isalpha(string[i]) == 0 )
    {
      string[i] = '\n';
    }
    else if( isalpha(string[i]) != 0 )
    {
      string[i] = tolower(string[i]);
    }
  }
  return string;
}

/*!
 * Read strings and determine if they consist of the same words.
 *
 * \param[in] a Fisrt string.
 * \param[in] b Second string.
 *
 * \return 0 for non matching words, 1 for matching.
 */
int sameWords ( const char * a, const char * b )
{
  int len1 = strlen(a);
  int len2 = strlen(b);
  char * x = strdup(a);
  char * y = strdup(b);
  x = cut_to_aplha(x, len1);
  y = cut_to_aplha(y, len2);

  // w is sum of words in first string 'x'
  // r is sum of same words 'w' in string 'y'
  int r1 = 0, r2 = 0, w1 = 0, w2 = 0;
  const char * s = "\n";
  char * pattern;
  char * word1 = strtok(x, s);
  while ( word1 != NULL )
  {
    w1++;
    pattern = strstr(y, word1);
    if ( pattern )
    {
      r1++;
    }
    word1 = strtok(NULL, s);
  }
  x = cut_to_aplha(x, len1);
  char * word2 = strtok(y, s);
  while ( word2 != NULL )
  {
    w2++;
    pattern = strstr(x, word2);
    if ( pattern )
    {
      r2++;
    }
    word2 = strtok(NULL, s);
  }

  if( w1 > r1 || w2 > r2 ) 
  {
    free(x);
    free(y);
    return 0;
  }
  free(x);
  free(y);
  return 1;
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
  assert ( sameWords ( "Hello students.", "HELLO studEnts!" ) == 1 );
  assert ( sameWords ( " He said 'hello!'", "'Hello.' he   said." ) == 1 );
  assert ( sameWords ( "He said he would do it.", "IT said: 'He would do it.'" ) == 1 );
  assert ( sameWords ( "one two three", "one two five" ) == 0 );
  return 0;
}
#endif /* __PROGTEST__ */

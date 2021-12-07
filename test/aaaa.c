#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

int sameWords ( const char * a, const char * b )
{
/*
   const char * ret1;
   const char * ret2;
  
  const char * newB = "HELLO";
   ret1 = strstr(a, newB);
  ret2 = strstr(b, newA);

   printf("The substring is: %s\n", ret1);
   printf("The substring is: %s\n", ret2);
*/
  char * newA = (char*) malloc( strlen(a) * sizeof(char*));
  //newA = strdup(a);
  strcpy(newA,a);
  char * newB = (char*) malloc( strlen(b) * sizeof(char*));
  //newB = strdup(b);
  strcpy(newB,b);

  const char * s = " ";
  char * token = strtok(newA, s);
  while( token != NULL ) 
  {
    
    if ( strcasecmp(newA, newB) == 0 )
    {
      printf("jeej\n");
    }
    else
    {
      printf( "%s\n", token );
    }

    token = strtok(NULL, s);
  }

  char * str = (char*) malloc( strlen(a) * sizeof(char*));
  strcpy(str, newA);
  //str[0] = 'C'; 
  printf("\n%c\n", str[0]);
  printf("%s\n", str); 
  free(str);

  return 0;
}

int main ( int argc, char * argv [] )
{
  sameWords ( "9 Hello: a students", "HELLO studEnts" );
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct string_c
{
  char * string;
  int size = 1;

  char * init ( void )
  {
    string = (char *) malloc ( size * sizeof(char) );
    string[0] = '\0'; 
    return string;
  }

  // constuctor
  // string_c();

  // constuctor with argument

  // resize
  char * resize ( char * string, int new_size )
  {
    string = (char *) realloc ( string, new_size * sizeof(char) );
    return string;
  }

  // add
  char * add ( char * string, char * text )
  {
    int string_len = strlen(string);
    int text_len = strlen(text);

    if ( string_len < text_len )
    {
      string = resize( string, text_len );
    }

    int i = 0;
    for (; i < text_len; i++)
    {
      string[i] = text[i];
    }
    string[i] = '\0';

    return string;
  }

  // copy

  // move

  // pop back

  // pop up

  // lenght


} string_c;

int main (void)
{
  char * ahoj = (char*)malloc(20*sizeof(char));
  ahoj = "Hello world!";
  string_c test;
  test.init();
  test.add( test.string, ahoj );
  printf("%s\n", test.string);


  return 1;
}
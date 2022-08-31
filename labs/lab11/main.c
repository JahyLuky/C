#include <stdio.h>
#include <stdlib.h>

void print_binary_rec ( int length, int i, char * number )
{
    if ( length == i)
    {
        number[i] = '\0';
        printf("%s\n", number);
        return;
    }
    else
    {
        number[i] = '0';
        print_binary_rec(length,i+1,number);
        number[i] = '1';
        print_binary_rec(length,i+1,number);
    }
}

void print_binary_numbers ( int length )
{
    char * buffer = (char*) malloc( (length+1) * sizeof(char) );
    print_binary_rec(length,0,buffer);
    free(buffer);
}

int main ( void )
{
	print_binary_numbers( 1 );
	print_binary_numbers( 2 );
	//print_binary_numbers( 3 );
	//print_binary_numbers( 5 );

	return 0;
}
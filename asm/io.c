#include "io.h"

#include <stdlib.h>

#define MIN_SIZE 20

char *getline( FILE * f )
{
	int c = fgetc( f );
	int pos = 0, size = MIN_SIZE;

    char *res = (char*) malloc( sizeof(char) * size );

	while( c != EOF && c != '\n' )
	{
		if( pos >= size - 1 )
		{
			size += MIN_SIZE;
			res = (char*) realloc( res, sizeof(char) * size );
		}

		res[pos++] = c;
		c = fgetc( f );
	}

	res[pos] = '\0';
	return res;
}

#define MAGIC 0xFF
#define MODE_CONSOLE 0xF0

void write_data( FILE *f, unsigned char *data, unsigned size )
{
	unsigned i;

	fputc( MAGIC, f );
	fputc( MODE_CONSOLE, f );

	for( i = 0; i < size; i++ )
		fputc( data[i], f );
}

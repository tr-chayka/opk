#include "io.h"
#include "map.h"
#include "compiler.h"

#include <stdio.h>
#include <stdlib.h>

map *load_commands()
{
	FILE *f = fopen("asm.cm", "r");
	map *m = map_create();

	if( f == NULL )
	{
		printf("Can not load commands\n");
		exit(2);
	}

	while( 1 )
	{
		char str[16], s_val[16];
		unsigned val;

		int res = fscanf(f, "%s%s\n", str, s_val );

		if( res != 2 )
			break;

		sscanf(s_val, "%x", &val);
		map_set( m, str, val );
	}

	fclose( f );
	return m;
}

int main( int argc, char *argv[] )
{
	unsigned size = 0;
	unsigned char **bin = (unsigned char**) malloc( sizeof(unsigned char*) );

	FILE *in, *out;
	map *commands = load_commands();

	if( argc < 2 || argc > 3 )
	{
		printf("no input file\n");
		return 0;
	}
	else if( argc == 3 )
	{
		in = fopen( argv[1], "r" );
		out = fopen( argv[2], "wb" );
	}
	else if( argc == 2 )
	{
		in = fopen( argv[1], "r" );
		out = fopen( "a.out", "wb" );
	}

	if( in == NULL )
	{
		printf("Can not open input file\n");
		return 2;
	}

	if( out == NULL )
	{
		printf("Can not create output file\n");
		return 2;
	}

	size = compile( in, commands, bin );

	if( !is_error() )
		write_data( out, *bin, size );

	map_free( commands );
	
	fclose( in );
	fclose( out );

	free( *bin );
	free( bin );


	system("pause");
	return 0;
}
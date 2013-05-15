#include "run/run.h"
#include "run/cmd.h"

#include <stdio.h>
#include <stdlib.h>

#define MAGIC 0xFF
#define MODE_CONSOLE 0xF0

char *get_code_from_file( char *file_name, unsigned int *size )
{
	int c = 0;
	unsigned int i = 0;
	char *code = NULL;

	FILE *file = fopen( file_name, "rb" );

	if( file == NULL )
		return NULL;

	c = fgetc( file );
	if( c != MAGIC )
	{
		fclose( file );
		return NULL;
	}

	c = fgetc( file );
	if( c != MODE_CONSOLE )
	{
		fclose( file );
		return NULL;
	}

	fseek( file, 0, SEEK_END );
	i = *size = ftell( file ) - 2;

	code = (char*)malloc( sizeof(char) * i );
	fseek( file, 2, SEEK_SET );

	i = 0;
	while( 1 )
	{
		c = fgetc( file );
		if( c == EOF )
			break;

		code[i++] = (char)c;
	}

	fclose( file );
	return code;
}

int main( int argc, char *argv[] )
{
	unsigned int code_size;
	char *code;
	int error;

	if( argc < 2 )
		return 0;

	code_size = 0;
	code = get_code_from_file( argv[1], &code_size );

	if( code == NULL )
		return 1;

	vm_init();
	error = vm_run( code, code_size );
	vm_free();

	printf("Program exited with code %d\n", error );
	system("pause");

	return 0;
}




























	/*vm_init();
	vm_run( code, 19 );
	vm_free();

	system("pause");*/
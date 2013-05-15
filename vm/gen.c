/*
*/

#include <stdio.h>
#include "run/cmd.h"

#define MAGIC 0xFF
#define MODE_CONSOLE 0xF0

int main()
{
	FILE *code_file = fopen("code.run", "wb");	

	unsigned char code[100];

	code[0] = IN;
	code[1] = STDIN_PORT;

	code[2] = MOVRR;
	code[3] = (0x01 << 4) + 0x00;

	code[4] = MOVD1;
	code[5] = 0x00;
	code[6] = '0';

	code[7] = OUT;
	code[8] = STDOUT_PORT;

	code[9] = MOVRR;
	code[10] = (0x00 << 4) + 0x01;

	code[11] = OUT;
	code[12] = STDOUT_PORT;

	code[13] = MOVD1;
	code[14] = 0x00;
	code[15] = '\n';

	code[16] = OUT;
	code[17] = STDOUT_PORT;
	code[18] = HALT;

	fputc( MAGIC, code_file );
	fputc( MODE_CONSOLE, code_file );	

	for( int i = 0; i <= 18; i++ )
		fputc( code[i], code_file );

	fclose( code_file );
	
	return 0;
}

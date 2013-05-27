#include "io.h"
#include "vector.h"
#include "compiler.h"

#include <string.h>
#include <stdlib.h>

#include "asm-cmd.h"
#include "cmd.h"

typedef unsigned char uchar;
typedef unsigned short word;

static uchar *bin;
static unsigned error, line, position;

static map *labels;
static vector *inserts;

static void _error( char *format, char *str )
{
	error = 1;
	
	if( str == NULL )
		printf( format, line );
	else
		printf( format, str, line );
}

static uchar H(	word w )
{
	return w >> 8;
}

static uchar L( word w )
{
	return w & 0xFF;
}

int is_error()
{
    return error;
}

static unsigned char get_code( map *commands, char *command )
{
	return map_get( commands, command );
}

#define NONE 1
#define LABEL 2
#define NUMBER 4
#define ADDRESS 8
#define REGISTER 16

static void write0( cmd_t co, uchar code )
{
	if( !empty(co.param1) || !empty(co.param2) )
		_error("Command '%s' must have no parameters. line: %d\n", co.command);
	else
		bin[position++] = code;
}

static void write1( cmd_t co, uchar code, uchar type )
{
	if( empty(co.param1) )
		_error( "Expected one parameter for command '%s'. line: %d\n", co.command );
	else if( !empty(co.param2) )
		_error( "Command '%s' must have only one parameter. line %d\n", co.command );
	else
		switch( type )
		{
			case REGISTER:
			{
				uchar R = get_register( co.param1 );
				
				if( R <= 0 )
					_error( "Expected register name. line: %d\n", NULL );
				else
					bin[position++] = code + R - 1;
				break;
			}
			case LABEL:
			{
				if( !is_label(co.param1) )
					_error( "Expected label name. line: %d\n", NULL );
				else
				{
					bin[position++] = code;
					vector_push( inserts, label_create(position, co.param1) );
					position += 2;
				}
				break;
			}
			case NUMBER:
			{
				unsigned data = 0;
				if( !get_int(co.param1, &data) )
					_error( "Expected number. line: %d\n", NULL );
				else
				{
					bin[position++] = code;
					if( code == PUSHD )
					{
						bin[position++] = H(data);
						bin[position++] = L(data);
					}
					else
					{
						bin[position++] = data;
					}
				}
				break;
			}
		}
}

static void writemath( cmd_t co, uchar code1, uchar code2 )
{
	int R1 = get_register( co.param1 );
	int R2 = get_register( co.param2 );

	if( empty(co.param1) || empty(co.param2) )
		_error( "Command '%s' has two parameters. line %d\n", co.command );
	else if( R1 < 0 )
		_error( "Expected register name. line %d\n", NULL );
	else
	{
		if( R2 > 0 )
		{			
			bin[position++] = code2;
			bin[position++] = ((R1 - 1) << 4) + (R2 - 1);
		}
		else
		{
			if( code2 == AND || code2 == OR || code2 == XOR ) 
				_error("Expected register name. line %d\n", NULL);
			else
			{
				unsigned data = 0;
				if( !get_int(co.param2, &data) )
					_error( "Expected number. line %d\n", NULL );
				else
				{
					bin[position++] = code1 + R1 - 1;
					bin[position++] = H(data);
					bin[position++] = L(data);
				}
			}
		}
	}
}

static void writemov( cmd_t co )
{
	if( empty(co.param1) || empty(co.param2) )
		_error( "Command '%s' has two parameters. line %d\n", co.command );
	else
	{
		int R1 = get_register( co.param1 );
		int R2 = get_register( co.param2 );
		
		unsigned D1 = 0, D2 = 0;
		
		if( R1 > 0 )
		{
			if( R2 > 0 )
			{
				bin[position++] = MOVRR;
				bin[position++] = ((R1 - 1) << 4) + (R2 - 1);
			}
			else if( get_address(co.param2, &D2) )
			{
				bin[position++] = MOVTR1 + R1 - 1;
				bin[position++] = H(D2);
				bin[position++] = L(D2);
			}
			else if( get_int(co.param2, &D2) )
			{
				bin[position++] = MOVD1 + R1 - 1;
				bin[position++] = H(D2);
				bin[position++] = L(D2);
			}
			else
				_error("Incorrect second parameter for '%s', line: '%d\n", co.command );
		}
		else
		{
			if( R2 > 0 )
			{
				if( get_address(co.param1, &D1) )
				{
					bin[position++] = MOVFR1 + R2 - 1;
					bin[position++] = H(D1);
					bin[position++] = L(D2);
				}
				else if( get_reg_address(co.param1, &D1) )
				{
					bin[position++] = MOV;
					bin[position++] = ((D1 - 1) << 4) + (R2 - 1);
				}
				else
					_error("Incorrect first parameter for '%s', line: '%d\n", co.command );
			}
			else
				_error("Expected register name. line %d\n", NULL);
		}
	}
}

static void update_labels()
{
	unsigned i, len = inserts->size;

	for( i = 0; i < len; i++ )
	{
		label_t t = vector_at( inserts, i );
		unsigned addr = map_get( labels, t.name );

		if( addr > 0 )
		{
			addr += 1024;
			bin[t.pos] = H(addr - 1);
			bin[t.pos + 1] = L(addr - 1);
		}
		else
		{
			printf( "Undefined label '%s'\n", t.name );
			error = 1;
		}
 	}
}

#define MIN_SIZE 100
unsigned compile( FILE *in, map *commands, unsigned char **_bin )
{
	unsigned size = MIN_SIZE;

    error = line = position = 0;
	bin = (unsigned char*) malloc( sizeof(unsigned char) * size );

	labels = map_create();
    inserts = vector_create();

	while( !feof(in) )
	{
		unsigned char command_code = 0;
		char *cline = getline( in );
		cmd_t co = parse_line( cline );

		free(cline);

		if( size - position <= 3 )
		{
			size += MIN_SIZE;
            bin = (unsigned char*) realloc( bin, sizeof(unsigned char) * size );
        }

		line++;
		if( co.is_error )
		{
			printf( "Unrecognized expression. line: %d position: %d\n", line, co.is_error );
			error = 1;
		}

		command_code = get_code( commands, co.command );

		if( co.label != NULL )
			map_set( labels, co.label, position + 1 );

		if( co.command[0] != '\0' && command_code == 0 )
			_error( "Unknown command '%s'. line: %d\n", co.command );
		else
		{
			switch( command_code )
			{
				case A_JMP	: write1( co, JMP,	LABEL ); break;
				case A_JE	: write1( co, JE,	LABEL ); break;
				case A_JNE	: write1( co, JNE,	LABEL ); break;
				case A_JL	: write1( co, JL,	LABEL ); break;
				case A_JLE	: write1( co, JLE,	LABEL ); break;
				case A_JG	: write1( co, JG,	LABEL ); break;
				case A_JGE	: write1( co, JGE,	LABEL ); break;
				case A_CALL : write1( co, CALL,	LABEL ); break;
				
				case A_NOP	: write0( co, NOP ); break;
				case A_RET	: write0( co, RET ); break;
				case A_HALT	: write0( co, HALT ); break;

				case A_IN	: write1( co, IN, NUMBER ); break;
				case A_OUT	: write1( co, OUT, NUMBER ); break;

				case A_INC	: write1( co, INC1, REGISTER ); break;
				case A_DEC	: write1( co, DEC1, REGISTER ); break;
				case A_NOT	: write1( co, NOT1, REGISTER ); break;
				case A_POP	: write1( co, POP1, REGISTER ); break;
				case A_PUSH	: 
					if( get_register(co.param1) )
						write1( co, PUSH1, REGISTER );
					else
						write1( co, PUSHD, NUMBER );
					break;
				case A_ADD	: writemath( co, ADDD1, ADD ); break;
				case A_SUB	: writemath( co, SUBD1, SUB ); break;
				case A_MUL	: writemath( co, MULD1, MUL ); break;
				case A_DIV	: writemath( co, DIVD1, DIV ); break;
				case A_CMP	: writemath( co, CMPD1, CMP ); break;
				case A_AND	: writemath( co, 0, AND ); break;
				case A_OR	: writemath( co, 0, OR ); break;
				case A_XOR	: writemath( co, 0, XOR ); break;
				case A_MOV	: writemov( co ); break;
			}
		}
	}

	update_labels();

	map_free( labels );
	vector_free( inserts );

	*_bin = bin;
	return position;
}
#undef MIN_SIZE
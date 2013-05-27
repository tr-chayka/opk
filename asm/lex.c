#include "lex.h"

#include <string.h>
#include <stdlib.h>
#include <ctype.h>

static int iswordchar( char c )
{
	return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_' || c == '[' || c == ']' || c == '#';
}

int empty( char *str )
{
	return (str == NULL) || (str[0] == '\0');
}

int get_value( char c )
{
	if( c >= '0' && c <= '9' )
		return c - '0';
		
	if( c >= 'a' && c <= 'f' )
		return 10 + c - 'a';
		
	if( c >= 'A' && c <= 'F' )
		return 10 + c - 'A';
		
	return -1;
}

int get_int( char *str, unsigned *result )
{
	unsigned res = 0, base = 0;
	
	if( str[0] == '#' )
	{
		base = 16;
		str++;
	}
	else
		base = 10;

	while( str[0] != '\0' )
	{
		int digit;

		if( base == 10 && !isdigit(str[0]) )
			return 0;
		
		digit = get_value( str[0] );
		
		if( digit >= 0)
			res = (res * base) + digit;
		else 
			return 0;
		
		str++;
	}
	
	*result = res;
	return 1;
}

static char buf[256];
static unsigned pos, bufpos;

static void skip_whitespace( char *line )
{
	while( isspace(line[pos]) )
		pos++;
}

static void get_word( char *line )
{
	skip_whitespace( line );

	bufpos = 0;
	while( iswordchar(line[pos]) && bufpos < 255 )
		buf[bufpos++] = toupper(line[pos++]);

	buf[bufpos] = '\0';
}

cmd_t parse_line( char *line )
{
	cmd_t result;

	pos = 0;
	bufpos = 0;

	result.label = NULL;
	result.command = NULL;
	result.param1 = NULL;
	result.param2 = NULL;

	get_word(line);
	skip_whitespace(line);

	if( line[pos] == ':' )
	{
		pos++;
		result.label = strdup(buf);

		get_word( line );
		result.command = strdup(buf);
	}
	else
		result.command = strdup(buf);

	get_word(line);
	result.param1 = strdup(buf);

	skip_whitespace(line);

	if( line[pos] == ',' )
	{
		pos++;

		get_word(line);
		result.param2 = strdup(buf);
	}

	skip_whitespace( line );

	if( line[pos] != '\0' )
		result.is_error = pos;
	else
		result.is_error = 0;

	return result;
}

int get_register( char *str )
{
	if( str == NULL || strlen(str) < 2 )
		return -1;
	if( str[0] == 'R' && (str[1] > '0' && str[1] < '9') && str[2] == '\0' )
		return str[1] - '0';
	else
		return -1;
}

int is_label( char *str )
{
    unsigned i = 0;

	if( empty(str) )
		return 0;

	while( str[i] != '\0' )
	{
		if( !iswordchar(str[i]) )
			return 0;

		++i;
	}

    return 1;
}

int get_address( char *str, unsigned *addr )
{
	unsigned x = 0, len = 0;

	if( empty(str) )
		return 0;

	len = strlen( str );

	if( str[0] == '[' && str[len - 1] == ']' )
	{
		*addr = 0;
		str[len - 1] = '\0';
		
		return get_int( str + 1, addr );
	}
	else
		return 0;
}

int get_reg_address( char *str, unsigned *addr )
{
	unsigned x = 0, len = 0;

	if( empty(str) )
		return 0;

	len = strlen( str );

	if( str[0] == '[' && str[len - 1] == ']' )
	{
		int reg = 0;

		str[len - 1] = '\0';

		reg = get_register( str + 1 );
		
		if( reg > 0 )
		{
			*addr = reg;
			return 1;
		}
	}
	else
		return 0;
}


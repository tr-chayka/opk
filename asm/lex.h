#pragma once

struct _cmd_t
{
	char *label;
	char *command;

	char *param1;
	char *param2;

	unsigned is_error;
};

typedef struct _cmd_t cmd_t;

cmd_t parse_line( char *line );

int get_int( char *str, unsigned *result );
int empty( char *str );
int get_address( char *str, unsigned *addr );
int get_reg_address( char *str, unsigned *addr );
int get_register( char *str );
int is_label( char *str );



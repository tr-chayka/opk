#pragma once

struct _label
{
	unsigned pos;
	char *name;
};

typedef struct _label label_t;

label_t label_create( unsigned pos, char *name );

#define value_type label_t

struct _vector
{
	value_type *data;
    unsigned max_size;
	unsigned size;
};

typedef struct _vector vector;

vector *vector_create();
void vector_free( vector *v );

void vector_push( vector *v, value_type value );
void vector_pop( vector *v );

value_type vector_at( vector *v, unsigned index );


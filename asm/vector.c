#include "vector.h"
#include <stdlib.h>
#include <string.h>

#define MIN_SIZE 10

label_t label_create( unsigned pos, char *name )
{
	label_t res;

	res.pos = pos;
	res.name = strdup(name);

	return res;
}

vector *vector_create()
{
	vector *v = (vector*) malloc( sizeof(vector) );

	v->size = 0;
	v->max_size = MIN_SIZE;
	v->data = (value_type*) malloc( sizeof(value_type) * v->max_size );

	return v;
}

void vector_free( vector *v )
{
	free( v->data );
	free( v );
}

void vector_push( vector *v, value_type value )
{
	if( v->size >= v->max_size )
	{
		v->max_size += MIN_SIZE;
		v->data = (value_type*) realloc( v->data, sizeof(value_type) * v->max_size );
	}

	v->data[v->size] = value;
	v->size++;
}

void vector_pop( vector *v )
{
	v->size--;
}

value_type vector_at( vector *v, unsigned index )
{
	return v->data[index];
}

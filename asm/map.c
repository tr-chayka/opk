#include "map.h"
#include <stdlib.h>

typedef unsigned long long i64;

i64 get_hash( const char* str )
{
	i64 hash = 0;
	size_t i = 0;

	while( str[i] != '\0' )
	{
		hash += str[i];
		hash += (hash << 10);
        hash ^= (hash >> 6);
		i++;
	}

	hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

	return hash;
}

map *map_create()
{
	size_t i;
	map *m = (map*)malloc( sizeof(map) );

	for( i = 0; i < 10; i++ )
		m->ch[i] = NULL;

	m->value = value_none;

	return m;
}

void map_free( map *m )
{
	size_t i;
	if( m == NULL )
		return;

	for( i = 0; i < 10; i++ )
		if( m->ch[i] != NULL )
			map_free( m->ch[i] );

	free( m );
}

void map_set( map *m, const char* key, value_type value )
{
	i64 hash = get_hash(key);

	while ( hash > 0 )
	{
		i64 t = hash % 10;

		if( m->ch[t] == NULL )
			m->ch[t] = map_create();

		m = m->ch[t];

		hash /= 10;
	}

	m->value = value;
}

value_type map_get( map *m, const char* key )
{
	i64 hash = get_hash(key);

	while( hash > 0 )
	{
		i64 t = hash % 10;

		if( m->ch[t] == NULL )
			return value_none;
		else
			m = m->ch[t];

		hash /= 10;
	}

	return m->value;
}

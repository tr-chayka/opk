#pragma once

#define value_type unsigned
#define value_none 0

struct _map
{
	value_type value;
	struct _map *ch[10];
};

typedef struct _map map;

map *map_create();
void map_free( map *m );

void map_set( map *m, const char* key, value_type value );
value_type map_get( map *m, const char* key );

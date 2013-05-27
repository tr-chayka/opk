#pragma once

#include "lex.h"
#include "map.h"

#include <stdio.h>

unsigned compile( FILE *in, map *commands, unsigned char **_bin );
int is_error();

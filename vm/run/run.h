#pragma once
#include <stdlib.h>

typedef unsigned char byte;
typedef unsigned short word;

int vm_init();
int vm_run( byte *code, size_t code_size );
void vm_free();

void vm_print_state();
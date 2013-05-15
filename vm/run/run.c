#include "run.h"
#include "cmd.h"

#include <stdio.h>

signed char F;

word IP, SP, R[8];
byte *memory;

#define MEMORY_SIZE 64*1024
#define STACK_SIZE 1024

int vm_init()
{
	memory = (byte*)malloc( sizeof(byte) * MEMORY_SIZE );

	if( memory == NULL )
		return -1;
	else
		return 0;
}

byte H( word w )
{
	return w >> 8;
}

byte L( word w )
{
	return w & 0xFF;
}

void vm_free()
{
	free( memory );
}

word get_word( byte *buf, word pos )
{
	word H = buf[pos];
	word L = buf[pos + 1];

	return (H << 8) + L;
}

int vm_run( byte *code, size_t code_size )
{
	word i;
	for( i = 0; i < code_size; i++  )
		memory[STACK_SIZE + i] = code[i];

	SP = -1;
	F = 0;
	IP = STACK_SIZE;

	while( 1 )
		switch( memory[IP] )
		{
			case HALT: 
				return 0;

			case CALL:
				{
					char i;
					for( i = 0; i < 8; i++ )
					{
						memory[++SP] = H( R[i] );
						memory[++SP] = L( R[i] );
					}

					memory[++SP] = IP + 3;
					memory[++SP] = F;

					IP = get_word( memory, IP + 1 );
					break;
				}

			case MOV:
				{
					char a1 = memory[IP + 1] >> 4;
					char a2 = memory[IP + 1] & 0xF;

					memory[ R[a1] ] = R[a2];

					IP += 2; break;
				}

			case MOVRR:
				{
					char a1 = memory[IP + 1] >> 4;
					char a2 = memory[IP + 1] & 0xF;

					R[a1] = R[a2];

					IP += 2; break;
				}

			case RET:
				{
					char i;
					
					F = memory[SP--];
					IP = memory[SP--];

					for( i = 0; i < 8; i++ )
					{
						R[i] = get_word( memory, SP - 1 );
						SP -= 2;
					}
					break;
				}

			case NOP:
				{
					IP++; 
					break;
				}

			case IN:
				{
					byte port_num = memory[IP + 1];

					switch( port_num )
					{
						case STDIN_PORT : 
							R[0] = getchar();
							break;
					}

					IP += 2; break;
				}

			case OUT:
				{
					byte port_num = memory[IP + 1];
				
					switch( port_num )
					{
						case STDOUT_PORT:
							putchar( R[0] );
							break;
					}

					IP += 2; break;
				}

			case JMP:
				{
					IP = get_word( memory, IP + 1 );
					break;
				}

			case CMP:
				{
					char a1 = memory[IP + 1] >> 4;
					char a2 = memory[IP + 1] & 0xF;

					if( R[a1] < R[a2] )
						F = -1;
					if( R[a1] == R[a1] )
						F = 0;
					if( R[a1] > R[a2] )
						F = 1;

					IP += 2;
					break;
				}

			case JE: 
				if( F == 0 )
					IP = get_word( memory, IP + 1 );
				else
					IP += 3;
				break;

			case JNE:
				if( F != 0 )
					IP = get_word( memory, IP + 1 );
				else
					IP += 3;
				break;

			case JL:
				if( F < 0 )
					IP = get_word( memory, IP + 1 );
				else
					IP += 3;
				break;

			case JLE:
				if( F <= 0 )
					IP = get_word( memory, IP + 1 );
				else
					IP += 3;
				break;

			case JG:
				if( F > 0 )
					IP = get_word( memory, IP + 1 );
				else
					IP += 3;
				break;

			case JGE:
				if( F >= 0 )
					IP = get_word( memory, IP + 1 );
				else
					IP += 3;
				break;

			case OR:
				{
					char a1 = memory[IP + 1] >> 4;
					char a2 = memory[IP + 1] & 0xF;

					R[a1] = R[a1] | R[a2];
					
					IP += 2; break;
				}
				

			case AND:
				{
					char a1 = memory[IP + 1] >> 4;
					char a2 = memory[IP + 1] & 0xF;

					R[a1] = R[a1] & R[a2];
					
					IP += 2; break;
				}

			case XOR:
				{
					char a1 = memory[IP + 1] >> 4;
					char a2 = memory[IP + 1] & 0xF;

					R[a1] = R[a1] ^ R[a2];
					
					IP += 2; break;
				}

			case ADD:
				{
					char a1 = memory[IP + 1] >> 4;
					char a2 = memory[IP + 1] & 0xF;

					R[a1] = R[a1] + R[a2];
					
					IP += 2; break;
				}

			case SUB:
				{
					char a1 = memory[IP + 1] >> 4;
					char a2 = memory[IP + 1] & 0xF;

					R[a1] = R[a1] - R[a2];
					
					IP += 2; break;
				}

			case MUL:
				{
					char a1 = memory[IP + 1] >> 4;
					char a2 = memory[IP + 1] & 0xF;

					R[a1] = R[a1] * R[a2];
					
					IP += 2; break;
				}

			case DIV:
				{
					char a1 = memory[IP + 1] >> 4;
					char a2 = memory[IP + 1] & 0xF;

					R[a1] = R[a1] / R[a2];
					
					IP += 2; break;
				}
				
			case PUSHD:
				{
					word d = get_word( memory, IP + 1 );

					SP++;
					memory[SP] = d;

					IP += 3; break;
				}
				
			default:
				{
					byte cmd = memory[IP];
					
					if( cmd >= CMPD1 && cmd <= CMPD8 )
					{
						word x = R[cmd - CMPD1];
						word y = get_word( memory, IP + 1 );

						if( x > y )
							F = 1;
						if( x == y )
							F = 0;
						if( x < y )
							F = -1;

						IP += 3; continue;
					}

					if( cmd >= MOVD1 && cmd <= MOVD8 )
					{
						R[cmd - MOVD1] = get_word( memory, IP + 1 );
						
						IP += 3; continue;
					}

					if( cmd >= NOT1 && cmd <= NOT8 )
					{
						R[cmd - NOT1] = !R[cmd - NOT1];

						IP++; continue;
					}

					if( cmd >= INC1 && cmd <= INC8 )
					{
						R[cmd - INC1]++;

						IP++; continue;
					}

					if( cmd >= DEC1 && cmd <= DEC8 )
					{
						R[cmd - DEC1]--;

						IP++; continue;
					}

					if( cmd >= PUSH1 && cmd <= PUSH8 )
					{
						SP++;
						memory[SP] = R[cmd - PUSH1];
						
						IP++; continue;
					}

					if( cmd >= POP1 && cmd <= POP8 )
					{
						R[cmd - POP1] = memory[SP];
						SP--;

						IP++; continue;
					}

					if( cmd >= MOVTR1 && cmd <= MOVTR8 )
					{
						word a = get_word( memory, IP + 1 );

						R[cmd - MOVTR1] = memory[a];
						IP += 3; break;
					}

					if( cmd >= MOVFR1 && cmd <= MOVFR8 )
					{
						word a = get_word( memory, IP + 1 );
						
						memory[a] = R[cmd - MOVFR1];
						IP += 3; continue;
					}

					if( cmd >= ADDD1 && cmd <= ADDD8 )
					{
						word d = get_word( memory, IP + 1 );

						R[cmd - ADDD1] += d;
						IP += 3; continue;
					}

					if( cmd >= SUBD1 && cmd <= SUBD8 )
					{
						word d = get_word( memory, IP + 1 );

						R[cmd - SUBD1] -= d;
						IP +=3; continue;
					}

					if( cmd >= MULD1 && cmd <= MULD8 )
					{
						word d = get_word( memory, IP + 1 );

						R[cmd - MULD1] *= d;
						IP += 3; continue;
					}

					if( cmd >= DIVD1 && cmd <= DIVD8 )
					{
						word d = get_word( memory, IP + 1 );

						R[cmd - DIVD1] /= d;
						IP += 3; continue;
					}
				}
		}
		return 0;
}

void vm_print_state()
{
	char i;

	for( i = 0; i < 16; i++ )
		printf("R%d = %d\n", i, R[i] );
}

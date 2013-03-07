#include "rational.h"
#include <stdlib.h>

int main()
{
	int a, b;
	
	scanf("%d/%d", &a, &b);
	struct Rational *A = rat_create(a, b);
	
	scanf("%d/%d", &a, &b);
	struct Rational *B = rat_create(a, b);
	
	
	switch( rat_compare(A, B) )
	{
		case 0 : printf("A = B\n"); break;
		case 1 : printf("A > B\n"); break;
		case -1: printf("A < B\n"); break;
	}
	
	printf("A + B = ");
	rat_println( rat_add(A, B), stdout );
	
	printf("A - B = ");
	rat_println( rat_sub(A, B), stdout );
	
	printf("A * B = ");
	rat_println( rat_mul(A, B), stdout );
	
	printf("A / B = ");
	rat_println( rat_div(A, B), stdout );
	
	int p;
	
	p = rand() % 10;
	printf("A ^ %d = ", p);
	rat_println( rat_power(A, p), stdout );
	
	p = rand() % 10;
	printf("B ^ %d = ", p);
	rat_println( rat_power(B, p), stdout );
	
	printf("Rounded B is %d\n", rat_to_i(A));
	printf("Rounded B is %d\n", rat_to_i(B));
	
	printf("A as double is %0.10lg\n", rat_to_d(A));
	printf("B as double is %0.10lg\n", rat_to_d(B));
	
	rat_destroy(A);
	rat_destroy(B);
	
	return 0;
}

#include "rational.h"
#include <math.h>

#define alloc(x) ((x*)malloc(sizeof(x)))
#define simplify(x) {int g = gcb(abs(x->numer), abs(x->denom));x->numer /= g;x->denom /= g;}
#define swap(a,b) {int p = a; a = b; b = p;}

int gcb( int a, int b)
{
	if ( b == 0 )
		return a;
	else
		return gcb(b, a % b);
}

struct Rational *rat_create(int a, int b)
{
	struct Rational *res = alloc(struct Rational);
	res->numer = a;
	res->denom = b;
	return res;
}

void rat_print(struct Rational * a, FILE *fp)
{
	fprintf(fp, "%d/%d", a->numer, a->denom);
}

void rat_println(struct Rational *a, FILE *fp)
{
	fprintf(fp, "%d/%d\n", a->numer, a->denom);
}

struct Rational *rat_add(struct Rational *a, struct Rational *b)
{
	struct Rational *res = alloc(struct Rational);
	res->numer = (a->numer * b->denom) + (b->numer * a->denom);
	res->denom = a->denom * b->denom;
	
	simplify(res);
	return res;
}

struct Rational *rat_sub(struct Rational *a, struct Rational *b)
{
	struct Rational *res = alloc(struct Rational);
	res->numer = (a->numer * b->denom) - (b->numer * a->denom);
	res->denom = a->denom * b->denom;
	
	simplify(res);
	return res;
}

struct Rational *rat_mul(struct Rational *a, struct Rational *b)
{
	struct Rational *res = alloc(struct Rational);
	res->numer = a->numer * b->numer;
	res->denom = a->denom * b->denom;
	
	simplify(res);
	return res;
}

struct Rational *rat_div(struct Rational *a, struct Rational *b)
{
	struct Rational *res = alloc(struct Rational);
	res->numer = a->numer * b->denom;
	res->denom = a->denom * b->numer;
	
	simplify(res);
	return res;
}

int int_pow(int a, int p)
{
	if( p == 0)
		return 1;
	if( p & 1 )
		return int_pow(a, p - 1) * a;
	else
	{
		int b = int_pow(a , p >> 1);
		return b * b;
	}
}

struct Rational *rat_power(struct Rational *r, int power)
{
	struct Rational *res = alloc(struct Rational);
	res->numer = int_pow(r->numer, abs(power) );
	res->denom = int_pow(r->denom, abs(power) );
	
	if( power < 0 )
		swap(res->numer, res->denom);
		
	simplify(res);	
	return res;
}

int rat_compare(struct Rational *a, struct Rational *b)
{
	struct Rational *res = rat_sub(a, b);
	
	if( res->numer == 0 )
		return 0;

	if( res->numer > 0 )
		return 1;
	else
		return -1;
}

double rat_to_d(struct Rational *a)
{
	return (double)a->numer / a->denom;
}

int rat_to_i(struct Rational *a)
{
	double t = (double)a->numer / a->denom;
	int _t = (int)t;
	
	if( fabs(t - _t) > fabs(_t + 1 - t) )
		return _t + 1;
	else
		return _t;
}

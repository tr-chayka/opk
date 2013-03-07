#include <stdio.h>

struct Rational
{
	int numer;
	int denom;
};

struct Rational *rat_add(struct Rational *a, struct Rational *b);
struct Rational *rat_sub(struct Rational *a, struct Rational *b);
struct Rational *rat_mul(struct Rational *a, struct Rational *b);
struct Rational *rat_div(struct Rational *a, struct Rational *b);
struct Rational *rat_power(struct Rational *r, int power);

struct Rational *rat_create(int a, int b);

int rat_compare(struct Rational *a, struct Rational *b);
int rat_to_i(struct Rational *a);
double rat_to_d(struct Rational *a);

void rat_print(struct Rational *a, FILE *fp);
void rat_println(struct Rational *a, FILE *fp);

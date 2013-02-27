#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	srand(time(NULL));
	
	int n = 100000000, count = 0;
	
	for( int i = 0; i < n; i++ )	
	{
		double x = (double)rand() / RAND_MAX;
		double y = (double)rand() / RAND_MAX;
		
		if( rand() & 1 ) x = -x;
		if( rand() & 1 ) y = -y;
		
		if( x*x + y*y <= 1 )
			count++;
	}
		
	printf("%d %d\n", count, n);
	double pi =  4 * (double)count / n;
	
	printf("pi = %0.6g\n", pi);
	
	return 0;
}

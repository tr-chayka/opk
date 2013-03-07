#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

void swap(int *a, int *b)
{
	int p = *a;
	*a = *b;
	*b = p;
}

void _sort(int *arr, int l, int r)
{
	int i = l, j = r, m = arr[l + rand() % (r - l + 1)];
	
	do
	{
		while( arr[i] < m ) i++;
		while( arr[j] > m ) j--;
		
		if( i <= j )
		{
			swap( arr + i, arr + j );
			i++;
			j--;
		}	
	}
	while ( i <= j );
	
	if( i < r )
		_sort(arr, i, r);
	if( j > l )
		_sort(arr, l, j);
}

void intqsort(int *arr, size_t size)
{
	_sort(arr, 0, size - 1);
}

#define to_intp(a) ((int*)a)

int compare( const void *a, const void *b )
{
	return *to_intp(a) - *to_intp(b);
}

#undef to_intp

void test_rand()
{
	int n = rand() % 100000;
	int a[n], b[n];
	
	for( int i = 0; i < n; i++ )
		a[i] = b[i] = rand();
	
	qsort(a, n, sizeof(int), compare);
	intqsort(b, n);
	
	for( int i = 0; i < n; i++ )
		assert( a[i] == b[i] );
}

int main()
{
	srand( time(NULL) );
	
	int test_count = rand() % 100;
	for( int i = 0; i < test_count; i++ )
		test_rand();
		
	int n = 0;
	printf("Enter size of array : ");
	scanf("%d", &n);
	
	int a[n];
	printf("Enter array : ");
	for( int i = 0; i < n; i++ )
		scanf("%d", a + i);
		
	intqsort(a, n);
	
	printf("Sorted array : ");
	for( int i = 0; i < n; i++ )
		printf("%d ", a[i]);
		
	printf("\b\n");
	return 0;
}

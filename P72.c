#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>

#define to_intp(a) ((int*)a)
int compare_int( const void *a, const void * b )
{
	return *to_intp(a) - *to_intp(b);
}
#undef to_intp

#define to_charp(a) ((char*)a)
int compare_char( const void *a, const void *b )
{
	return *to_charp(a) - *to_charp(b);
}
#undef to_charp

void swap( void *a, void *b, int size )
{
	void *p = malloc(size);
	memcpy(p, a, size);
	memcpy(a, b, size);
	memcpy(b, p, size);
	free(p);
}

void _sort( const void *arr, int l, int r, int size, int (*compare)(const void *, const void *) )
{
	int i = l, j = r, m = l + rand() % (r - l + 1);
	
	void *mid = malloc(size);
	memcpy(mid, arr + m * size, size);
	
	do
	{
		while( compare(arr + i * size, mid) < 0 ) i++;
		while( compare(arr + j * size, mid) > 0 ) j--;
			
		if( i <= j )
		{
			if( i < j )
				swap( arr + i * size, arr + j * size, size );
			i++;
			j--;
		}
	}
	while( i <= j );
	
	if( i < r )
		_sort(arr, i, r, size, compare);
	if( j > l )
		_sort(arr, l, j, size, compare);
}

void _qsort( const void *base, size_t count, size_t size, int (*compare)(const void *, const void *) )
{
	if( count != 0 )
		_sort(base, 0, count - 1, size, compare);
}

void test_rand()
{
	int n = rand() % 1000;
	int a[n], b[n];
	
	for( int i = 0; i < n; i++ )
		a[i] = b[i] = rand();
	
	qsort(a, n, sizeof(int), compare_int);
	_qsort(b, n, sizeof(int), compare_int);
	
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
		
	_qsort(a, n, sizeof(int), compare_int);
	
	printf("Sorted array : ");
	for( int i = 0; i < n; i++ )
		printf("%d ", a[i]);
		
	printf("\b\n");
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>

int min( int a, int b )
{
	return a < b ? a : b;
}

#define arr_at(x) (arr + (x) * size)
#define temp_at(x) (temp + (x) * size)
void _sort( void *arr, int l, int r, int size, int (*compare)(const void *, const void *), void *temp )
{
	if( l == r ) return;
	
	int m = (l + r) / 2;
	_sort(arr, l, m, size, compare, temp);
	_sort(arr, m + 1, r, size, compare, temp);
	
	int x = 0, y = 0;
	int l_size = (m - l + 1), r_size = (r - m);
	
	for( int i = 0; i < (r - l + 1); i++ )
		if( x < l_size && y < r_size )
		{
			if( compare(arr_at(l + x), arr_at(m + y + 1)) < 0 )
			{
				memcpy( temp_at(i), arr_at(l + x), size );
				x++;
			}
			else
			{
				memcpy( temp_at(i), arr_at(m + y + 1), size );
				y++;
			}
		}
		else
		{
			if ( x < l_size )
			{
				memcpy( temp_at(i), arr_at(l + x), size );
				x++;
			}
			else if( y < r_size )
			{
				memcpy( temp_at(i), arr_at(m + y + 1), size );
				y++;
			}
		}
	
	for( int i = 0; i < r - l + 1; i++ )
		memcpy(arr_at(l + i), temp_at(i), size);
}
#undef arr_at
#undef temp_at


void mergesort( void *base, size_t count, size_t size, int (*compare)(const void *, const void *) )
{
	void *temp = malloc(count * size);
	_sort(base, 0, count - 1, size, compare, temp);
	free(temp);
}

#define to_intp(x) ((int*)x)
int compare_int( const void *a, const void *b )
{
	return *to_intp(a) - *to_intp(b);
}
#undef to_intp4

#define to_charp(a) ((char*)a)
int compare_char( const void *a, const void *b )
{
	return *to_charp(a) - *to_charp(b);
}
#undef to_charp

void test_rand()
{
	{
		int n = rand() % 100000;
		int a[n], b[n];
	
		for( int i = 0; i < n; i++ )
			a[i] = b[i] = rand();
	
		qsort(a, n, sizeof(int), compare_int);
		mergesort(b, n, sizeof(int), compare_int);
	
		for( int i = 0; i < n; i++ )
			assert( a[i] == b[i] );
	}
	
	{
		int n = rand() % 100000;
		char a[n], b[n];
		
		for( int i = 0; i < n; i++ )
			a[i] = b[i] = rand() % CHAR_MAX;
			
		qsort(a, n, sizeof(char), compare_char);
		mergesort(b, n, sizeof(char), compare_char);
		
		for( int i = 0; i < n; i++ )
			assert( a[i] == b[i] );
	}	
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
		
	mergesort(a, n, sizeof(int), compare_int);
	
	printf("Sorted array : ");
	for( int i = 0; i < n; i++ )
		printf("%d ", a[i]);
		
	printf("\b\n");
	return 0;
}

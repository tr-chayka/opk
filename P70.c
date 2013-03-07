#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define to_intp(x) ((int*)x)

int compare( const void *a, const void *b )
{
	return *to_intp(a) - *to_intp(b);
}

void *_bsearch(const void *key, const void *base, size_t count, size_t size, int (*compare)(const void *, const void *))
{
	int l = 0, r = count - 1;
	
	while( l < r )
	{
		int m = l + (r - l) / 2;
		
		if( compare(base + m * size, key) < 0 )
			l = m + 1;
		else
			r = m;
	}
	
	if( l == r && l < count && compare(base + l * size, key) == 0 ) 
		return base + l * size;
	else
		return NULL;
}

int main()
{
	#define size(a) (sizeof(a) / sizeof(a[0]))
	
	srand( time(NULL) );
	
	{
		int arr[] = {0, 1};
		int t = 2;
		assert( _bsearch(&t, arr, size(arr), sizeof(int), compare) == NULL );
	}
	
	{
		int arr[] = {};
		int t = 1;
		assert( _bsearch(&t, arr, size(arr), sizeof(int), compare) == NULL );
	}
	
	{
		int arr[] = {0};
		int t = 0;
		assert( (int*)_bsearch(&t, arr, size(arr), sizeof(int), compare) == arr );
	}
	
	#undef size(a)
	
	{
		int test_count = rand() % 1000;
	
		for( int k = 0; k < test_count; k++ )
		{
			int n = rand() % 10000;
			int arr[n];
		
			for( int i = 0; i < n; i++ )
				arr[i] = rand();
		
			int t = 0;
			if( rand() & 1 )
				t = arr[rand() % n];
			else
				t = rand();
			
			qsort(arr, n, sizeof(int), compare);
		
			int *r1 = (int*)_bsearch(&t, arr, n, sizeof(n), compare);
			int *r2 = (int*)bsearch(&t, arr, n, sizeof(n), compare);
		
			if( r1 == NULL )
				assert( r2 == NULL );
			else
				assert( *r1 == t );
		}
	}
	
	int n, t;
	scanf("%d", &n);
		
	int *a = (int*)malloc(n * sizeof(int));
	for( int i = 0; i < n; i++ )
		scanf("%d", &a[i]);
			
	scanf("%d", &t);
		
	int *res = (int*)_bsearch(&t, a, n, sizeof(int), compare);
		
	if( *res == NULL )
		printf("There is no element in the array\n");
	else
		printf("Element is found in the position %d", res - a);
	
	return 0;
}

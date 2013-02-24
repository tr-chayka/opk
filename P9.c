#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#define min(a, b) ((a < b) ? a : b)
#define size(a) (sizeof(a) / sizeof(a[0]))

char* str_find_z(char *string, char *temp)
{
	int slen = strlen(string), tlen = strlen(temp), len = tlen + slen + 1, r = 0, l = 0, i;
	
	int  *z = (int*)malloc(sizeof(int) * len);
	char *s = (char*)malloc(sizeof(char) *  (len + 1));
	
	if( strlen(temp) == 0 )
		return string;
	
	sprintf(s, "%s\n%s", temp, string);
	memset(z, 0, sizeof(int) * len);
	
	for( i = 1; i < len; i++ )
	{
		if( i <= r )
			z[i] = min(z[i - l], r - i + 1);
		
		while( i + z[i] < len && s[z[i]] == s[z[i] + i] )
			z[i]++;
		
		if( i + z[i] - 1 > r )
		{
			l = i;
			r = z[i] + i - 1;
		}
		
		if( z[i] == tlen )
			return string + i - tlen - 1;
	}
		
	return NULL;
}

char* str_find_h( char *string, char *temp)
{
	unsigned long long hash = 0;
	unsigned long long *w, *h;
	int slen = strlen(string), tlen = strlen(temp), i;
	
	if( tlen == 0 )
		return string;

	if( tlen > slen )
		return NULL;

	w = (unsigned long long*)malloc(sizeof(unsigned long long) * slen);
	h = (unsigned long long*)malloc(sizeof(unsigned long long) * slen);
	
	w[0] = 1;
	for( i = 1; i < slen; i++ )
		w[i] = w[i-1] * 257;
		
	for( i = 0; i < tlen; i++ )
		hash += temp[i] * w[i];
		
	h[0] = w[0] * string[0];
	for( i = 1; i < slen; i++ )
	{
		h[i] = h[i-1] + w[i] * string[i];
	}
		
	if( hash == h[tlen - 1] )
		return string;
	
	for( i = tlen; i < slen; i++ )
		if( hash * w[i - tlen + 1] == h[i] - h[i - tlen] )
			return string + i - tlen + 1;
		
	return NULL;
}


int main()
{	
	char str[1000], temp[1000];
	char *result1, *result2, *result3;
	
	{
		char *str = "", *temp = "";
		assert( strstr(str, temp) == str_find_z(str, temp) && strstr(str, temp) == str_find_h(str, temp));
	}
	
	{
		char *str = "", *temp = "A";
		assert( strstr(str, temp) == str_find_z(str, temp) && strstr(str, temp) == str_find_h(str, temp) );
	}
	
	{
		char *str = "A", *temp = "";
		assert( strstr(str, temp) == str_find_z(str, temp) && strstr(str, temp) == str_find_h(str, temp) );
	}


	{
		const char s[] = ".,;:'/?><~!@#$%^&*()_+[]\\|\"";
		char chars[62], len = 0, c;
		int j, count;

		for( c = 'a'; c <= 'z'; c++ )
			chars[len++] = c;

		for( c = 'A'; c <= 'Z'; c++ )
			chars[len++] = c;
		
		for( c = '0'; c <= '9'; c++ )
			chars[len++] = c;

		for( c = 0; c < size(s); c++ )
			chars[len++] = s[c];
	
		srand(time(NULL));
		count = rand() % 100;
		
		for( j = 0; j < count; j++ )
		{
			char *str, *temp;
			int slen, tlen, i;

			slen = rand() % 10000;
			str = (char*)malloc((slen + 1) * sizeof(char));

			str[slen] = '\0';
			for( i = 0; i < slen; i++ )
				str[i] = chars[rand() % size(chars)];

			if( rand() & 1 )
			{
				int pos = rand() % slen;
				tlen = rand() % (slen - pos + 1);

				temp = (char*)malloc((tlen + 1) * sizeof(char));
				
				temp[tlen] = '\0';
				for( i = 0; i < tlen; i++ )
					temp[i] = str[pos + i];
			}
			else
			{
				tlen = rand() % 10000;
				temp = (char*)malloc((tlen + 1) * sizeof(char));

				temp[tlen] = '\0';
				for( i = 0; i < tlen; i++ )
					temp[i] = chars[rand() % size(chars)];
			}

			assert( strstr(str, temp) == str_find_z(str, temp) && strstr(str, temp) == str_find_h(str, temp) );
		
			free(str);
			free(temp);
		}
	}
		
	printf("Enter string: ");
	scanf("%999s", str);
	
	printf("Enter template: ");
	scanf("%999s", temp);
	
	result1 = strstr(str, temp);
	result2 = str_find_z(str, temp);
	result3 = str_find_h(str, temp);
	
	if( result1 != result2 || result1 != result3 )
		printf("Error");
	else
	{
		if( result1 == NULL )
			printf("There is no template in the string\n");
		else
			printf("Template position is %d", result1 - str);
	}
	return 0;
}

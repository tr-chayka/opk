#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define size(a) (sizeof((a)) / sizeof((a[0])))

const char roman[] = "IVXLCDM";
const int  num[7] = {1, 5, 10, 50, 100, 500, 1000};
 
int less(char a, char b)
{
	char i, ia, ib;
	for( i = 0; i < size(roman); i++ )
	{
		if( a == roman[i] ) ia = i;
		if( b == roman[i] ) ib = i;
	}
	return ia < ib;
}

int get( char c )
{
	int i;
	for( i = 0; i < size(roman); i++ )
		if( c == roman[i] )
			return num[i];
	return 0;
}
 
int roman_to_decimal(char *number)
{
	int i, result = 0, len = strlen(number);
	char prev = 'M';
	
	if( strcmp(number, "") == 0 )
		return 0;
	
	for( i = 0; i < len; i++ )
	{
		if( less(prev, number[i]) )
			result = result - get(prev) * 2 + get(number[i]);
		else
			result += get(number[i]);
	
		prev = number[i];
	}
	return result;
}

const char* roman_ex[] = {"I", "IV", "V", "IX", "X", "XL", "L", "XC", "C", "CD", "D", "CM", "M"};
const int number_ex[13] = { 1, 4, 5, 9, 10, 40, 50, 90, 100, 400, 500, 900, 1000}; 
 
int decimal_to_roman(int number, char *string, int maxlen)
{
	int i, pos = -1;

	for( i = size(roman_ex) - 1; i >= 0; i-- )
		while( number - number_ex[i] >= 0 )
		{	
			int j, len = 1 + (i & 1);
 			
			for( j = 0; j < len; j++ )
			{
				pos++;
				if( pos == maxlen - 1 )
				{
					string[pos] = '\0';
					return 1;
				}
				string[pos] = roman_ex[i][j];
			}
			
			number -= number_ex[i];
		}

	string[pos + 1] = '\0';
	return 0;
}

int main()
{
	{
		const char *e[] = {"XXXI", "DLXXXIII", "DCCCLXXXVIII", "MDCLXVIII", "MCMLXXXIX", "MMXII", "MMMCMXCIX", "MMDLXII", "DXLI", "MMCMLXXXIV"};
		const int ans[] = {31, 583, 888, 1668, 1989, 2012, 3999, 2562, 541, 2984};
		
		int i;
		for( i = 0; i < size(e); i++ )
			assert(roman_to_decimal(e[i]) == ans[i]);		
	}
	
	{
		const char *ans[] = {"XXXI", "DLXXXIII", "DCCCLXXXVIII", "MDCLXVIII", "MCMLXXXIX", "MMXII", "MMMCMXCIX", "MMDLXII", "DXLI", "MMCMLXXXIV"};
		const int e[] = {31, 583, 888, 1668, 1989, 2012, 3999, 2562, 541, 2984};
		
		int i;
		for( i = 0; i < size(e); i++ )
		{
			char result[100];
			int res = decimal_to_roman(e[i], result, 100);
			assert(strcmp(result, ans[i]) == 0 && res == 0);
		}
	}
	
	{
		srand(time(0));
		int length = rand() % 1000, i;
		
		for( i = 0; i < length; i++ )
		{
			char result[100] = "";
			int number = rand() % 4000;
			
			if( decimal_to_roman(number, result, 100) == 0 )
				assert(roman_to_decimal(result) == number);
		}
	}
	 
	char mode;
	char *str = (char*)malloc(100 * sizeof(char));
	
	printf("Select mode (R - from roman to decimal, D - from decimal to roman): ");
	scanf("%c", &mode);
	printf("Enter a number: ");
	
	if( mode == 'R' )
	{
		scanf("%99s", str);
		printf("\n%s -> %d", str, roman_to_decimal(str));
	}
	else
	{
		int x, res;
		scanf("%d", &x);
		
		res = decimal_to_roman(x, str, 100);
		if( res )
			printf("\nout of range\n");
		
		printf("\n%d -> %s\n", x, str);
	}
	
	return 0;
}

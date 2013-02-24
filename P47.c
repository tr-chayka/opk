#include <stdio.h>
#include <string.h>

char transform( char c, int n, char *password, int len )
{
	return c ^ password[n % len];
}

int crypt(char *inf, char *outf, char *password)
{
	int n = 0, len = strlen(password);
	char c = 0;
	
	FILE *in_file = fopen(inf, "rb"); 
	FILE *out_file = fopen(outf, "wb");

	if( !(in_file && out_file) )
		return 0;

	while( c != EOF )
	{
		c = fgetc(in_file);
		if( c != EOF )
			fputc(transform(c, n++, password, len), out_file);
	}
	
	fclose(in_file);
	fclose(out_file);
	
	return 1;
}

int main(int argc, char *argv[])
{
	int result = 0;
	
	if( argv == 4 )
	{
		result = crypt(argv[1], argv[2], argv[3]);
	}
	else
	{
		char in_file[100], out_file[100], password[100];
	
		printf("Enter input file name: ");
		scanf("%99s", in_file);
		printf("Enter output file name: ");
		scanf("%99s", out_file);
		printf("Enter password: ");
		scanf("%99s", password);
		
		result = crypt(in_file, out_file, password);
	}
	
	if( result )
		printf("OK");
	else
		printf("Error");	
	
	return 0;
	
}

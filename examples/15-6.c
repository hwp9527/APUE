#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>

int main(void)
{
	int c;

	while((c = getchar()) != EOF) {
		if(isupper(c))
			c = tolower(c);
		if(putchar(c) == EOF)
			err_sys("output error");
		if(c == '\n')
			fflush(stdout);
	}
	exit(0);
}

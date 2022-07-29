#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sm3.h"
#include<time.h>

#define MAXBUF 4096 
#define SM3_SIZE 32

static char buf[MAXBUF];

int main() {
	unsigned char* a = "abc";
	unsigned char b[32] ;
	int start, end;
	start = time(NULL);
	for (int i = 0; i < 10000000; i++)
	{
	sm3(a, 3, b);
	}
	end = time(NULL);
	printf("%d\n",end-start);
	for (int i = 0; i < 32; i++)
	{
		printf("%X", b[i]);
	}
}

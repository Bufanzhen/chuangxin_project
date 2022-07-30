#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sm3.h"
#include<time.h>
#include<random>
#define MAXBUF 4096 
#define SM3_SIZE 32

#define withoutthread
static char buf[MAXBUF];
#ifdef thread

void MultiThreadOfSM3(unsigned char* a1, unsigned char* a2, unsigned char* a3, unsigned char* b1, unsigned char* b2, unsigned char* b3 )
{
	thread Th[3];
	int tmp = 0;
	Th[0] = thread(sm3, tmp, a1,3,b1);
	Th[1] = thread(sm3, tmp+1, a2, 3, b2);
	Th[2] = thread(sm3, tmp+2, a3, 3, b3);
	for (int k = 0; k < 3; k++) {
		Th[k].join();
	}
}
#endif
#define  TEST

#ifdef TEST
int main() {

#ifdef withoutthread
	unsigned char* a1 = "abc";
	unsigned char b1[32] ;
	int start, end;
	puts("运行10**7次需要时间：（s）");
	start = time(NULL);
	for (int i = 0; i < 10000000; i++)
	{
	sm3(a1, 3, b1);
	}
	end = time(NULL);
	printf("%d\n",end-start);
	for (int i = 0; i < 32; i++)
	{
		printf("%X", b1[i]);
	}
#endif
#ifdef thread
	unsigned char* a1 = "abc";
	unsigned char* a2 = "efg";
	unsigned char* a3 = "hij";
	unsigned char b1[32];
	unsigned char b2[32];
	unsigned char b3[32];
	MultiThreadOfSM3(a1, a2, a3, b1, b2, b3);
#endif
}

#endif
#ifdef ATTACK
int main()
{
	unsigned char a[10];
	for (int i = 0; i < 9; i++)
	{
		a[i] = 'a' + rand() % 26;
	}
	a[9] = '\0';
	/*第一组，步长为1*/
	unsigned char buffer1[32];
	unsigned char buffer2[32];
	/*第2组，步长为2*/
	unsigned char buffer3[32];
	unsigned char buffer4[32];
	sm3(a, 1, buffer1);
	sm3(a, 1, buffer2);
	sm3(buffer1, 64, buffer3);
	sm3(buffer1, 64, buffer4);
	//for (int j = 0; j < 32; j++)
	//{
	//	printf("%x", buffer1[j]);
	//}
	//for (int j = 0; j < 32; j++)
	//{
	//	printf("%x", buffer3[j]);
	//}
	int lengthOfAttack = 4;
	int flag = 0;//找到碰撞的时候置为1
	while (1)
	{
		printf(".");
		sm3(buffer1, 64, buffer2);
		sm3(buffer3, 64, buffer4);
		sm3(buffer4, 64, buffer4);
		for (int i = 0; i < lengthOfAttack; i++)
		{
			if (buffer2[i] != buffer4[i]) {
				break;
			}
			if (buffer2[i] == buffer4[i] && i == (lengthOfAttack - 1))
			{
				puts("find a pair of collision!");
				printf("源象分别是：\n");
				for (int j = 0; j < 32; j++)
				{
					printf("%02x",buffer1[j]);
				}
				printf("\n");
				for (int j = 0; j < 32; j++)
				{
					printf("%02x", buffer3[j]);
				}
				printf("\n对应的hash分别是：\n");
				for (int j = 0; j < 32; j++)
				{
					printf("%02x", buffer2[j]);
				}
				printf("\n");
				for (int j = 0; j < 32; j++)
				{
					printf("%02x", buffer4[j]);
				}
				flag = 1;
				break;
			}
		}
		if (flag == 1)
		{
			break;
		}

		sm3(buffer2, 64, buffer1);
		sm3(buffer4, 64, buffer3);
		sm3(buffer3, 64, buffer3);
		for (int i = 0; i < lengthOfAttack; i++)
		{
			if (buffer1[i] != buffer3[i]) {
				break;
			}
			if (buffer1[i] == buffer3[i] && i == (lengthOfAttack - 1))
			{
				puts("find a pair of collision!");
				printf("源象分别是：\n");
				for (int j = 0; j < 32; j++)
				{
					printf("%02x", buffer2[j]);
				}
				printf("\n");
				for (int j = 0; j < 32; j++)
				{
					printf("%02x", buffer4[j]);
				}
				printf("对应的hash分别是：\n");
				for (int j = 0; j < 32; j++)
				{
					printf("%02x", buffer1[j]);
				}
				printf("\n");
				for (int j = 0; j < 32; j++)
				{
					printf("%02x", buffer3[j]);
				}
				flag = 1;
				break;
			}
		}
		if (flag == 1)
		{
			break;
		}
	}
}

#endif

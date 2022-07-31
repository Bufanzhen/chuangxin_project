#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sm3.h"
#include<time.h>
#include<random>
#include<string>
#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;

struct TreeNode
{
	int No;//编号
	int IsLeafNode;//是否是叶子节点
	unsigned char hash[32];//左右孩子，或者如果是叶子节点，数据的hash值
	TreeNode* left;
	TreeNode* right;
	TreeNode* parent;//父节点
};

TreeNode* CreateATree()
{
	vector<string> listOfData;
	while (1)
	{
		string data ;
		cin >> data;
		if (data == "$break")
		{
			break;
		}
		listOfData.push_back(data);
	}
	/*--------接收数据流---------*/
	int numberOfData = 0;
	vector<TreeNode*> NewTree;
	for (auto DataString : listOfData)
	{
		unsigned char* Data = (unsigned char*)DataString.c_str();
		TreeNode* node1 = new TreeNode;
		sm3(Data, strlen((char*)Data), node1->hash);
		node1->left = NULL;
		node1->right = NULL;
		node1->IsLeafNode = 1;
		node1->No = numberOfData++;
		NewTree.push_back(node1);
	}

	while (numberOfData != 1)
	{
		for (int i = 0; i < (int)(numberOfData / 2); i++)
		{

			TreeNode* node1 = new TreeNode;
			TreeNode* node2 = new TreeNode;
			node1 = NewTree.front();
			node2 = NewTree.front();
			TreeNode* node3 = new TreeNode;
			node3->left = node1;
			node3->right = node2;
			node1->parent = node3;
			node2->parent = node3;
			node3->IsLeafNode = 0;

			unsigned char hash1ANDhash2[32];
			for (int j = 0; j < 32; j++)
			{
				hash1ANDhash2[i] = (node1->hash[i] + node2->hash[i]);
			}
			sm3(hash1ANDhash2, 64, node3->hash);
			NewTree.erase(NewTree.begin());
			NewTree.erase(NewTree.begin());
			NewTree.push_back(node3);
			reverse(NewTree.begin(), NewTree.end());


			if (i == (int)(numberOfData / 2)-1)
			{
				numberOfData = NewTree.size();
			}
		}
	}

	return NULL;
}

#define MAXBUF 4096 
static char buf[MAXBUF];
#define SM3_SIZE 32

int main()
{
	CreateATree();
}
//
//#define withoutthread
//
//#ifdef thread
//
//void MultiThreadOfSM3(unsigned char* a1, unsigned char* a2, unsigned char* a3, unsigned char* b1, unsigned char* b2, unsigned char* b3)
//{
//	thread Th[3];
//	int tmp = 0;
//	Th[0] = thread(sm3, tmp, a1, 3, b1);
//	Th[1] = thread(sm3, tmp + 1, a2, 3, b2);
//	Th[2] = thread(sm3, tmp + 2, a3, 3, b3);
//	for (int k = 0; k < 3; k++) {
//		Th[k].join();
//	}
//}
//#endif
//
//
//#define  TEST
//
//#ifdef TEST
//int main() {
//
//#ifdef withoutthread
//	unsigned char a1[4] = "abc";
//	unsigned char b1[32];
//	int start, end;
//	puts("运行10**7次需要时间：（s）");
//	start = time(NULL);
//	for (int i = 0; i < 100000; i++)
//	{
//		sm3(a1, 3, b1);
//	}
//	end = time(NULL);
//	printf("%d\n", end - start);
//	for (int i = 0; i < 32; i++)
//	{
//		printf("%X", b1[i]);
//	}
//#endif
//#ifdef thread
//	unsigned char* a1 = "abc";
//	unsigned char* a2 = "efg";
//	unsigned char* a3 = "hij";
//	unsigned char b1[32];
//	unsigned char b2[32];
//	unsigned char b3[32];
//	MultiThreadOfSM3(a1, a2, a3, b1, b2, b3);
//#endif
//
//}
//
//#endif
//#ifdef ATTACK
//int main()
//{
//	unsigned char a[10];
//	for (int i = 0; i < 9; i++)
//	{
//		a[i] = 'a' + rand() % 26;
//	}
//	a[9] = '\0';
//	/*第一组，步长为1*/
//	unsigned char buffer1[32];
//	unsigned char buffer2[32];
//	/*第2组，步长为2*/
//	unsigned char buffer3[32];
//	unsigned char buffer4[32];
//	sm3(a, 1, buffer1);
//	sm3(a, 1, buffer2);
//	sm3(buffer1, 64, buffer3);
//	sm3(buffer1, 64, buffer4);
//	//for (int j = 0; j < 32; j++)
//	//{
//	//	printf("%x", buffer1[j]);
//	//}
//	//for (int j = 0; j < 32; j++)
//	//{
//	//	printf("%x", buffer3[j]);
//	//}
//	int lengthOfAttack = 4;
//	int flag = 0;//找到碰撞的时候置为1
//	while (1)
//	{
//		printf(".");
//		sm3(buffer1, 64, buffer2);
//		sm3(buffer3, 64, buffer4);
//		sm3(buffer4, 64, buffer4);
//		for (int i = 0; i < lengthOfAttack; i++)
//		{
//			if (buffer2[i] != buffer4[i]) {
//				break;
//			}
//			if (buffer2[i] == buffer4[i] && i == (lengthOfAttack - 1))
//			{
//				puts("find a pair of collision!");
//				printf("源象分别是：\n");
//				for (int j = 0; j < 32; j++)
//				{
//					printf("%02x", buffer1[j]);
//				}
//				printf("\n");
//				for (int j = 0; j < 32; j++)
//				{
//					printf("%02x", buffer3[j]);
//				}
//				printf("\n对应的hash分别是：\n");
//				for (int j = 0; j < 32; j++)
//				{
//					printf("%02x", buffer2[j]);
//				}
//				printf("\n");
//				for (int j = 0; j < 32; j++)
//				{
//					printf("%02x", buffer4[j]);
//				}
//				flag = 1;
//				break;
//			}
//		}
//		if (flag == 1)
//		{
//			break;
//		}
//
//		sm3(buffer2, 64, buffer1);
//		sm3(buffer4, 64, buffer3);
//		sm3(buffer3, 64, buffer3);
//		for (int i = 0; i < lengthOfAttack; i++)
//		{
//			if (buffer1[i] != buffer3[i]) {
//				break;
//			}
//			if (buffer1[i] == buffer3[i] && i == (lengthOfAttack - 1))
//			{
//				puts("find a pair of collision!");
//				printf("源象分别是：\n");
//				for (int j = 0; j < 32; j++)
//				{
//					printf("%02x", buffer2[j]);
//				}
//				printf("\n");
//				for (int j = 0; j < 32; j++)
//				{
//					printf("%02x", buffer4[j]);
//				}
//				printf("对应的hash分别是：\n");
//				for (int j = 0; j < 32; j++)
//				{
//					printf("%02x", buffer1[j]);
//				}
//				printf("\n");
//				for (int j = 0; j < 32; j++)
//				{
//					printf("%02x", buffer3[j]);
//				}
//				flag = 1;
//				break;
//			}
//		}
//		if (flag == 1)
//		{
//			break;
//		}
//	}
//}
//
//#endif

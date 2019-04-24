#ifndef ����ͼ_H_INCLUDED
#define ����ͼ_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#define INF 32767
#define MAX 50

using namespace std;

//�ڽӱ�Ĺ��� 
typedef struct route {
	int tag;
	char infor[30];
	int weight;
	route *next;
}Route;

typedef struct node {
	char name[20];
	int tag;
	char infor[100];
	Route *h;
}Pnode;

typedef struct {
	Pnode *phead[50];
	int node;
}Map;
//�ڽӾ���Ĺ���

typedef struct Mat {
	int edges[50][50];
	int node;
	int route;
} Graph;
//�����ڽӾ���� 

bool FileToNode(Pnode **phead, int m);//��������Ϣ�����֣���ţ����ܣ�·�����ƣ�������ͼ��

void PrintNode(Map *G, int m);//������ʵĽڵ��ţ�����ڵ���Ϣ

void InitialMap(Map *& G);
void CreatMap(Map *& G);
void CreateNextNode(Route *& h, vector<int> buffer);
void MatixToTable(Map * G, int A[MAX][MAX], int node);
//�����ڽӾ����ʾ��ͼ 

int Dijkstra(Graph *G, vector<int> input, vector<int> &output, int apath[]);
void FindPath(Map* G, vector<int> input, vector<int> &output);
//���·���㷨��apath���鴢�����·����ţ�v,m������ֹ�㣬�����������·������ 


#endif // ����ͼ_H_INCLUDED
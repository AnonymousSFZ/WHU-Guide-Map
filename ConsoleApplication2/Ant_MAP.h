#ifndef ANT_MAP_H_INCLUDED
#define ANT_MAP_H_INCLUDED

/*
��������
1����ֵ�ϸߵĵ����ȶȼ���
2���ͼ�ֵ���и��ʽ��룻
3��ѭ��������Σ�������������ȡ�����ֵ
4����ȵ���Զ�ν���
5�����ڽӵ�·�޷�����ʱֹͣ����
*/
#include"GUI_MAP.h"
#include"iostream"
#include "math.h"
#include "time.h"
#define N_IT_COUNT 2000
//����200��
#define SPOT_NUM 24
using namespace std;

typedef struct knot {
	int tag_num;
	int spotvalue;
	//int studyvalue;
}Spot_knot;

typedef struct point {
	Spot_knot phead[SPOT_NUM];
}Point;

void find_Path(Map* map, int StartSpotNum, vector<int> &output);
/*
int weight_study[SPOT_NUM] = {
+5,0,0,+5,+10,
0,+20,+10,+20,+10,
+20,0,+10,+20,0,
0,0,+5,+5,+20,
+20,+10,+10,+10
};
*/
double rand_double(double dbLow, double dbUpper);
class Find
{
public:
	Find(void);
	~Find(void);
public:
	vector<int> m_nPath;//��¼�߹���·��
	int m_dbPathLength;//��¼�߹���·������
	int m_nCurSpotNum;//���ھ���ı��
	int m_nMovedSpotCount;//�Ѿ�ȥ���ľ�����Ŀ
	Map *WHUmap;//����ͼ
	int Start;//������
	Point WHU_point;
	double Path_Weight;
	double worth;
public:
	int degree_Num(Pnode *p);//������Ķ�
	void Init(Map *map, int start);//��ʼ��
	int ChooseNextSpot();//ѡ����һ������
	bool Move();//�ھ�����ƶ�
	void Search(Map *map, int start);//����·��
	void CalPathLength();//�����߹���·������
	void WeightPath();
	double Distance(int n, int m);
};

class CTsp
{
public:
	CTsp(void);
	~CTsp(void);
public:
	Find m_cAry[N_IT_COUNT]; //��������
	Find m_cBest; //�ò�����������ֻ�������������Ž��
	Map *map;
	int Start;
public:
	//��ʼ������
	void InitData(Map *antmap, int start);
	//��ʼ����
	void Search();
};

#endif
#include "Ant_MAP.h"
int weight_spot[SPOT_NUM] = {
+40,0,0,+40,0,
0,+100,0,+10,+50,
+50,+50,+50,0,5,
0,0,+20,+20,0,
0,+50,0,0
};
Find::Find(void)
{
}
Find::~Find(void)
{
}
CTsp::CTsp(void)
{
}
CTsp::~CTsp(void)
{
}

//���ظ�������������ȡ����ĸ�����
double rand_double(double dbLow, double dbUpper)
{
	double dbTemp = rand() / ((double)RAND_MAX + 1.0);
	return dbLow + dbTemp * (dbUpper - dbLow);
}

//���ؽ��Ķ�
int Find::degree_Num(Pnode *p) {
	int num = 0;
	Route* road = NULL;
	road = p->h;
	for (; road->next != NULL; num++) {
		road = road->next;
	}
	return num+1;
}

//��ʼ��
void Find::Init(Map *map, int start) {
	WHUmap = map;
	Start = start;
	m_nPath.clear();
	m_dbPathLength = 0.0;
	m_nCurSpotNum = Start;
	m_nMovedSpotCount = 0;
	Path_Weight = 0.0;
	worth = 0.0;
		for (int num = 1; num <= SPOT_NUM; num++) {

			int tempi = degree_Num(WHUmap->phead[num]);
			if (5 > tempi > 2)
				WHU_point.phead[num - 1].tag_num = tempi - 2;//���ڵ���2�Ķ�ֻ����n-1��
			else
				if (tempi > 4)
					WHU_point.phead[num - 1].tag_num = tempi - 3;
				else
		            WHU_point.phead[num-1].tag_num = 1;

		WHU_point.phead[num-1].spotvalue = weight_spot[num-1];
		//WHU_point.phead[num].studyvalue = weight_study[num];
		}
		WHU_point.phead[Start - 1].tag_num--;
}

int Find::ChooseNextSpot()
{
	int nSelectedSpot = -1; //���ؽ��������ʱ��������Ϊ-1
	//==============================================================================
	//���㵱ǰ������ûȥ���ľ���֮�����Ϣ���ܺ�

	double dbTotal = 0.0;

	typedef struct stru {
		int tag;
		double probility;
	};
	stru c;
	vector<stru> prob;
	prob.clear();

	Route *p = WHUmap->phead[m_nCurSpotNum]->h;

	int i;
	for (; p != NULL; p = p->next) {
		i = p->tag;
		if (WHU_point.phead[i-1].tag_num)
		{
			c.probility = 0;
			c.tag = i;
			c.probility = (WHU_point.phead[i-1].spotvalue + 10)*10/ Distance(m_nCurSpotNum,i );//�ú����ɸ���
			prob.push_back(c);
			dbTotal += c.probility;
		}//ֻ���ڽӲ��ҷ��ʴ���û����Ľ����Է���
		else {
	;
}
	}
	
	//��������ѡ��
	double dbTemp = 0.0;
	dbTemp = rand_double( 0, dbTotal);//ȡһ�������
	if (dbTotal > 0.0)//����Ϣ�ش���0
	{
		
		for (int i = 0; i < prob.size(); i++)
		{
			dbTemp = dbTemp - prob[i].probility;
			if (dbTemp < 0.0)
			{
				nSelectedSpot = prob[i].tag;
				break;
			}
		}
	}
	//�������nSelectedSpot==-1,������·���ߣ���ʱͣ����
	return nSelectedSpot;
}

bool Find::Move()
{
	int nSpotNo = ChooseNextSpot(); //ѡ����һ������
	if (nSpotNo == -1) return false;
		m_nPath.push_back(nSpotNo); //�����ߵ�·��
	WHU_point.phead[nSpotNo-1].spotvalue = 0;
	WHU_point.phead[nSpotNo-1].tag_num--;//���������Ŀɷ��ʴ�����һ
	m_nCurSpotNum = nSpotNo; //�ı䵱ǰ���ھ���Ϊѡ��ľ���
	m_nMovedSpotCount++; //�Ѿ�ȥ���ľ���������1
	return true;
}

void Find::Search(Map *map, int start)
{
	Init(map,start);

	m_nPath.push_back(Start);
	while (1) {
		if (!Move())
			break;
	}
	CalPathLength();
	WeightPath();
	worth = Path_Weight*10 / m_dbPathLength;
}

void Find::CalPathLength()
{
	m_dbPathLength = 0.0; //�Ȱ�·��������0
	int m = 0;
	int n = 0;
	for (int i = 1; i < m_nPath.size(); i++)
	{
		m = m_nPath[i];
		n = m_nPath[i - 1];
		m_dbPathLength = m_dbPathLength + Distance(m, n);
	}
}

void Find::WeightPath()
{
	Path_Weight = 0.0;
	int m = 0;
	for (int i = 0; i < m_nPath.size(); i++)
	{
		m = m_nPath[i];
		Path_Weight += WHU_point.phead[m].spotvalue;
	}
}

//���������ľ���
double Find::Distance(int n, int m)
{
	if (!(WHUmap&&WHUmap->phead[n] && WHUmap->phead[n]->h))
	{
		return -1.0;
	}

	Route *p = WHUmap->phead[n]->h;

	do
	{
		if (p->tag == m )
		{
			return (double)p->weight;
		}
		p = p->next;
	} while (p != NULL);
	return 0;
}

void CTsp::InitData(Map* antmap,int start)
{
	//�Ȱ����ŵ�·����������Ϊ0
	m_cBest.worth = 0.0;
	map = antmap;
	Start = start;
}

void CTsp::Search()
{
	//�ڵ��������ڽ���ѭ��
		//ÿֻ��������һ��
	for (int j = 0; j < N_IT_COUNT; j++)
	{
		m_cAry[j].Search(map,Start);
	}
	//������ѽ��
	for (int j = 0; j < N_IT_COUNT; j++)
	{
		if (m_cAry[j].m_nMovedSpotCount >= 12)
		{
			if (m_cAry[j].worth > m_cBest.worth)
			{
				m_cBest = m_cAry[j];
			}
		}
	}
}

void find_Path(Map* map, int StartSpotNum, vector<int> &output)
{
	//�õ�ǰʱ����ʼ��������ӣ���ֹÿ�����еĽ������ͬ
	time_t tm;
	time(&tm);
	unsigned int nSeed = (unsigned int)tm;
	srand(nSeed);
	//��ʼ����
	CTsp tsp;
	tsp.InitData(map, StartSpotNum); //��ʼ��
	tsp.Search(); //��ʼ����
	//������
	for (int i = 0; i < tsp.m_cBest.m_nPath.size(); i++)
		output.push_back(tsp.m_cBest.m_nPath[i]);
}
#include"GUI_MAP.h"
#include"Ant_MAP.h"

using namespace std;

void mainloop() {
	Map *graph;
	vector<Site> site;
	vector<int> input, output;

	InitialMap(graph);
	CreatMap(graph);
	initSite(site);
	initComponent();
	setcaption("�人��ѧУ԰����");

    for( ; is_run(); delay_fps(60)){
		getSite(input, site);
		showSite(site, graph);
		showSearchPanel();
		//showAllPath();

		/* YOU MAY CHANGE CODE BELOW  */
		// getSite(vector<int> &input, vector<Site> site, int site_cnt)
		// �ú������ڶ�ȡ�û�����Ctrl��Խڵ�ĵ����
		// �ڵ�ı�Ŵ���input��site������Ҫ�Ķ���site_cntΪ��Ҫ��ȡ�ڵ������
		// connectPath(vector<int> output, vector<Site> site)
		// output��Ϊ��Ҫ��������ʾ��·�����ڵ������·����������site������Ҫ�Ķ�
		
		if (!input.empty()) {
			output.clear();
			if (input.size() == 2)// ���·��
				FindPath(graph, input, output);
			else // �Ƽ�·��
				find_Path(graph, input[0], output);
			connectPath(output, graph);
		}
		/* YOU MAY CHANGE CODE ABOVE  */
    }
	delComponent();
}

int main() {
	setinitmode(0);
	initgraph(MAP_LENGTH, MAP_WIDTH);   // ͼ�γ�ʼ�������ڳߴ�
	setrendermode(RENDER_MANUAL);		// ��ͼ����ģʽ����Ϊ�ֶ���������˸
    mainloop();
	return 0;
}

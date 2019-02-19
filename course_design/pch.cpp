#include "pch.h"

vector<int>* graph_initialization(vector<Vex>& vex, vector<int>* graph, 
	const string& vex_file_name, const string& edge_file_name)
{
	//	���������е���֣���Ҫ��Ϊʲô���ʾ��ǵ�ʱû���Ϲд��

	//open the two files of vex & edge
	ifstream inv(vex_file_name);
	ifstream ine(edge_file_name);

	//declare the variable
	int NumOfVex;	//��������
	int index;
	string name;
	string info;
	int vex_a, vex_b;
	int distance;

	//initial the vex & graph
	inv >> NumOfVex;
	graph = new vector<int>[NumOfVex];

	for (int i = 0; i < NumOfVex; ++i)
	{
		graph[i].resize(NumOfVex, INT_MAX);
		//graph[i][i] = 0;
		inv >> index;
		inv >> name;
		inv >> info;
		vex.push_back(Vex(index, name, info));
		//cout << vex[i].index << " : " << vex[i].info << endl;
	}
	while (!ine.eof())
	{
		ine >> vex_a >> vex_b >> distance;
		graph[vex_a][vex_b] = graph[vex_b][vex_a] = distance;
		//cout << vex_a << ' ' << vex_b << ' ' << distance << endl;
	}

	inv.close();
	ine.close();

	return graph;
}

void vex_find(vector<Vex> vex, vector<int>* graph)
{
	cout << "��������Ҫ���Ҿ���ı�ţ�";
	int index;
	cin >> index;
	cout << index << "�ž���������ǣ�" << vex[index].name << endl;
	cout << "������ܣ�" << endl << "	" << vex[index].info << endl;
	cout << "��þ������ڵľ��㼰��֮��ľ������£�" << endl;

	for (int i=0;i<(int)vex.size();++i)
	{
		if (graph[index][i] != INT_MAX)
		{
			cout << vex[i].name << " ���� " << vex[index].name <<" " << graph[index][i]<<" ����λ" << endl;
		}
	}
}

void graph_tour(vector<Vex> vex, vector<int>* graph)
{
	cout << "������Ԥ��������㾰���ţ�";
	int index;
	cin >> index;

	int number = vex.size();
	bool* visited = new bool[number]{0};
	int* path = new int[number];
	int count = 0;
	int nowpath = 1;

	cout << "�ƻ�����·�������¼��֣�" << endl << endl;
	DFS(vex, graph, visited, path, index, count, nowpath);
	
	delete[] visited;
	delete[] path;

}

void DFS(vector<Vex> vex, vector<int>* graph,
	bool* visited, int* path,
	int& nowpoint, int& count,int& nowpath) 
{
	visited[nowpoint] = true;	//����
	path[count++] = nowpoint;	//��¼·��

	if (vex.size() == count)	//special judge
	{
		cout << "�� " << nowpath << " ������·�����£�" <<endl;
		nowpath++;
		int index = 0;
		for (; index < count; ++index)
		{
			cout << vex[path[index]].name;
			if (index != count - 1)
				cout << " -> ";
		}
		cout << endl << endl;
	}
	else
	{
		int k;
		for (k = 0; k < (int)vex.size(); ++k)
		{
			if (visited[k] == false && graph[nowpoint][k] != INT_MAX)
				DFS(vex, graph, visited, path, k, count, nowpath);
		}
	}

	visited[nowpoint] = false;
	count--;
}

void graph_shortest_path(vector<Vex> vex, vector<int>* graph)
{
	int sp, ep;	//	begin & end
	
	cout << "��������Ҫ��ѯ���·������㣺";
	cin >> sp;
	cout << "��������Ҫ��ѯ���·�����յ㣺";
	cin >> ep;

	int NumOfVex = vex.size();
	unsigned int* dis = new unsigned int[NumOfVex];	//	Prevent data overflow
	bool* visit = new bool[NumOfVex];
	vector<int> path_index(NumOfVex,sp);
	int v, tmp;	//	Nodes and distances being maintained

	for (int i = 0; i < NumOfVex; ++i)
	{
		dis[i] = graph[sp][i];
		visit[i] = false;
	}

	dis[sp] = 0;
	visit[sp] = true;

	for (int i = 0; i <NumOfVex ; ++i)
	{
		tmp = INT_MAX;
		for (int j = 0; j < NumOfVex; ++j)
		{
			if (tmp > dis[j] && !visit[j])
			{
				tmp = dis[j];
				v = j;
			}
		}
		
		visit[v] = 1;

		for (int k = 0; k < NumOfVex; ++k)
		{
			if (!visit[k] && dis[k] > dis[v] + graph[v][k])
			{
				dis[k] = dis[v] + graph[v][k];
				path_index[k] = v;
			}
		}
	}

	cout << "�� " << vex[sp].name << " �� " << vex[ep].name << " �����·��Ϊ��" << endl;
	int len = path_index.size();
	int t = ep;
	cout << vex[t].name << " <-> ";
	while (path_index[t] != sp)
	{
		cout << vex[path_index[t]].name << " <-> ";
		t = path_index[t];
	}
	cout << vex[path_index[t]].name << endl;
	cout << "���·������Ϊ��" << dis[ep] << endl;

	delete[] visit;
	delete[] dis;
}

void graph_circuit_planning(vector<Vex> vex, vector<int>* graph)
{
	cout << "������·������ѷ���������£�" << endl << endl;

	//	declare	initialization
	int num = vex.size();
	const int start = 2;
	vector<bool> vis(num, false);
	vector<int> prevex(num, start);	//	record and maintain precursor nodes
	vector<int > short_dis(graph[start].begin(),graph[start].end());	//	//record and maintain the shortest distance of new nodes

	long long sum_distance = 0;
	vis[start] = true;
	cout << "��Ҫ������·���������㼰��������£�" << endl;

	for (int i = 1; i < num; ++i)
	{
		int now_vex = -1;
		int now_dis = INT_MAX;

		for(int j=0;j<num;++j)
			if (!vis[j] && now_dis>short_dis[j])
			{
				now_dis = short_dis[j];
				now_vex = j;
			}

		if (now_vex != -1)
		{
			vis[now_vex] = true;
			sum_distance += short_dis[now_vex];
			cout << prevex[now_vex] << " -- " << now_vex << "   " << short_dis[now_vex] << endl;

			for (int j=0;j<num;++j)
				if (!vis[j] && short_dis[j] > graph[now_vex][j])
				{
					short_dis[j] = graph[now_vex][j];
					prevex[j] = now_vex;
				}
		}
	}

	cout << "��·������ѷ�����·��Ϊ��" << sum_distance << "����λ��" << endl << endl;	
}

void graph_crud(vector<Vex>& vex, vector<int>* graph, const string & vex_file_name, const string & edge_file_name)
{
	while (true)
	{
		cout << "�������¹滮�������£�" << endl
			<< " 0 ������޸ģ��ؽ������滮ͼ" << endl
			<< " 1 �����뾰��" << endl
			<< " 2 ��ɾ������" << endl
			<< " 3 ���޸ľ�����Ϣ�����ı侰�����룩" << endl
			<< " 4 ���޸ľ�������" << endl << endl
			<< "�������Ӧ���ѡ����Ҫ���еĲ�����";

		int ope;
		cin >> ope;
		system("cls");

		if (!ope)
			break;

		switch (ope)
		{
		case 1:
			graph = vex_create(vex, graph);
			break;
		case 2:
			graph = vex_delete(vex, graph);
			break;
		case 3:
			vex_update(vex);
			break;
		case 4:
			graph = edge_update(vex, graph);
			break;
		default:
			cout << "�޴˹��ܣ�����������ָ��";
			break;;
		}

		system("cls");
	}

	cout << "�����ؽ������滮ͼ..." << endl;

	//open the two files of vex & edge
	ofstream inv(vex_file_name);
	ofstream ine(edge_file_name);

	int NumOfVex = vex.size();
	inv << NumOfVex ;

	for (int i = 0; i < NumOfVex; ++i)
	{
		inv << endl << vex[i].index;
		inv << endl << vex[i].name;
		inv << endl << vex[i].info;

		for (int j = i+1; j < NumOfVex; ++j)
		{
			if (graph[i][j] != INT_MAX)
			{
				ine << i << ' ' << j << ' ' << graph[i][j];
				if (!ine.eof())
					ine << endl;
			}
		}
	}

	inv.close();
	ine.close();
	Sleep(1000);
	cout << "�����滮ͼ�ؽ���ɣ�" << endl << endl << endl;

	cout << "������Ϣ��" << endl;
	for (int i = 0; i < NumOfVex; ++i)
		cout << vex[i].index << ' ' << vex[i].name << ' ' << vex[i].info << endl;

	cout << endl << "��·��Ϣ��" << endl;
	for (int i = 0; i < NumOfVex; ++i)
	{
		for (int j = i + 1; j < NumOfVex; ++j)
			if (graph[i][j] != INT_MAX)
				cout << vex[i].name << " ���� " << vex[j].name << ' ' << graph[i][j] << " ����λ" << endl;
	}

}

vector<int>* vex_create(vector<Vex>& vex, vector<int>* graph)
{
	int old_vex_num = vex.size();
	int new_vex_num = old_vex_num + 1;

	cout << "���潫��ӱ��Ϊ" << new_vex_num << "�ľ���" << endl;

	cout << "�����뾰�����ƣ�" << endl;
	string name;
	cin >> name;

	cout << "�����뾰���飺" << endl;
	string info;
	cin >> info;

	vex.push_back(Vex(old_vex_num, name, info));
	vector<int>* new_graph = new vector<int>[new_vex_num];

	for (int i=0;i<new_vex_num;++i)
	{
		new_graph[i].resize(new_vex_num, INT_MAX);
		if (i != new_vex_num-1)
			for(int j=0;j<new_vex_num-1;++j)
				new_graph[i][j] = graph[i][j];
	}

	cout << "��������þ�����ͨ�ľ������(Ӧ����"<<new_vex_num<<"��)��" << endl;
	int edge_num;
	cin >> edge_num;

	cout << "��������þ�����ͨ�ľ������Լ����룺" << endl;
	int index, dis;
	for (int i = 0; i < edge_num; ++i)
	{
		cin >> index >> dis;
		new_graph[index][new_vex_num - 1] = new_graph[new_vex_num - 1][index] = dis;
	}

	return new_graph;
}

vector<int>* vex_delete(vector<Vex>& vex, vector<int>* graph)
{
	int index;
	cout << "��������Ҫɾ���ľ����ţ�" << endl;
	cin >> index;
	
	vex.erase(vex.begin() + index);
	int new_vex_num = vex.size();
	vector<int>* new_graph = new vector<int>[new_vex_num];


	for (int i = 0; i < new_vex_num; ++i)
	{
		vex[i].index = i;

		new_graph[i].resize(new_vex_num, INT_MAX);
		for (int j=0;j<new_vex_num;++j)
		{

			if (j < index && i<index)
				new_graph[i][j] = graph[i][j];
			else if(j >= index && i >= index)
				new_graph[i][j] = graph[i + 1][j + 1];
			else if(i>=index)
				new_graph[i][j] = graph[i+1][j];
			else if(j>=index)
				new_graph[i][j] = graph[i][j+1];
		}
	}

	return new_graph;
}

void vex_update(vector<Vex>& vex)
{
	int index;
	string name;
	string info;

	cout << "��������Ҫ���ĵľ����ţ�" << endl;
	cin >> index;
	cout << "��������ĺ�ľ�������" << endl;
	cin >> name;
	cout << "��������ĺ�ľ�����Ϣ" << endl;
	cin >> info;

	vex[index] = Vex(index, name, info);
}

vector<int>* edge_update(vector<Vex>& vex, vector<int>* graph)
{
	int in_a, in_b, dis;

	cout << "��������Ҫ���ĵĵ�·��ؾ��� �� ��ţ�" << endl;
	cin >> in_a;
	cout << "��������Ҫ���ĵĵ�·��ؾ��� �� ��ţ�" << endl;
	cin >> in_b;
	cout << "��������ĺ�ĵ�·���룺" << endl;
	cin >> dis;

	graph[in_a][in_b] = graph[in_b][in_a] = dis;

	return graph;
}
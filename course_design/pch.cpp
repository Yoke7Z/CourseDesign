#include "pch.h"

vector<int>* graph_initialization(vector<Vex>& vex, vector<int>* graph, 
	const string& vex_file_name, const string& edge_file_name)
{
	//	数据类型有点奇怪，不要问为什么，问就是当时没想好瞎写的

	//open the two files of vex & edge
	ifstream inv(vex_file_name);
	ifstream ine(edge_file_name);

	//declare the variable
	int NumOfVex;	//景点总数
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
	cout << "请输入需要查找景点的编号：";
	int index;
	cin >> index;
	cout << index << "号景点的名称是：" << vex[index].name << endl;
	cout << "景点介绍：" << endl << "	" << vex[index].info << endl;
	cout << "与该景点相邻的景点及其之间的距离如下：" << endl;

	for (int i=0;i<(int)vex.size();++i)
	{
		if (graph[index][i] != INT_MAX)
		{
			cout << vex[i].name << " 距离 " << vex[index].name <<" " << graph[index][i]<<" 个单位" << endl;
		}
	}
}

void graph_tour(vector<Vex> vex, vector<int>* graph)
{
	cout << "请输入预定游览起点景点编号：";
	int index;
	cin >> index;

	int number = vex.size();
	bool* visited = new bool[number]{0};
	int* path = new int[number];
	int count = 0;
	int nowpath = 1;

	cout << "计划游览路线有以下几种：" << endl << endl;
	DFS(vex, graph, visited, path, index, count, nowpath);
	
	delete[] visited;
	delete[] path;

}

void DFS(vector<Vex> vex, vector<int>* graph,
	bool* visited, int* path,
	int& nowpoint, int& count,int& nowpath) 
{
	visited[nowpoint] = true;	//打标记
	path[count++] = nowpoint;	//记录路径

	if (vex.size() == count)	//special judge
	{
		cout << "第 " << nowpath << " 条游览路线如下：" <<endl;
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
	
	cout << "请输入需要查询最短路径的起点：";
	cin >> sp;
	cout << "请输入需要查询最短路径的终点：";
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

	cout << "从 " << vex[sp].name << " 到 " << vex[ep].name << " 的最短路径为：" << endl;
	int len = path_index.size();
	int t = ep;
	cout << vex[t].name << " <-> ";
	while (path_index[t] != sp)
	{
		cout << vex[path_index[t]].name << " <-> ";
		t = path_index[t];
	}
	cout << vex[path_index[t]].name << endl;
	cout << "最短路径长度为：" << dis[ep] << endl;

	delete[] visit;
	delete[] dis;
}

void graph_circuit_planning(vector<Vex> vex, vector<int>* graph)
{
	cout << "景区电路铺设最佳方案设计如下：" << endl << endl;

	//	declare	initialization
	int num = vex.size();
	const int start = 2;
	vector<bool> vis(num, false);
	vector<int> prevex(num, start);	//	record and maintain precursor nodes
	vector<int > short_dis(graph[start].begin(),graph[start].end());	//	//record and maintain the shortest distance of new nodes

	long long sum_distance = 0;
	vis[start] = true;
	cout << "需要铺设线路的两个景点及其距离如下：" << endl;

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

	cout << "电路铺设最佳方案总路程为：" << sum_distance << "个单位。" << endl << endl;	
}

void graph_crud(vector<Vex>& vex, vector<int>* graph, const string & vex_file_name, const string & edge_file_name)
{
	while (true)
	{
		cout << "景区重新规划功能如下：" << endl
			<< " 0 ：完成修改，重建景区规划图" << endl
			<< " 1 ：插入景点" << endl
			<< " 2 ：删除景点" << endl
			<< " 3 ：修改景点信息（不改变景点间距离）" << endl
			<< " 4 ：修改景点间距离" << endl << endl
			<< "请输入对应编号选择需要进行的操作：";

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
			cout << "无此功能，请重新输入指令";
			break;;
		}

		system("cls");
	}

	cout << "正在重建景区规划图..." << endl;

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
	cout << "景区规划图重建完成！" << endl << endl << endl;

	cout << "景点信息：" << endl;
	for (int i = 0; i < NumOfVex; ++i)
		cout << vex[i].index << ' ' << vex[i].name << ' ' << vex[i].info << endl;

	cout << endl << "道路信息：" << endl;
	for (int i = 0; i < NumOfVex; ++i)
	{
		for (int j = i + 1; j < NumOfVex; ++j)
			if (graph[i][j] != INT_MAX)
				cout << vex[i].name << " 距离 " << vex[j].name << ' ' << graph[i][j] << " 个单位" << endl;
	}

}

vector<int>* vex_create(vector<Vex>& vex, vector<int>* graph)
{
	int old_vex_num = vex.size();
	int new_vex_num = old_vex_num + 1;

	cout << "下面将添加编号为" << new_vex_num << "的景点" << endl;

	cout << "请输入景点名称：" << endl;
	string name;
	cin >> name;

	cout << "请输入景点简介：" << endl;
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

	cout << "请输入与该景点连通的景点个数(应少于"<<new_vex_num<<"个)：" << endl;
	int edge_num;
	cin >> edge_num;

	cout << "请输入与该景点连通的景点编号以及距离：" << endl;
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
	cout << "请输入需要删除的景点编号：" << endl;
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

	cout << "请输入需要更改的景点编号：" << endl;
	cin >> index;
	cout << "请输入更改后的景点名称" << endl;
	cin >> name;
	cout << "请输入更改后的景点信息" << endl;
	cin >> info;

	vex[index] = Vex(index, name, info);
}

vector<int>* edge_update(vector<Vex>& vex, vector<int>* graph)
{
	int in_a, in_b, dis;

	cout << "请输入需要更改的道路相关景点 Ⅰ 编号：" << endl;
	cin >> in_a;
	cout << "请输入需要更改的道路相关景点 Ⅱ 编号：" << endl;
	cin >> in_b;
	cout << "请输入更改后的道路距离：" << endl;
	cin >> dis;

	graph[in_a][in_b] = graph[in_b][in_a] = dis;

	return graph;
}
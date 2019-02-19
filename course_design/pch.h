// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件

#ifndef PCH_H
#define PCH_H

// TODO: 添加要在此处预编译的标头
#include "iostream"
#include "fstream"
#include "vector"
#include "string"
#include "algorithm"
#include "windows.h"
#include "cstdlib"
using namespace std;

//class Vex : include all informations of a attraction
class Vex
{
public:
	int index;
	string name;
	string info;
	Vex(int _index, string _name, string _info)
	{
		index = _index;
		name = _name;
		info = _info;
	}
};



//method one : initialize all the attractions and adjacency matrix
vector<int>* graph_initialization(vector<Vex>& vex, vector<int>* graph,
	const string& vex_file_name = "Vex.txt", const string& edge_file_name = "Edge.txt");

//method two : find the designated attraction ,output its information and nearby attractions
void vex_find(vector<Vex> vex, vector<int>* graph);

//method three : according to the given attraction ,output all the no loop tours of all attractions
void graph_tour(vector<Vex> vex, vector<int>* graph);
void DFS(vector<Vex> vex, vector<int>* graph, bool* visited, int* path, int& nowpoint, int& count, int& nowpath);

//method four : find the shortest path between two attractions in the graph
void graph_shortest_path(vector<Vex> vex, vector<int>* graph);

//method five : Minimum spanning tree & Prim algorithm
void graph_circuit_planning(vector<Vex> vex, vector<int>* graph);

//method six : create,update,delete the attractions
void graph_crud(vector<Vex>& vex, vector<int>* graph,
	const string& vex_file_name = "Vex.txt",
	const string& edge_file_name = "Edge.txt");
vector<int>* vex_create(vector<Vex>& vex, vector<int>* graph);
vector<int>* vex_delete(vector<Vex>& vex, vector<int>* graph);
void vex_update(vector<Vex>& vex);
vector<int>* edge_update(vector<Vex>& vex, vector<int>* graph);

#endif //PCH_H
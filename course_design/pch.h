/*
所有中文注释都是写完逻辑之后整理时补充的。
英文注释写于课设过程中，避免编码出现问题我要改好久。
*/

#ifndef PCH_H
#define PCH_H

// TODO: 添加要在此处预编译的标头
#include "iostream"
#include "fstream"
#include "vector"
#include "string"
#include "windows.h"
//#include "cstdlib"
using namespace std;

//class Vex : include all informations of a attraction
class Vex
{
public:
	int index;	//	景点编号
	string name;	//	景点名称
	string info;	//	景点简介
	Vex(int _index, string _name, string _info)
	{
		//	图个方便构建对象
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
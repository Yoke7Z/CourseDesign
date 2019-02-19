// course_design.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>

int main()
{
	vector<Vex> vex;
	vector<int>* graph=nullptr;
	graph = graph_initialization(vex, graph,"Vex.txt","Edge.txt");
	
	if (!graph)
	{
		cout << "gg" << endl;
		Sleep(2000);
		return 0;
	}	
	
	while (true)
	{
		cout << "已成功读入 " << vex.size() << " 个景点(编号0-" << vex.size() - 1 << ")的所有信息" << endl;
		cout << "可执行操作如下:" << endl
			<< " 0 : 结束程序" << endl
			<< " 1 : 查询景点相关信息" << endl
			<< " 2 : 查询最佳游览路线" << endl
			<< " 3 : 查询两景点间最优路线" << endl
			<< " 4 : 电路铺设规划最佳方案" << endl 
			<< " 5 : 景区信息修改" << endl << endl
			<< "请输入对应编号选择需要进行的操作：";

		int ope;
		cin >> ope;
		system("cls");

		if (!ope)
			break;

		switch (ope)
		{
		case 1:
			vex_find(vex, graph);
			break;
		case 2:
			graph_tour(vex, graph);
			break;
		case 3:
			graph_shortest_path(vex, graph);
			break;
		case 4:
			graph_circuit_planning(vex, graph);
			break;
		case 5:
			graph_crud(vex, graph);
			break;
		default:
			cout << "无此功能，请重新输入指令";
			break;;
		}

		Sleep(1000);
		cout << endl << endl << "操作完成，";
		system("pause");
		system("cls");
	}
	

	delete[] graph;
	cout << "Over!";
	return 0;
}

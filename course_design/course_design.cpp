// course_design.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
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
		cout << "�ѳɹ����� " << vex.size() << " ������(���0-" << vex.size() - 1 << ")��������Ϣ" << endl;
		cout << "��ִ�в�������:" << endl
			<< " 0 : ��������" << endl
			<< " 1 : ��ѯ���������Ϣ" << endl
			<< " 2 : ��ѯ�������·��" << endl
			<< " 3 : ��ѯ�����������·��" << endl
			<< " 4 : ��·����滮��ѷ���" << endl 
			<< " 5 : ������Ϣ�޸�" << endl << endl
			<< "�������Ӧ���ѡ����Ҫ���еĲ�����";

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
			cout << "�޴˹��ܣ�����������ָ��";
			break;;
		}

		Sleep(1000);
		cout << endl << endl << "������ɣ�";
		system("pause");
		system("cls");
	}
	

	delete[] graph;
	cout << "Over!";
	return 0;
}

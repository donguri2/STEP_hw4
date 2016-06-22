#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <ctype.h>
#include "adjacencymatrix.h"

using namespace std;

struct info{
	float point;
	float num_edge;
	float hand_point;
};

int check_vertex_or_edge(string str,int &num_vertex)
{
	static int mark=0;			//mark=1で頂点読み込み中、mark=2で辺読み込み中,0だと数字
	if (isdigit(str[0])){
		if(mark == 0){
			num_vertex = atoi(str.c_str());
			mark++;
			return 0;
		}
		else if(mark == 1){
			mark++;
			return 0;
		}
	}
		return mark;
}

void make_vertex(string str,map<string,int> &vertex)		//入力された順に1,2,3...と番号をつけていく
{
	static int number=1;

	vertex[str] = number;
	number++;
}

void make_AdjacencyMatrix(int num_vertex,Adjacencymatrix &adj)
{
	adj.get_num_vertex(num_vertex);
	adj.make_adj();
}

void read_number(string str,string &origin,string &destin)
{
	origin = str[0];		//時間あればしっかり作る。
	destin = str[2];
	/*
	int flag = 0;
	string tmp;

	for (int i = 0; i < str.length(); ++i)
	{
		tmp = str[i];
		if(isalpha(tmp.c_str()))
		{
			if (!flag)
			{
			origin = str[i];
			}else
			destin = str[i];
		}
	}
	*/
}

void make_edge(string str,map<string,int> vertex,int num_vertex,Adjacencymatrix &adj)
{
	static int flag=0;
	string origin,destin;

	if (flag == 0)
	{
		make_AdjacencyMatrix(num_vertex,adj);
		flag++;
	}
	read_number(str,origin,destin);
	adj.add_edge(vertex[origin],vertex[destin]);
}


int readfile(map<string,int> &vertex,Adjacencymatrix &adj)		//ファイルを読む
{
	int mark;
	int num_vertex;

	ifstream ifs("small_data.txt");
	if(ifs.fail())
	{
		cerr << "Failed to open file" << endl;
		exit(1);
	}
	string str;
	while(getline(ifs,str))
	{
		mark=check_vertex_or_edge(str,num_vertex);
		if(mark == 1){
			make_vertex(str,vertex);
		}
		else if(mark == 2){
			make_edge(str,vertex,num_vertex,adj);
		}
	}
	return num_vertex;
}

int count_num_edge(Adjacencymatrix adj,int n,int num_vertex)
{
	int count = 0;
	int **matrix = adj.get_matrix();
	for (int i = 0; i < num_vertex; ++i)
	{
		count += matrix[n][i];
	}
	return count;
}

void add_info(Adjacencymatrix adj,int num_vertex,info* &vertex_info)
{
	for (int i = 0; i < num_vertex; ++i)
	{
		vertex_info[i].point = 0;
		vertex_info[i].num_edge = count_num_edge(adj,i,num_vertex);
		vertex_info[i].hand_point = num_vertex / vertex_info[i].num_edge;
	}
}

void hand_out_point(Adjacencymatrix adj,info* &vertex_info,int num_vertex)
{
	int **matrix = adj.get_matrix();
	float point;

	for (int i = 0; i < num_vertex; ++i)
	{
		point = vertex_info[i].hand_point;
		for (int j = 0; j < num_vertex; ++j)
		{
			if (matrix[i][j])
			{
				vertex_info[j].point += point;
			}
		}
	}
}

void init_point(int num_vertex,info* vertex_info)
{
	for (int i = 0; i < num_vertex; ++i)
	{
		vertex_info[i].point = 0;
	}
}

void point_in(int num_vertex,info* vertex_info)
{
	for (int i = 0; i < num_vertex; ++i)
	{
		vertex_info[i].hand_point = vertex_info[i].point / vertex_info[i].num_edge;
	}
}

void cycle(Adjacencymatrix adj,int num_vertex,info* vertex_info)
{
	int i = num_vertex;
	while(i){
	init_point(num_vertex,vertex_info);
	hand_out_point(adj,vertex_info,num_vertex);
	point_in(num_vertex,vertex_info);
	i--;
	}
}


void display(info* vertex_info,int num_vertex,map<string,int> vertex)
{
	map<string, int>::iterator itr;
	for (itr = vertex.begin();itr != vertex.end(); ++itr)
	{
		cout << itr->first << ":" << vertex_info[itr->second-1].point << endl;
	}
}

void checkdata(info* vertex_info,int num_vertex)
{
	float totalpoint=0;
	int total;
	for (int i = 0; i < num_vertex; ++i)
	{
		totalpoint += vertex_info[i].point;
	}
	total = num_vertex * num_vertex;
	cout << "こうなった:" <<totalpoint << endl << "本来:" << total << endl;
}

int main(int argc, char const *argv[])
{
	map<string,int> vertex;
	Adjacencymatrix adj;
	int num_vertex;
	info *vertex_info = new info[num_vertex];

	num_vertex = readfile(vertex,adj);
	//adj.display();  //check!


	add_info(adj,num_vertex,vertex_info);
	cycle(adj,num_vertex,vertex_info);
	adj.delete_matrix();
	display(vertex_info,num_vertex,vertex);
	checkdata(vertex_info,num_vertex);

	return 0;
}
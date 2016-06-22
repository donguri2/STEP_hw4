#include "adjacencymatrix.h"
#include <iostream>

using namespace std;

void Adjacencymatrix::get_num_vertex(int num)
{
	num_vertex = num;
}

void Adjacencymatrix::make_adj()
{
	matrix = new int*[num_vertex];
	for (int i = 0; i < num_vertex; ++i)
	{
		matrix[i] = new int[num_vertex];
		for (int j = 0; j < num_vertex; j++)
		{
			matrix[i][j] = 0;
		}
	}
}

void Adjacencymatrix::add_edge(int origin,int destin)
{
	if (origin > num_vertex || destin > num_vertex || origin < 0 || destin < 0)
	{
		cout << "Invalid edge!" << endl;
	}else{
		matrix[origin-1][destin-1] = 1;
	}
}

int** Adjacencymatrix::get_matrix()
{
	return matrix;
}

void Adjacencymatrix::display()
{
	for (int i = 0; i < num_vertex; ++i)
	{
		for (int j = 0; j < num_vertex; ++j)
		{
			cout << matrix[i][j] << " ";
		}
	cout << endl;
	}
}

void Adjacencymatrix::delete_matrix()
{
	for (int i = 0; i < num_vertex; ++i)
	{
		delete[] matrix[i];
	}
}
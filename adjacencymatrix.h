#ifndef _ADJACENCYMATRIX_H_
#define _ADJACENCYMATRIX_H_

class Adjacencymatrix
{
private:
	int num_vertex;		//サイズ
	int **matrix;
public:
	void get_num_vertex(int num);
	void make_adj();
	void add_edge(int origin,int destin);
	int** get_matrix();
	void display();
	void delete_matrix();
	
};

#endif
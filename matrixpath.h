#pragma once
class Matrixpath {
public:
	int n=0;//����� ũ��
	void initMatrix(int **arr, int col); //�ʱ�ȭ�ϴ� �Լ�->������ ���� �־ �迭�� ä���.
	void printMatrix(int **arr, int col); //����� ����ϴ� �Լ�->�ʱ�ȭ�� ����� ����Ѵ�.
	void printPath(int **cost, int **arr,int row, int col); //��θ� ����ϴ� �Լ�
	
	int maximum(int case1, int case2, int case3); //3���� ������ ĭ�� ���� �ִ��� ����ϴ� �Լ�
	int recursion(int **arr,int **cost,  int i, int j, int n, int **count, int *count_i, int *count_j); //recursion function
	int dynamic_programming(int **arr, int **cost,  int col, int *count_i, int *count_j); //dynamic_programming funtion


};

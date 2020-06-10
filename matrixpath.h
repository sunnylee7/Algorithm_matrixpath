#pragma once
class Matrixpath {
public:
	int n=0;//행렬의 크기
	void initMatrix(int **arr, int col); //초기화하는 함수->랜덤한 값을 넣어서 배열을 채운다.
	void printMatrix(int **arr, int col); //행렬을 출력하는 함수->초기화된 행렬을 출력한다.
	void printPath(int **cost, int **arr,int row, int col); //경로를 출력하는 함수
	
	int maximum(int case1, int case2, int case3); //3가지 인접한 칸에 대해 최댓값을 출력하는 함수
	int recursion(int **arr,int **cost,  int i, int j, int n, int **count, int *count_i, int *count_j); //recursion function
	int dynamic_programming(int **arr, int **cost,  int col, int *count_i, int *count_j); //dynamic_programming funtion


};

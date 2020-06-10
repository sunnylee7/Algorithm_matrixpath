#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <malloc.h>
#include "matrixpath.h"
#pragma warning(disable: 4996) 
using namespace std;



int main()
{

	Matrixpath map;
	int n = map.n;
	int *size = (int*)malloc(sizeof(int)* n);
	printf("-행렬의 경로 찾기 프로그램-\n");
	printf("IT공학과 1812313 이현선\n");
	printf("행렬의 왼쪽 위 원소(1,1)에서 원소(i,j)까지 도달하는 경로들의 점수 중 최고점 구하기->(i,j)는 (i-1,j), (i,j-1), (i-1,j-1)원소들 중 하나 방문 가능\n");
	printf("\n*행렬 경로 찾기 규칙\n");
	printf("오른쪽, 아래쪽, 오른쪽 아래로만 이동할 수 있다 \n 왼쪽, 위쪽, 왼쪽 위로는 이동할 수 없다.\n");
	printf("\n*음수를 행렬값에 할당하는 이유: 대각선 이동을 허용하였으므로, 이를 활용하기 위해서.\n");
	printf("만일 양수로만 행렬을 채우면, 모든 경우에서 대각선으로 이동하는 것 보다 오른쪽->아래쪽(ㄱ자 이동)이나 아래쪽->오른쪽(ㄴ자 이동)의 경우가 점수의 합이 더 클것이다\n");
	printf("따라서, 대각선 이동은 일어나는 일이 없어진다. 그러나 음수를 행렬값에 할당하면, 오른쪽값과 아래쪽값이 음수이고 대각선 값이 양수라면, 혹은 그 값이 더 작은 음수일 경우, 대각선으로 이동하는 것이 점수가 더 클 수 있다.\n");
	printf("따라서, 음수가 있는 행렬의 경우는 대각선 이동이 유의미하고, 효율적인 이동이 된다. 이 문제는 대각선 이동을 고려하므로, 음수를 할당해야 이를 활용할 수 있다.\n\n");
	printf("-입력된 크기(n)의 n*n행렬에서, (1,1)에서 (n,n)까지 가는 경로를 출력\n");
	printf("원하는 행렬의 크기를 입력하세요. 단 , 양수여야합니다.");
	scanf("%d", &n);
	
	//배열을 동적으로 할당하기
	n++; //배열을 1부터 시작할 것이므로(0번째 행/열들은 판단용), 입력한 값에서 1을 더해준다.

	int **path; //경로를 알고자하는 행렬 생성
	//행렬의 크기를 동적으로 할당하기
	path = (int **)malloc(sizeof(int *) * n); 
	path[0] = (int *)malloc(sizeof(int) * n*n);
	for (int i = 1; i < n; i++) //주소를 배정
	{
		path[i] = path[i - 1] + n;
	}

	

	//recursion 함수에서 중복횟수를 조사해서 출력하는 행렬
	int **p_count;
	p_count = (int **)malloc(sizeof(int *) * n);
	p_count[0] = (int *)malloc(sizeof(int) * n * n);
	for (int i = 1; i < n; i++) //주소 배 정
	{
		p_count[i] = p_count[i - 1] + n;
	}
	
	for (int i = 0; i < n ; i++)
	{
		for (int j = 0; j < n ; j++)
		{
			p_count[i][j] = 0;
			
		}
		
	}
	
	//칸의 최고점수를 저장하는 행렬
	int **cost;
	//행렬의 크기를 동적으로 할당하기
	cost = (int **)malloc(sizeof(int *) * n);
	cost[0] = (int *)malloc(sizeof(int) * n*n);
	for (int i = 1; i < n; i++) 
	{
		cost[i] = cost[i - 1] + n;
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cost[i][j] = 0;
			
		}
	}



	//중간경로 출력을 위한 index  배열
	int *count_i; //index i를 저장할 배열
	count_i = (int *)malloc(sizeof(int) * n);
	int *count_j; //index j를 저장할 배열
	count_j = (int *)malloc(sizeof(int) * n);
	for (int t = 0; t < n; t++)
	{
		count_i[t] = 0;
		count_j[t] = 0;
	}
	//count_i[t]나 count_j[t] 가 0이 아니면, path[t][t] 를 지나갔다는 표시

	double rec = 0, dp = 0;//recursion 함수와 dynamic programming 함수의 수행시간을 저장하는 변수

	//recursion 
	printf("================================================================================\n");
	printf("\n<recursion(재귀법)을 이용한 행렬 경로 구하기>\n");
	printf("재귀법을 이용한 방법은, 행렬의 마지막 원소인 (n,n)부터, 왼쪽, 위쪽, 왼쪽 대각선 위쪽 값의 최고점수를 비교해 큰 값을 반환하는 방법으로, 각 칸의 최고점수를 구하기 위해, 재귀적으로 recursion함수를 실행해서 그 값을 얻는 방법이다.");
	map.initMatrix(path, n); //path행렬, 즉, 경로를 구할 행렬을 초기화
	printf("\n경로를 구하고자 하는 행렬\n");
	map.printMatrix(path, n); //초기화된 행렬을 출력.

	//걸리는 시간 측정
	LARGE_INTEGER StartCounter1, EndCounter1, liFrequency1;// 시간 측정에 사용하기 위한 변수
	QueryPerformanceFrequency(&liFrequency1); // 주파수(1초당 증가되는 카운트수)를 구한다. 시간측정의 초기화
	QueryPerformanceCounter(&StartCounter1); // 코드 수행 전 카운트 저장
	
	int result;
	result = map.recursion(path,cost, n-1, n-1,n, p_count, count_i,count_j); //recursion 함수의 결과를 저장
	printf("\n최고점수: %d\n", result);

	printf("중복횟수 출력\n");
	printf("************************************\n");
	//p_count[1][1]--;
	for (int x = 1; x < n; x++)
	{
		for (int y = 1; y < n; y++)
		{
			printf("%d  ", p_count[x][y]);
		}
		printf("\n");
	}
	printf("************************************\n");
	
	//경로출력
	map.printPath(cost, path, n,n);

	//동적으로 할당했던 배열을 해제해준다.
	free(p_count[0]); //p_count 행렬 가로공간 해제
	free(p_count); //p_count 행렬 세로공간 해제
	

	
	QueryPerformanceCounter(&EndCounter1); // 코드 수행 후 카운트 저장
	rec = (double)(EndCounter1.QuadPart - StartCounter1.QuadPart) / (double)liFrequency1.QuadPart; //rec에 recursion 함수 수행시간 저장
	printf("\n\n재귀법 수행시간 = %.2f 초\n", rec);

	//dynamic programming
	printf("================================================================================\n");
	printf("\n <dynamic programming(동적 프로그래밍)을 이용한 행렬 경로 구하기>\n");
	printf("동적 프로그래밍을 이용한 방법은, 행렬의 임의의 원소까지 이르는 최고점수들을 cost 행렬에 저장한 후,  (n,n)부터, cost의 왼쪽, 위쪽, 왼쪽 대각선 위쪽 값의 최고점수를 비교해 큰 값을 반환하는 방법이다.");

	//최종점수를 저장하는 행렬 초기화
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j <n; j++)
		{
			cost[i][j] = 0;
		}
	}

	//중간 경로 출력을 위한 index 배열 초기화
	for (int t = 0; t < n; t++)
	{
		count_i[t] = 0;
		count_j[t] = 0;
	}



	printf("\n경로를 구하고자 하는 행렬\n");
	map.printMatrix(path, n); //경로를 출력할 행렬출력
	//걸리는 시간 측정
	LARGE_INTEGER StartCounter2, EndCounter2, liFrequency2; // 시간 측정에 사용하기 위한 변수
	QueryPerformanceFrequency(&liFrequency2); // 주파수(1초당 증가되는 카운트수)를 구한다. 시간측정의 초기화
	QueryPerformanceCounter(&StartCounter2); // 코드 수행 전 카운트 저장

	map.dynamic_programming(path,cost, n, count_i, count_j);  //동적 프로그래밍 실행

	
	//수행시간 측정
	QueryPerformanceCounter(&EndCounter2); // 코드 수행 후 카운트 저장
	dp = (double)(EndCounter2.QuadPart - StartCounter2.QuadPart) / (double)liFrequency2.QuadPart; //dp에 dynamic programming 수행 시간을 저장
	printf("\n\n동적 프로그래밍 수행시간 = %.2f 초\n", dp);

	free(path[0]); // 가로 공 간 해제
	free(path); // 세로 공 간 해제
	free(cost[0]); //cost 행렬 가로공간 해제
	free(cost);//cost 행렬 세로공간 해제
	free(count_i);
	free(count_j);

	if (rec - dp > 0)
		printf("\n동적 프로그래밍이  재귀법보다 %.2f 초 더 빠른 수행시간을 갖는다", rec - dp); 
	else if(rec - dp <0)
		printf("\n재귀법이 동적프로그래밍보다 %.2f 초 더 빠른 수행시간을 갖는다", dp - rec);


}

//행렬에 값들을 채우는 함수
void Matrixpath::initMatrix(int **arr, int col)
{
	//행렬은 1부터 시작할 것이므로, i가0이고, j가 0인 원소들은  0으로 채우고 값은 채우지 않는다.
	for (int i = 0; i < col; i++)
	{
		arr[i][0] = 0;
	}

	for (int j = 0; j < col; j++)
	{
		arr[0][j] = 0;
	}

	srand(GetTickCount()); //시간을 매번 바꿔서 그에 따라 랜덤한 수를 생성한다.
	for (int i = 1; i < col; i++)
	{
		for (int j = 1; j < col; j++)
		{
			//행렬을 -100부터 100까지의 수를 임의로 골라 채운다.
			arr[i][j] = (int)(rand() % (201) - 100); //201로 나눈 나머지 값들의 범위에서 난수를 발생. 즉, 0~200까지의 범위에서 발생한다. -100을 해주어 범위를 -100~100 범위로 바꿔준다.
		}
	}
}

//행렬을 출력하는 함수
void Matrixpath::printMatrix(int **arr, int col)
{
	//1행 1열부터 원소값 모두 출력
	for (int i = 1; i < col; i++)
	{
		for (int j = 1; j < col; j++)
		{
			printf("        %d ", arr[i][j]);
		}
		printf("\n");
	}
}


//경로를 출력하는 함수
void Matrixpath::printPath(int **cost, int **arr, int row, int col)
{
	//cost배열은 최고점수들을 저장해놓은 행렬
	int *path; //경로를 저장할 배열
	path = (int *)malloc(sizeof(int) * row*col);

	//좌표를 저장할 배열
	int *x; //경로를 저장할 배열
	x = (int *)malloc(sizeof(int) * row*col);

	int *y; //경로를 저장할 배열
	y = (int *)malloc(sizeof(int) * row*col);


	int p_index = 0; //경로를 저장하는 배열의 index
	int result = cost[row - 1][col - 1]; //현재 위치한 칸까지의 최고점수를 저장하는 변수
	int i = row - 1, j = col - 1;
	
	while (i != 0 && j != 0)
	{
		//(i,y)의 위치의 cost값, 즉, (i,j)까지의 최고점수에서 현재 위치 (i,j)값을 뺸 값을, cost의 위쪽 값(지나온 값)과 비교해 일치하먼,
		if (result - arr[i][j] == cost[i - 1][j])
		{
			path[p_index] = arr[i - 1][j]; //일치한다는 것은 그 길을 지나왔다는 것이므로, 경로를 저장하는 배열 path에 해당 cost값에 해당하는 위치(i-1,j)의 arr값, 즉 원래 행렬의 값을 저장
			x[p_index] = i - 1; //x좌표저장
			y[p_index] = j; //y좌표저장
			result = result - arr[i][j]; //현재 위치를 지나온 길로 갱신. (이 과정을 반복하면 경로를 거슬러 올라가서 1,1 에 다다르면 경로를 출력한다.
			i--; //위쪽으로 이동했으므로 i값 감소시킨다.
			p_index++; //값을 저장했으므로, 경로를 저장하는 행렬을 한 칸 이동시킴
		
		}

		//(i,y)의 위치의 cost값, 즉, (i,j)까지의 최고점수에서 현재 위치 (i,j)값을 뺸 값을,  cost의 왼쪽(지나온 값들)과 비교해 일치하먼,
		else if (result - arr[i][j] == cost[i][j - 1])
		{
			path[p_index] = arr[i][j - 1];//일치한다는 것은 그 길을 지나왔다는 것이므로, 경로를 저장하는 배열 path에 해당 cost값에 해당하는 위치(i,j-1)의 arr값, 즉 원래 행렬의 값을 저장
			x[p_index] = i;  //x좌표저장
			y[p_index] = j-1; //y좌표저장
			result = result - arr[i][j]; //현재 위치를 지나온 길로 갱신
			j--; //왼쪽으로 이동했으므로 j값 감소시킨다.
			p_index++; //값을 저장했으므로, 경로를 저장하는 행렬을 한 칸 이동시킴
		}

		//(i,y)의 위치의 cost값, 즉, (i,j)까지의 최고점수에서 현재 위치 (i,j)값을 뺸 값을,  cost의 왼쪽 대각선 값(지나온 값들)과 비교해 일치하먼,
		else if (result - arr[i][j] == cost[i - 1][j - 1])
		{
			path[p_index] = arr[i - 1][j - 1];//일치한다는 것은 그 길을 지나왔다는 것이므로, 경로를 저장하는 배열 path에 해당 cost값에 해당하는 위치(i-1,j-1)의 arr값, 즉 원래 행렬의 값을 저장
			x[p_index] = i - 1; //x좌표저장
			y[p_index] = j-1; //y좌표저장
			result = result - arr[i][j];//현재 위치를 지나온 길로 갱신
			i--; j--;  //왼쪽 대각선으로 이동했으므로 i,j값 감소시킨다.
			p_index++; //값을 저장했으므로, 경로를 저장하는 행렬을 한 칸 이동시킴
		}

	}

	//경로를 출력
	printf("\n최종경로출력: i 는 열, j는 행\n");
	for (int t = p_index - 2; t >= 0; t--)
	{
		printf("(i = %d, j = %d) : %d->", x[t], y[t], path[t]); //좌표,값 출력
	}
	printf("(i = %d, j = %d) : %d ", col-1, col-1, arr[col - 1][col - 1]);
	free(x);
	free(y);
}



int Matrixpath::maximum(int case1, int case2, int case3) // 3가지 경로중에 가장 큰 값을 리턴하는 함수
{
	int max;
	max = case1 > case2 ? case1 : case2; //case1를 먼저 비교해서 큰 값을 리턴
	max = max > case3 ? max : case3; //비교된 ase1과 case2 값 중 큰 값과 case3 비교
	return max;
}

//recursion function
int Matrixpath::recursion(int **arr, int **cost, int i, int j, int n, int **count, int *count_i, int *count_j) 
{
	count[i][j]++;//recursion에 들어오면 호출된 것이므로,  호출된 횟수를 증가시킨다.

	if (i == 0 || j == 0)
	{
		return 0;
	}

	else if (i == 1 && j != 1)
	{
		//i가 1일때는가장 큰 값이 왼쪽 값이므로, 왼쪽값의 최고점수와 더한다. 
		int r = arr[i][j] + recursion(arr, cost, i, j - 1, n, count, count_i, count_j);
		if (cost[i][j] == 0) //최고점수를 저장하는 행렬인 cost에 현재 위치까지의 최고점수가 저장되지 않았으면, 구한 최고점수 값을 저장한다. 
		{						//(이미 저장되어 있다면 , 저장되어 있는 값이 (먼저 recursion 이 수행되어 maximum을 통해 최고점수로 판단된 것이므로, 그 칸까지의 경로 중 제일 큰 값이다. ) 더 큰 것이므로, 
								//덮어쓰지 않는다.	
			cost[i][j] = r; //r은 (i,j)까지의 경로의 최고점수(cost[i][j] == 0이므로)
		}
		return r; 
	}

	//j가 1일때는가장 큰 값이 위쪽 값이므로, 위쪽값의 최고점수와 더한다. 
	else if (i != 1 && j == 1)
	{		
		
		int r2 = arr[i][j] + recursion(arr, cost, i-1, j , n, count, count_i, count_j);
		if (cost[i][j] == 0)//최고점수를 저장하는 행렬인 cost에 현재 위치까지의 최고점수가 저장되지 않았으면, 구한 최고점수 값을 저장한다. 
		{
			cost[i][j] = r2;
		}
		return r2;
	}

	//i, j가 1일때는가장 큰 값이 (1,1)이므로, arr 행렬의 (1,1)원소를 반환한다.
	else if (i == 1 && j == 1)
	{
		
		if (cost[i][j] == 0)
		{
			cost[i][j] = arr[i][j];//최고점수를 저장하는 행렬인 cost에 (1,1)원소의 값이 저장되지 않았으면,  저장한다. 
		}
		return arr[i][j];
	}
	
	else
	{
		//경로 탐색 과정 출력하는 부분 
		//*입력한 행렬크기 n이 5 이상이면, 출력이 너무 많아지므로
		// 이부분부터
		//위쪽,왼쪽, 왼쪽 대각선 위쪽 값들의 최고점수를 비교하여 더 큰 값을 현재값과 더해 최고점수를 구한다. 
		int res = arr[i][j] + maximum(recursion(arr, cost, i - 1, j, n, count, count_i, count_j), recursion(arr, cost, i, j - 1, n, count, count_i, count_j), recursion(arr, cost, i - 1, j - 1, n, count, count_i, count_j));
		if (cost[i][j] == 0)
		{
			
			//최고점수들이 저장되는 과정 출력
			int max = maximum(cost[i - 1][j], cost[i][j - 1], cost[i - 1][j - 1]);
			if (max == cost[i - 1][j] && count_i[i] == 0 && count_j[j] == 0)
			{
				printf("--------------------------------------------------------------------------------------------------------\n");
				printMatrix(cost, n);
				printf("인접한 세 칸의 최고점수들 중 arr[%d][%d]=%d까지의 값이 %d로 가장 크므로, ", i - 1, j, arr[i - 1][j], cost[i - 1][j]);
				printf("%d로 이동\n", arr[i - 1][j]);
				count_i[i - 1]++; count_j[j]++;
			}

			else if (max == cost[i][j - 1] && count_i[i] == 0 && count_j[j] == 0)
			{
				printf("--------------------------------------------------------------------------------------------------------\n");
				printMatrix(cost, n);
				printf("인접한 세 칸의 최고점수들 중 arr[%d][%d]=%d까지의 값이 %d로 가장 크므로, ", i, j - 1, arr[i][j - 1], cost[i][j - 1]);
				printf("%d으로 이동\n", arr[i][j - 1]);
				count_i[i]++; count_j[j - 1]++;
			}

			else if (max == cost[i - 1][j - 1] && count_i[i] == 0 && count_j[j] == 0)
			{
				printf("--------------------------------------------------------------------------------------------------------\n");
				printMatrix(cost, n);
				printf("인접한 세 칸의 최고점수들 중 arr[%d][%d]=%d까지의 값이 %d로 가장 크므로 , ", i - 1, j - 1, arr[i - 1][j - 1], cost[i - 1][j - 1]);
				printf("%d으로 이동\n", arr[i - 1][j - 1]);
				count_i[i - 1]++; count_j[j - 1]++;
			}
			printf("\n");
			//이 부분까지는 주석처리하고 실행해주세요(출력이 너무 많을때)
			
			cost[i][j] = res; //최고점수를 저장하는 행렬인 cost에 현재 위치까지의 최고점수가 저장되지 않았으면, 구한 최고점수 값을 저장한다. 
			printf("\n");
		

		}
		return res;
	}

	
}
		

int Matrixpath::dynamic_programming(int **arr, int **cost, int col,int *count_i, int *count_j)
{
	int i, j; // i 는 행렬의 열을, j는 행을 나타낸다.
	

	//3가지 경로 중에 최고점수를 비교해서 현재 경로의 값과 더한다.
	for (int i = 1; i < col; i++)
	{
		for (int j = 1; j < col; j++)
		{
			//행렬의 (1,1)에서부터 시작하므로, 처음에 값을 입력해주어야한다.
			if (i == 1 && j == 1)
			{
				cost[i][j] = arr[i][j]; //i,j가 1일 때는 cost[1][1]에 arr[1][1]값을 저장
				if (count_i[i] == 0 && count_j[j] == 0)
				{
					//printf("인접한 세 칸의 최고점수들 중 arr[%d][%d]=%d까지의 값이 %d로 가장 크므로, ", i, j - 1, arr[i][j - 1], cost[i][j - 1]);
					printf("%d출발\n", arr[i][j]);
					//count_i[i]++; count_j[j]++;
				}
				
			}
			else if (i == 1 && j != 1)
			{
				cost[i][j] = cost[1][j-1] + arr[1][j]; //i가 1일때는 cost[1][j]값에 왼쪽 칸의 최고점수를 더함
				
			}
			else if (i != 1 && j == 1)
			{
				cost[i][j] = cost[i-1][j] + arr[i][1]; //j가 1일때는 cost[1][j]값에 위쪽 칸의 최고점수를 더함
				
			}

			else
			{			
				cost[i][j] = arr[i][j] + maximum(cost[i - 1][j], cost[i][j - 1], cost[i - 1][j - 1]); //왼쪽, 위쪽, 왼쪽 대각선 위쪽 값의 최고점수를 비교해 큰 값에 현재 값을 더해 최고점수를 만든다.

				//경로 탐색 과정 출력하는 부분 
				//*입력한 행렬크기 n이 5 이상이면, 출력이 너무 많아지므로
				// 이부분부터
				//위쪽,왼쪽, 왼쪽 대각선 위쪽 값들의 최고점수를 비교하여 더 큰 값을 현재값과 더해 최고점수를 구한다. 
				int res = arr[i][j] + maximum(cost[i - 1][j], cost[i][j - 1], cost[i - 1][j - 1]);
				
					
					//최고점수들이 저장되는 과정 출력
					int max = maximum(cost[i - 1][j], cost[i][j - 1], cost[i - 1][j - 1]);
					if (max == cost[i - 1][j] && count_i[i] == 0 && count_j[j] == 0)
					{
						printf("--------------------------------------------------------------------------------------------------------\n");
						printMatrix(cost, col);
						printf("인접한 세 칸의 최고점수들 중 arr[%d][%d]=%d까지의 값이 %d로 가장 크므로, ", i - 1, j, arr[i - 1][j], cost[i - 1][j]);
						printf("%d로 이동\n", arr[i - 1][j]);
						count_i[i - 1]++; count_j[j]++;
					}

					else if (max == cost[i][j - 1] && count_i[i]==0 && count_j[j]==0)
					{
						printf("--------------------------------------------------------------------------------------------------------\n");
						printMatrix(cost, col);
						printf("인접한 세 칸의 최고점수들 중 arr[%d][%d]=%d까지의 값이 %d로 가장 크므로, ", i, j - 1, arr[i][j - 1], cost[i][j - 1]);
						printf("%d으로 이동\n", arr[i][j - 1]);
						count_i[i]++; count_j[j - 1]++;
					}

					else if (max == cost[i - 1][j - 1] && count_i[i] == 0 && count_j[j] == 0)
					{
						printf("--------------------------------------------------------------------------------------------------------\n");
						printMatrix(cost, col);
						printf("인접한 세 칸의 최고점수들 중 arr[%d][%d]=%d까지의 값이 %d로 가장 크므로 , ", i - 1, j - 1, arr[i - 1][j - 1], cost[i - 1][j - 1]);
						printf("%d으로 이동\n", arr[i - 1][j - 1]);
						count_i[i-1]++; count_j[j-1]++;
					}
					printf("\n");
					//이 부분까지는 주석처리하고 실행해주세요(출력이 너무 많을때)
				

			}
			

		}
	}
	//최종 최고점수 출력
	printf("\n\n최종 최고점수: %d\n", cost[col - 1][col - 1]);
	//최종 경로를 출력
	printPath(cost, arr, col,col);
	return cost[col - 1][col - 1];

}

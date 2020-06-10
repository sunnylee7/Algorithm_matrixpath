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
	printf("-����� ��� ã�� ���α׷�-\n");
	printf("IT���а� 1812313 ������\n");
	printf("����� ���� �� ����(1,1)���� ����(i,j)���� �����ϴ� ��ε��� ���� �� �ְ��� ���ϱ�->(i,j)�� (i-1,j), (i,j-1), (i-1,j-1)���ҵ� �� �ϳ� �湮 ����\n");
	printf("\n*��� ��� ã�� ��Ģ\n");
	printf("������, �Ʒ���, ������ �Ʒ��θ� �̵��� �� �ִ� \n ����, ����, ���� ���δ� �̵��� �� ����.\n");
	printf("\n*������ ��İ��� �Ҵ��ϴ� ����: �밢�� �̵��� ����Ͽ����Ƿ�, �̸� Ȱ���ϱ� ���ؼ�.\n");
	printf("���� ����θ� ����� ä���, ��� ��쿡�� �밢������ �̵��ϴ� �� ���� ������->�Ʒ���(���� �̵�)�̳� �Ʒ���->������(���� �̵�)�� ��찡 ������ ���� �� Ŭ���̴�\n");
	printf("����, �밢�� �̵��� �Ͼ�� ���� ��������. �׷��� ������ ��İ��� �Ҵ��ϸ�, �����ʰ��� �Ʒ��ʰ��� �����̰� �밢�� ���� ������, Ȥ�� �� ���� �� ���� ������ ���, �밢������ �̵��ϴ� ���� ������ �� Ŭ �� �ִ�.\n");
	printf("����, ������ �ִ� ����� ���� �밢�� �̵��� ���ǹ��ϰ�, ȿ������ �̵��� �ȴ�. �� ������ �밢�� �̵��� ����ϹǷ�, ������ �Ҵ��ؾ� �̸� Ȱ���� �� �ִ�.\n\n");
	printf("-�Էµ� ũ��(n)�� n*n��Ŀ���, (1,1)���� (n,n)���� ���� ��θ� ���\n");
	printf("���ϴ� ����� ũ�⸦ �Է��ϼ���. �� , ��������մϴ�.");
	scanf("%d", &n);
	
	//�迭�� �������� �Ҵ��ϱ�
	n++; //�迭�� 1���� ������ ���̹Ƿ�(0��° ��/������ �Ǵܿ�), �Է��� ������ 1�� �����ش�.

	int **path; //��θ� �˰����ϴ� ��� ����
	//����� ũ�⸦ �������� �Ҵ��ϱ�
	path = (int **)malloc(sizeof(int *) * n); 
	path[0] = (int *)malloc(sizeof(int) * n*n);
	for (int i = 1; i < n; i++) //�ּҸ� ����
	{
		path[i] = path[i - 1] + n;
	}

	

	//recursion �Լ����� �ߺ�Ƚ���� �����ؼ� ����ϴ� ���
	int **p_count;
	p_count = (int **)malloc(sizeof(int *) * n);
	p_count[0] = (int *)malloc(sizeof(int) * n * n);
	for (int i = 1; i < n; i++) //�ּ� �� ��
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
	
	//ĭ�� �ְ������� �����ϴ� ���
	int **cost;
	//����� ũ�⸦ �������� �Ҵ��ϱ�
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



	//�߰���� ����� ���� index  �迭
	int *count_i; //index i�� ������ �迭
	count_i = (int *)malloc(sizeof(int) * n);
	int *count_j; //index j�� ������ �迭
	count_j = (int *)malloc(sizeof(int) * n);
	for (int t = 0; t < n; t++)
	{
		count_i[t] = 0;
		count_j[t] = 0;
	}
	//count_i[t]�� count_j[t] �� 0�� �ƴϸ�, path[t][t] �� �������ٴ� ǥ��

	double rec = 0, dp = 0;//recursion �Լ��� dynamic programming �Լ��� ����ð��� �����ϴ� ����

	//recursion 
	printf("================================================================================\n");
	printf("\n<recursion(��͹�)�� �̿��� ��� ��� ���ϱ�>\n");
	printf("��͹��� �̿��� �����, ����� ������ ������ (n,n)����, ����, ����, ���� �밢�� ���� ���� �ְ������� ���� ū ���� ��ȯ�ϴ� �������, �� ĭ�� �ְ������� ���ϱ� ����, ��������� recursion�Լ��� �����ؼ� �� ���� ��� ����̴�.");
	map.initMatrix(path, n); //path���, ��, ��θ� ���� ����� �ʱ�ȭ
	printf("\n��θ� ���ϰ��� �ϴ� ���\n");
	map.printMatrix(path, n); //�ʱ�ȭ�� ����� ���.

	//�ɸ��� �ð� ����
	LARGE_INTEGER StartCounter1, EndCounter1, liFrequency1;// �ð� ������ ����ϱ� ���� ����
	QueryPerformanceFrequency(&liFrequency1); // ���ļ�(1�ʴ� �����Ǵ� ī��Ʈ��)�� ���Ѵ�. �ð������� �ʱ�ȭ
	QueryPerformanceCounter(&StartCounter1); // �ڵ� ���� �� ī��Ʈ ����
	
	int result;
	result = map.recursion(path,cost, n-1, n-1,n, p_count, count_i,count_j); //recursion �Լ��� ����� ����
	printf("\n�ְ�����: %d\n", result);

	printf("�ߺ�Ƚ�� ���\n");
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
	
	//������
	map.printPath(cost, path, n,n);

	//�������� �Ҵ��ߴ� �迭�� �������ش�.
	free(p_count[0]); //p_count ��� ���ΰ��� ����
	free(p_count); //p_count ��� ���ΰ��� ����
	

	
	QueryPerformanceCounter(&EndCounter1); // �ڵ� ���� �� ī��Ʈ ����
	rec = (double)(EndCounter1.QuadPart - StartCounter1.QuadPart) / (double)liFrequency1.QuadPart; //rec�� recursion �Լ� ����ð� ����
	printf("\n\n��͹� ����ð� = %.2f ��\n", rec);

	//dynamic programming
	printf("================================================================================\n");
	printf("\n <dynamic programming(���� ���α׷���)�� �̿��� ��� ��� ���ϱ�>\n");
	printf("���� ���α׷����� �̿��� �����, ����� ������ ���ұ��� �̸��� �ְ��������� cost ��Ŀ� ������ ��,  (n,n)����, cost�� ����, ����, ���� �밢�� ���� ���� �ְ������� ���� ū ���� ��ȯ�ϴ� ����̴�.");

	//���������� �����ϴ� ��� �ʱ�ȭ
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j <n; j++)
		{
			cost[i][j] = 0;
		}
	}

	//�߰� ��� ����� ���� index �迭 �ʱ�ȭ
	for (int t = 0; t < n; t++)
	{
		count_i[t] = 0;
		count_j[t] = 0;
	}



	printf("\n��θ� ���ϰ��� �ϴ� ���\n");
	map.printMatrix(path, n); //��θ� ����� ������
	//�ɸ��� �ð� ����
	LARGE_INTEGER StartCounter2, EndCounter2, liFrequency2; // �ð� ������ ����ϱ� ���� ����
	QueryPerformanceFrequency(&liFrequency2); // ���ļ�(1�ʴ� �����Ǵ� ī��Ʈ��)�� ���Ѵ�. �ð������� �ʱ�ȭ
	QueryPerformanceCounter(&StartCounter2); // �ڵ� ���� �� ī��Ʈ ����

	map.dynamic_programming(path,cost, n, count_i, count_j);  //���� ���α׷��� ����

	
	//����ð� ����
	QueryPerformanceCounter(&EndCounter2); // �ڵ� ���� �� ī��Ʈ ����
	dp = (double)(EndCounter2.QuadPart - StartCounter2.QuadPart) / (double)liFrequency2.QuadPart; //dp�� dynamic programming ���� �ð��� ����
	printf("\n\n���� ���α׷��� ����ð� = %.2f ��\n", dp);

	free(path[0]); // ���� �� �� ����
	free(path); // ���� �� �� ����
	free(cost[0]); //cost ��� ���ΰ��� ����
	free(cost);//cost ��� ���ΰ��� ����
	free(count_i);
	free(count_j);

	if (rec - dp > 0)
		printf("\n���� ���α׷�����  ��͹����� %.2f �� �� ���� ����ð��� ���´�", rec - dp); 
	else if(rec - dp <0)
		printf("\n��͹��� �������α׷��ֺ��� %.2f �� �� ���� ����ð��� ���´�", dp - rec);


}

//��Ŀ� ������ ä��� �Լ�
void Matrixpath::initMatrix(int **arr, int col)
{
	//����� 1���� ������ ���̹Ƿ�, i��0�̰�, j�� 0�� ���ҵ���  0���� ä��� ���� ä���� �ʴ´�.
	for (int i = 0; i < col; i++)
	{
		arr[i][0] = 0;
	}

	for (int j = 0; j < col; j++)
	{
		arr[0][j] = 0;
	}

	srand(GetTickCount()); //�ð��� �Ź� �ٲ㼭 �׿� ���� ������ ���� �����Ѵ�.
	for (int i = 1; i < col; i++)
	{
		for (int j = 1; j < col; j++)
		{
			//����� -100���� 100������ ���� ���Ƿ� ��� ä���.
			arr[i][j] = (int)(rand() % (201) - 100); //201�� ���� ������ ������ �������� ������ �߻�. ��, 0~200������ �������� �߻��Ѵ�. -100�� ���־� ������ -100~100 ������ �ٲ��ش�.
		}
	}
}

//����� ����ϴ� �Լ�
void Matrixpath::printMatrix(int **arr, int col)
{
	//1�� 1������ ���Ұ� ��� ���
	for (int i = 1; i < col; i++)
	{
		for (int j = 1; j < col; j++)
		{
			printf("        %d ", arr[i][j]);
		}
		printf("\n");
	}
}


//��θ� ����ϴ� �Լ�
void Matrixpath::printPath(int **cost, int **arr, int row, int col)
{
	//cost�迭�� �ְ��������� �����س��� ���
	int *path; //��θ� ������ �迭
	path = (int *)malloc(sizeof(int) * row*col);

	//��ǥ�� ������ �迭
	int *x; //��θ� ������ �迭
	x = (int *)malloc(sizeof(int) * row*col);

	int *y; //��θ� ������ �迭
	y = (int *)malloc(sizeof(int) * row*col);


	int p_index = 0; //��θ� �����ϴ� �迭�� index
	int result = cost[row - 1][col - 1]; //���� ��ġ�� ĭ������ �ְ������� �����ϴ� ����
	int i = row - 1, j = col - 1;
	
	while (i != 0 && j != 0)
	{
		//(i,y)�� ��ġ�� cost��, ��, (i,j)������ �ְ��������� ���� ��ġ (i,j)���� �A ����, cost�� ���� ��(������ ��)�� ���� ��ġ�ϸ�,
		if (result - arr[i][j] == cost[i - 1][j])
		{
			path[p_index] = arr[i - 1][j]; //��ġ�Ѵٴ� ���� �� ���� �����Դٴ� ���̹Ƿ�, ��θ� �����ϴ� �迭 path�� �ش� cost���� �ش��ϴ� ��ġ(i-1,j)�� arr��, �� ���� ����� ���� ����
			x[p_index] = i - 1; //x��ǥ����
			y[p_index] = j; //y��ǥ����
			result = result - arr[i][j]; //���� ��ġ�� ������ ��� ����. (�� ������ �ݺ��ϸ� ��θ� �Ž��� �ö󰡼� 1,1 �� �ٴٸ��� ��θ� ����Ѵ�.
			i--; //�������� �̵������Ƿ� i�� ���ҽ�Ų��.
			p_index++; //���� ���������Ƿ�, ��θ� �����ϴ� ����� �� ĭ �̵���Ŵ
		
		}

		//(i,y)�� ��ġ�� cost��, ��, (i,j)������ �ְ��������� ���� ��ġ (i,j)���� �A ����,  cost�� ����(������ ����)�� ���� ��ġ�ϸ�,
		else if (result - arr[i][j] == cost[i][j - 1])
		{
			path[p_index] = arr[i][j - 1];//��ġ�Ѵٴ� ���� �� ���� �����Դٴ� ���̹Ƿ�, ��θ� �����ϴ� �迭 path�� �ش� cost���� �ش��ϴ� ��ġ(i,j-1)�� arr��, �� ���� ����� ���� ����
			x[p_index] = i;  //x��ǥ����
			y[p_index] = j-1; //y��ǥ����
			result = result - arr[i][j]; //���� ��ġ�� ������ ��� ����
			j--; //�������� �̵������Ƿ� j�� ���ҽ�Ų��.
			p_index++; //���� ���������Ƿ�, ��θ� �����ϴ� ����� �� ĭ �̵���Ŵ
		}

		//(i,y)�� ��ġ�� cost��, ��, (i,j)������ �ְ��������� ���� ��ġ (i,j)���� �A ����,  cost�� ���� �밢�� ��(������ ����)�� ���� ��ġ�ϸ�,
		else if (result - arr[i][j] == cost[i - 1][j - 1])
		{
			path[p_index] = arr[i - 1][j - 1];//��ġ�Ѵٴ� ���� �� ���� �����Դٴ� ���̹Ƿ�, ��θ� �����ϴ� �迭 path�� �ش� cost���� �ش��ϴ� ��ġ(i-1,j-1)�� arr��, �� ���� ����� ���� ����
			x[p_index] = i - 1; //x��ǥ����
			y[p_index] = j-1; //y��ǥ����
			result = result - arr[i][j];//���� ��ġ�� ������ ��� ����
			i--; j--;  //���� �밢������ �̵������Ƿ� i,j�� ���ҽ�Ų��.
			p_index++; //���� ���������Ƿ�, ��θ� �����ϴ� ����� �� ĭ �̵���Ŵ
		}

	}

	//��θ� ���
	printf("\n����������: i �� ��, j�� ��\n");
	for (int t = p_index - 2; t >= 0; t--)
	{
		printf("(i = %d, j = %d) : %d->", x[t], y[t], path[t]); //��ǥ,�� ���
	}
	printf("(i = %d, j = %d) : %d ", col-1, col-1, arr[col - 1][col - 1]);
	free(x);
	free(y);
}



int Matrixpath::maximum(int case1, int case2, int case3) // 3���� ����߿� ���� ū ���� �����ϴ� �Լ�
{
	int max;
	max = case1 > case2 ? case1 : case2; //case1�� ���� ���ؼ� ū ���� ����
	max = max > case3 ? max : case3; //�񱳵� ase1�� case2 �� �� ū ���� case3 ��
	return max;
}

//recursion function
int Matrixpath::recursion(int **arr, int **cost, int i, int j, int n, int **count, int *count_i, int *count_j) 
{
	count[i][j]++;//recursion�� ������ ȣ��� ���̹Ƿ�,  ȣ��� Ƚ���� ������Ų��.

	if (i == 0 || j == 0)
	{
		return 0;
	}

	else if (i == 1 && j != 1)
	{
		//i�� 1�϶��°��� ū ���� ���� ���̹Ƿ�, ���ʰ��� �ְ������� ���Ѵ�. 
		int r = arr[i][j] + recursion(arr, cost, i, j - 1, n, count, count_i, count_j);
		if (cost[i][j] == 0) //�ְ������� �����ϴ� ����� cost�� ���� ��ġ������ �ְ������� ������� �ʾ�����, ���� �ְ����� ���� �����Ѵ�. 
		{						//(�̹� ����Ǿ� �ִٸ� , ����Ǿ� �ִ� ���� (���� recursion �� ����Ǿ� maximum�� ���� �ְ������� �Ǵܵ� ���̹Ƿ�, �� ĭ������ ��� �� ���� ū ���̴�. ) �� ū ���̹Ƿ�, 
								//����� �ʴ´�.	
			cost[i][j] = r; //r�� (i,j)������ ����� �ְ�����(cost[i][j] == 0�̹Ƿ�)
		}
		return r; 
	}

	//j�� 1�϶��°��� ū ���� ���� ���̹Ƿ�, ���ʰ��� �ְ������� ���Ѵ�. 
	else if (i != 1 && j == 1)
	{		
		
		int r2 = arr[i][j] + recursion(arr, cost, i-1, j , n, count, count_i, count_j);
		if (cost[i][j] == 0)//�ְ������� �����ϴ� ����� cost�� ���� ��ġ������ �ְ������� ������� �ʾ�����, ���� �ְ����� ���� �����Ѵ�. 
		{
			cost[i][j] = r2;
		}
		return r2;
	}

	//i, j�� 1�϶��°��� ū ���� (1,1)�̹Ƿ�, arr ����� (1,1)���Ҹ� ��ȯ�Ѵ�.
	else if (i == 1 && j == 1)
	{
		
		if (cost[i][j] == 0)
		{
			cost[i][j] = arr[i][j];//�ְ������� �����ϴ� ����� cost�� (1,1)������ ���� ������� �ʾ�����,  �����Ѵ�. 
		}
		return arr[i][j];
	}
	
	else
	{
		//��� Ž�� ���� ����ϴ� �κ� 
		//*�Է��� ���ũ�� n�� 5 �̻��̸�, ����� �ʹ� �������Ƿ�
		// �̺κк���
		//����,����, ���� �밢�� ���� ������ �ְ������� ���Ͽ� �� ū ���� ���簪�� ���� �ְ������� ���Ѵ�. 
		int res = arr[i][j] + maximum(recursion(arr, cost, i - 1, j, n, count, count_i, count_j), recursion(arr, cost, i, j - 1, n, count, count_i, count_j), recursion(arr, cost, i - 1, j - 1, n, count, count_i, count_j));
		if (cost[i][j] == 0)
		{
			
			//�ְ��������� ����Ǵ� ���� ���
			int max = maximum(cost[i - 1][j], cost[i][j - 1], cost[i - 1][j - 1]);
			if (max == cost[i - 1][j] && count_i[i] == 0 && count_j[j] == 0)
			{
				printf("--------------------------------------------------------------------------------------------------------\n");
				printMatrix(cost, n);
				printf("������ �� ĭ�� �ְ������� �� arr[%d][%d]=%d������ ���� %d�� ���� ũ�Ƿ�, ", i - 1, j, arr[i - 1][j], cost[i - 1][j]);
				printf("%d�� �̵�\n", arr[i - 1][j]);
				count_i[i - 1]++; count_j[j]++;
			}

			else if (max == cost[i][j - 1] && count_i[i] == 0 && count_j[j] == 0)
			{
				printf("--------------------------------------------------------------------------------------------------------\n");
				printMatrix(cost, n);
				printf("������ �� ĭ�� �ְ������� �� arr[%d][%d]=%d������ ���� %d�� ���� ũ�Ƿ�, ", i, j - 1, arr[i][j - 1], cost[i][j - 1]);
				printf("%d���� �̵�\n", arr[i][j - 1]);
				count_i[i]++; count_j[j - 1]++;
			}

			else if (max == cost[i - 1][j - 1] && count_i[i] == 0 && count_j[j] == 0)
			{
				printf("--------------------------------------------------------------------------------------------------------\n");
				printMatrix(cost, n);
				printf("������ �� ĭ�� �ְ������� �� arr[%d][%d]=%d������ ���� %d�� ���� ũ�Ƿ� , ", i - 1, j - 1, arr[i - 1][j - 1], cost[i - 1][j - 1]);
				printf("%d���� �̵�\n", arr[i - 1][j - 1]);
				count_i[i - 1]++; count_j[j - 1]++;
			}
			printf("\n");
			//�� �κб����� �ּ�ó���ϰ� �������ּ���(����� �ʹ� ������)
			
			cost[i][j] = res; //�ְ������� �����ϴ� ����� cost�� ���� ��ġ������ �ְ������� ������� �ʾ�����, ���� �ְ����� ���� �����Ѵ�. 
			printf("\n");
		

		}
		return res;
	}

	
}
		

int Matrixpath::dynamic_programming(int **arr, int **cost, int col,int *count_i, int *count_j)
{
	int i, j; // i �� ����� ����, j�� ���� ��Ÿ����.
	

	//3���� ��� �߿� �ְ������� ���ؼ� ���� ����� ���� ���Ѵ�.
	for (int i = 1; i < col; i++)
	{
		for (int j = 1; j < col; j++)
		{
			//����� (1,1)�������� �����ϹǷ�, ó���� ���� �Է����־���Ѵ�.
			if (i == 1 && j == 1)
			{
				cost[i][j] = arr[i][j]; //i,j�� 1�� ���� cost[1][1]�� arr[1][1]���� ����
				if (count_i[i] == 0 && count_j[j] == 0)
				{
					//printf("������ �� ĭ�� �ְ������� �� arr[%d][%d]=%d������ ���� %d�� ���� ũ�Ƿ�, ", i, j - 1, arr[i][j - 1], cost[i][j - 1]);
					printf("%d���\n", arr[i][j]);
					//count_i[i]++; count_j[j]++;
				}
				
			}
			else if (i == 1 && j != 1)
			{
				cost[i][j] = cost[1][j-1] + arr[1][j]; //i�� 1�϶��� cost[1][j]���� ���� ĭ�� �ְ������� ����
				
			}
			else if (i != 1 && j == 1)
			{
				cost[i][j] = cost[i-1][j] + arr[i][1]; //j�� 1�϶��� cost[1][j]���� ���� ĭ�� �ְ������� ����
				
			}

			else
			{			
				cost[i][j] = arr[i][j] + maximum(cost[i - 1][j], cost[i][j - 1], cost[i - 1][j - 1]); //����, ����, ���� �밢�� ���� ���� �ְ������� ���� ū ���� ���� ���� ���� �ְ������� �����.

				//��� Ž�� ���� ����ϴ� �κ� 
				//*�Է��� ���ũ�� n�� 5 �̻��̸�, ����� �ʹ� �������Ƿ�
				// �̺κк���
				//����,����, ���� �밢�� ���� ������ �ְ������� ���Ͽ� �� ū ���� ���簪�� ���� �ְ������� ���Ѵ�. 
				int res = arr[i][j] + maximum(cost[i - 1][j], cost[i][j - 1], cost[i - 1][j - 1]);
				
					
					//�ְ��������� ����Ǵ� ���� ���
					int max = maximum(cost[i - 1][j], cost[i][j - 1], cost[i - 1][j - 1]);
					if (max == cost[i - 1][j] && count_i[i] == 0 && count_j[j] == 0)
					{
						printf("--------------------------------------------------------------------------------------------------------\n");
						printMatrix(cost, col);
						printf("������ �� ĭ�� �ְ������� �� arr[%d][%d]=%d������ ���� %d�� ���� ũ�Ƿ�, ", i - 1, j, arr[i - 1][j], cost[i - 1][j]);
						printf("%d�� �̵�\n", arr[i - 1][j]);
						count_i[i - 1]++; count_j[j]++;
					}

					else if (max == cost[i][j - 1] && count_i[i]==0 && count_j[j]==0)
					{
						printf("--------------------------------------------------------------------------------------------------------\n");
						printMatrix(cost, col);
						printf("������ �� ĭ�� �ְ������� �� arr[%d][%d]=%d������ ���� %d�� ���� ũ�Ƿ�, ", i, j - 1, arr[i][j - 1], cost[i][j - 1]);
						printf("%d���� �̵�\n", arr[i][j - 1]);
						count_i[i]++; count_j[j - 1]++;
					}

					else if (max == cost[i - 1][j - 1] && count_i[i] == 0 && count_j[j] == 0)
					{
						printf("--------------------------------------------------------------------------------------------------------\n");
						printMatrix(cost, col);
						printf("������ �� ĭ�� �ְ������� �� arr[%d][%d]=%d������ ���� %d�� ���� ũ�Ƿ� , ", i - 1, j - 1, arr[i - 1][j - 1], cost[i - 1][j - 1]);
						printf("%d���� �̵�\n", arr[i - 1][j - 1]);
						count_i[i-1]++; count_j[j-1]++;
					}
					printf("\n");
					//�� �κб����� �ּ�ó���ϰ� �������ּ���(����� �ʹ� ������)
				

			}
			

		}
	}
	//���� �ְ����� ���
	printf("\n\n���� �ְ�����: %d\n", cost[col - 1][col - 1]);
	//���� ��θ� ���
	printPath(cost, arr, col,col);
	return cost[col - 1][col - 1];

}

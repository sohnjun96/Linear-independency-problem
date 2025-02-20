// ConsoleApplication4.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>
#include <cmath>
#include <vector>

#include <limits>

using namespace std;

//gauss함수는 input으로 받은 c벡터의 모든 row가 pivot을 가졌는지 판단해 1또는 0반환.
int gauss(vector < vector<double> > c, int NumOfVector) 
{
	double EPS = 1E-9;
	int n = NumOfVector;
	int m = (int)c[0].size();
	vector < vector<double> > a = c; //원 벡터가 변하지 않도록 새 벡터에 Gauss-Jordan 수행.
	int row = 0;
	int col = 0;
	while( row < n && col < m )		//row by row로 col을 pivot으로 left triangle을 제거.
	{
		for(int currentrow = row; currentrow < n ; currentrow++) //row 아래 행 중 가장 큰 행을 row로.
		{
			if(abs(a[currentrow][col]) < EPS)
				continue;
			if(abs(a[currentrow][col])>abs(a[row][col]))
			{
				a[row].swap(a[currentrow]);
			}
		}
		if( abs(a[row][col]) <EPS){			//나눗셈에 의한 작은 수 방지.
			a[row][col] = 0;
			col++;
			continue;
		}
		for(int currentrow=row+1;currentrow < n;currentrow++) //row+1행부터 아래로 소거
		{
			float tmp = a[currentrow][col]/a[row][col];
			for(int currentcol=col; currentcol<m; currentcol++) //col열부터 오른쪽으로 소거.
			{
				if (currentcol == col)
				{
					a[currentrow][currentcol] = 0;
					continue;
				}
				a[currentrow][currentcol] -= a[row][currentcol] * tmp;
				if (abs(a[currentrow][currentcol]) < EPS) {		//작은 수 또 방지
					a[currentrow][currentcol] = 0;
				}
			}
		}
		
		row++;
		col++;
	}

	/*
	printf("---after gauss---\n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			printf("%f ", a[i][j]);
		printf("\n");
	}*/
	int isindependent = 0;
	
	for(int i=0;i<n;i++) //각 row별로 0이 아닌 값이 있는지 체크해 isindependent에 +1.
	{
		int tmp = 0;
		for(int j=0;j<m;j++)
		{
			if(a[i][j] != 0) //잘 돌아갈까... => 잘 돌아간다
				tmp++;
		}
		if(tmp!=0)
			isindependent++;
	}
	if(isindependent == n) //if all rows have at least one non zero value(isindependent = 1), it is independent. -> return 1
		return 1;
	else
		return 0;

}

//input : B, BB, start는 시작점, vertor_space는 끝점, number는 nCr의 r, h는 BB에 저장된 vector의 개수.
int recursive(vector < vector<double> > B, vector < vector<double> > BB,int start, int finish, int number, int h) 
{
	int vector_space = (int)B[0].size();
	if (number == 0)
		return 1;

	for (int extra = start; extra < finish; extra++)
	{
		BB[h] = B[extra];
		if (recursive(B, BB, extra + 1, finish, number - 1, h+1) == 1) //재귀함수 호출.
		{
				cout << "벡터 ";
				for (int ii = 0; ii < h; ii++) {
					for (int z = 0; z < vector_space; z++)
					{
						cout << BB[ii][z] << " ";
					}
					cout << "와 ";
					cout << "벡터 ";
				}
				for (int z = 0; z < vector_space; z++)
				{
					cout << BB[h][z] << " ";
				}
				if (gauss(BB, h + 1))			//gauss함수로 판단.
					cout << "는 독립이다. \n" << endl;
				else
					cout << "는 독립이 아니다. \n" << endl;
		}
		BB.pop_back();
	}
	
}

int main()
{

	printf("입력할 벡터의 개수를 미리 입력해주세요 (m)\n");
	int NumOfVector;
	cin >> NumOfVector;
	int vector_space;
	printf("입력할 벡터의 공간을 미리 입력해주세요 (n)\n");
	cin >> vector_space;

	printf("확인할 벡터를 한칸씩 띄워서 입력해 주세요\n");


	//벡터 초기화
	vector <double> a(vector_space);
	//행렬 만들기
	vector <vector<double>>B(NumOfVector, a);

	for (int i = 0; i < NumOfVector; i++)
	{
		for (int j = 0; j < vector_space; j++)
			cin >> B[i][j];
	}

	vector <double> temp(a.size());

	//ii는 한번에 비교할 vector의 개수로 각 ii마다 nCr = (NumOfVector)C(ii)개의 출력 발생.
	for (int ii = 2; ii <= NumOfVector; ii++) 
	{
		vector <vector<double>>BB(NumOfVector, temp);
		recursive(B, BB, 0, NumOfVector, ii,0);
	}
	
	cin >> NumOfVector; //디버거 정지용.
	return 0;
}
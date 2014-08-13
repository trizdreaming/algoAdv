// C2_1_to_2_4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#define ROW(i) matrixChain[i-1]
#define COL(i) matrixChain[i]

int minMultiplyMatrixChainBottomUpWithCutPos( int* matrixChain, int** cutPos, int chainSize );
void PrintOptimalParenthesis( int **cutPos, int startPoint, int endPoint );
void PrintTable( int** table, int size );

int _tmain( int argc, _TCHAR* argv[] )
{
	int matrixChain[] = { 3, 3, 2, 5, 3 };
	int chainSize = ( sizeof( matrixChain ) / sizeof( matrixChain[0] ) - 1 );

	int** cutPos = new( int*[chainSize] );
	for ( int i = 0; i < chainSize; ++i )
	{
		cutPos[i] = new ( int[chainSize] );
		memset( cutPos[i], 0, sizeof( int )*chainSize );
	}


	int result = minMultiplyMatrixChainBottomUpWithCutPos( matrixChain, cutPos, chainSize );

	//�迭�� 0~3�̹Ƿ� endpoint�� ���� �������� -1��
	PrintOptimalParenthesis( cutPos, 0, chainSize-1 );
	printf_s( "�ּ� ���� Ƚ��: %d", result );


	for ( int i = 0; i < chainSize;++i )
	{
		delete[] cutPos[i];
	}
	delete[] cutPos;

	getchar();
	return 0;
}

int minMultiplyMatrixChainBottomUpWithCutPos( int* matrixChain, int** cutPos, int chainSize )
{
	if ( chainSize == 0 )
	{
		return 0;
	}

	int** resultTable = new ( int*[chainSize] );
	for ( int i = 0; i < chainSize; ++i )
	{
		resultTable[i] = new ( int[chainSize] );
		memset( resultTable[i], 0, sizeof( int )*chainSize );
	}


	for ( int diff = 1; diff < chainSize; ++diff )
	{
		for ( int startPoint = 0; startPoint < chainSize - diff; ++startPoint )
		{
			int endPoint = startPoint + diff;
			printf_s( "%d , %d \n", startPoint, endPoint );
			resultTable[startPoint][endPoint] = resultTable[startPoint + 1][endPoint] + ROW( startPoint + 1 )*COL( startPoint + 1 )*COL( endPoint + 1 );
			cutPos[startPoint][endPoint] = startPoint;

			for ( int endOfFirst = startPoint + 1; endOfFirst < endPoint; ++endOfFirst )
			{
				int cost = resultTable[startPoint][endOfFirst] + resultTable[endOfFirst + 1][endPoint] + ROW( startPoint + 1 )*COL( endOfFirst + 1 )*COL( endPoint + 1 );

				if ( cost < resultTable[startPoint][endPoint] )
				{
					resultTable[startPoint][endPoint] = cost;
					cutPos[startPoint][endPoint] = endOfFirst;
				}
			}



			PrintTable( resultTable, chainSize );
			getchar();
		}
	}

	//�� ���� ��� �������� �ּҰ�
	//�迭������ 0~3�̹Ƿ� ���� �̾Ƽ� return
	int minCost = resultTable[0][chainSize - 1];

	for ( int i = 0; i < chainSize; ++i )
	{
		delete[] resultTable[i];
	}

	delete[] resultTable;


	return minCost;

}

void PrintOptimalParenthesis( int **cutPos, int startPoint, int endPoint )
{
	if (startPoint == endPoint)
	{
		printf_s( "A%d", startPoint );
	}
	else
	{
		printf_s( "(" );
		//�ڸ� �κ��� �������� ���ۺ��� �ڸ� �κб���
		//�ڸ� �κ� ����(+1)���� ������
		PrintOptimalParenthesis( cutPos, startPoint, cutPos[startPoint][endPoint] );
		PrintOptimalParenthesis( cutPos, cutPos[startPoint][endPoint] + 1, endPoint );	
		printf_s( ")" );
	}
}

void PrintTable( int** table, int size )
{
	for ( int i = 0; i < size; ++i )
	{
		for ( int j = 0; j < size; ++j )
		{
			printf_s( "%4d", table[i][j] );
		}
		printf_s( "\n" );
	}
}

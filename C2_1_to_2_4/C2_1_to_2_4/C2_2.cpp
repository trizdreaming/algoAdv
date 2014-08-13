// C2_1_to_2_4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#define ROW(i) matrixChain[i-1]
#define COL(i) matrixChain[i]

int minMultiplyMatrixChainMemoization( int* matrixChain, int startPoint, int endPoint, int** resultArray );

int _tmain( int argc, _TCHAR* argv[] )
{
	int matrixChain[] = { 3, 3, 2, 5, 3 };
	
	//��� ����� �޸� �迭 ����
	//��Ʈ������ 4���̹Ƿ� 5*5 �迭 ����
	int chainSize = sizeof( matrixChain ) / sizeof(matrixChain[0]);
	int** resultArray = new( int*[chainSize] );
	for ( int i = 0; i < chainSize; ++i )
	{
		resultArray[i] = new( int[chainSize] );
		memset( resultArray[i], 0, sizeof( int )*( chainSize ) );
	}

	int result = minMultiplyMatrixChainMemoization( matrixChain, 1, 4, resultArray );

	printf_s( "%d", result );


	//��� ���� �޸� �迭 ����
	for ( int i = 0; i < chainSize - 1; ++i )
	{
		delete[] resultArray[i];
	}
	delete[] resultArray;

	getchar();
	return 0;
}

int minMultiplyMatrixChainMemoization( int* matrixChain, int startPoint, int endPoint, int** resultArray )
{
	int cost;

	if ( resultArray[startPoint][endPoint] != 0)
	{
		return resultArray[startPoint][endPoint];
	}
	
	if ( startPoint == endPoint )
	{
		return 0;
	}

	//�� ��Ʈ���� ü�ο��� ���ü� �ִ� �ִ� ��
	//�ٿ���� ������� ����� �ִ� ��
	resultArray[startPoint][endPoint] = minMultiplyMatrixChainMemoization( matrixChain, startPoint + 1, endPoint, resultArray ) + ROW( startPoint )*COL( startPoint )*COL( endPoint );

	for ( int endOfFirst = startPoint + 1; endOfFirst < endPoint; ++endOfFirst )
	{
		cost = minMultiplyMatrixChainMemoization( matrixChain, startPoint, endOfFirst, resultArray ) + minMultiplyMatrixChainMemoization( matrixChain, endOfFirst + 1, endPoint, resultArray ) + ROW( startPoint )*COL( endOfFirst )*COL( endPoint );

		if ( cost < resultArray[startPoint][endPoint] )
		{
			resultArray[startPoint][endPoint] = cost;
		}
	}
	return resultArray[startPoint][endPoint];
}

// C2_1_to_2_4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#define ROW(i) matrixChain[i-1]
#define COL(i) matrixChain[i]

int minMultiplyMatrixChain( int* matrixChain, int startPoint, int endPoint );

int _tmain(int argc, _TCHAR* argv[])
{
	int matrixChain[] = { 3, 3, 2, 5, 3, 1 };
	
	int result = minMultiplyMatrixChain( matrixChain, 1, 5 );

	printf_s( "%d", result );

	getchar();
	return 0;
}

int minMultiplyMatrixChain( int* matrixChain, int startPoint, int endPoint )
{
	int minCost, cost;

	if (startPoint == endPoint)
	{
		return 0;
	}

	//이 매트릭스 체인에서 나올수 있는 최대 값
	//바운더리 컨디션을 만들어 주는 것
	minCost = minMultiplyMatrixChain( matrixChain, startPoint + 1, endPoint ) + ROW( startPoint )*COL( startPoint )*COL( endPoint );

	for ( int endOfFirst = startPoint + 1; endOfFirst < endPoint; ++endOfFirst )
	{
		cost = minMultiplyMatrixChain( matrixChain, startPoint, endOfFirst ) + minMultiplyMatrixChain( matrixChain, endOfFirst + 1, endPoint ) + ROW( startPoint )*COL( endOfFirst )*COL( endPoint );

		if ( cost < minCost )
		{
			minCost = cost;
		}
	}
	return minCost;
}

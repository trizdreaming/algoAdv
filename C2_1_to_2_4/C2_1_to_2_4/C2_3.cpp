// C2_1_to_2_4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#define ROW(i) matrixChain[i-1]
#define COL(i) matrixChain[i]

int minMultiplyMatrixChainBottomUp( int* matrixChain, int chainSize );
void PrintTable( int** table, int size );

int _tmain( int argc, _TCHAR* argv[] )
{
	int matrixChain[] = { 3, 3, 2, 5, 3 };

	int result = minMultiplyMatrixChainBottomUp( matrixChain, 4 );

	printf_s( "ÃÖ¼Ò °ö¼À È½¼ö: %d", result );

	getchar();
	return 0;
}

int minMultiplyMatrixChainBottomUp( int* matrixChain, int chainSize )
{
	if (chainSize == 0)
	{
		return 0;
	}

	int** resultTable = new ( int*[chainSize] );
	for ( int i = 0; i < chainSize; ++ i )
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

			for ( int endOfFirst = startPoint + 1; endOfFirst < endPoint; ++endOfFirst )
			{
				int cost = resultTable[startPoint][endOfFirst] + resultTable[endOfFirst + 1][endPoint] + ROW( startPoint + 1 )*COL( endOfFirst + 1 )*COL( endPoint + 1 );

				if (cost < resultTable[startPoint][endPoint])
				{
					resultTable[startPoint][endPoint] = cost;
				}
			}

			

			PrintTable( resultTable, chainSize );
			getchar();
		}
	}

	int minCost = resultTable[0][chainSize - 1];

	for ( int i = 0; i < chainSize; ++ i )
	{
		delete[] resultTable[i];
	}

	delete[] resultTable;


	return minCost;

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

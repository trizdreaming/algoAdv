#include "stdafx.h"
#include <iostream>

int RodCutBottomUp( int* pricePerPiece, int totalLen, int* maxPriceTable, int* firstCutsPoint );
void PrintSolution( int* firstCutsPoint, int totalLen );
void TestCode( int* pricePerPiece );

int _tmain( int argc, _TCHAR* argv[] )
{
	int pricePerPiece[11] = { 0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30 };

	//���ϴ� �׽�Ʈ Ƚ ��
	int testCount = 10;

	//�׽�Ʈ ��� ���
	for ( int i = 0; i < testCount; ++i )
	{
		printf_s( "%d��° ���: ", i );
		TestCode( pricePerPiece );
	}


	getchar();
	return 0;
}

int RodCutBottomUp( int* pricePerPiece, int totalLen, int* maxPriceTable, int* CuttingPoint )
{
	int tempValue = 0;
	int subMaxValue = -1;

	maxPriceTable[0] = 0;
	CuttingPoint[0] = 0;

	if ( maxPriceTable[totalLen] != -1 )
	{
		return maxPriceTable[totalLen];
	}

	for ( int firstCutPos = 1; firstCutPos <= totalLen; ++firstCutPos )
	{
		for ( int secondCutPos = 1; secondCutPos <= firstCutPos; ++secondCutPos )
		{
			tempValue = pricePerPiece[secondCutPos] + maxPriceTable[firstCutPos - secondCutPos];

			if ( tempValue > subMaxValue )
			{
				subMaxValue = tempValue;
				CuttingPoint[firstCutPos] = secondCutPos;
			}
		}
		maxPriceTable[firstCutPos] = subMaxValue;
	}

	return maxPriceTable[totalLen];

}

void PrintSolution( int* firstCutsPoint, int totalLen )
{
	int len;

	len = totalLen;
	while ( len > 0 )
	{
		printf_s( "%d, ", firstCutsPoint[len] );
		len -= firstCutsPoint[len];
	}
	printf_s( "\n" );
}

void TestCode( int* pricePerPiece )
{
	int totalLen = rand() % 11;

	int* CuttingPoint = new( int[totalLen + 1] );

	int* maxPriceTable = new ( int[totalLen + 1] );
	for ( int i = 0; i <= totalLen; ++i )
	{
		maxPriceTable[i] = -1;
	}

	int totalPrice = RodCutBottomUp( pricePerPiece, totalLen, maxPriceTable, CuttingPoint );

	std::cout << "Rod ����" << totalLen << ", " << totalPrice << std::endl;
	PrintSolution( CuttingPoint, totalLen );

	delete[] maxPriceTable;
}
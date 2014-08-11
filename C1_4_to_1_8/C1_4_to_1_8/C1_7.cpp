﻿#include "stdafx.h"
#include <iostream>

int RodCutBottomUp( int* pricePerPiece, int totalLen, int* maxPriceTable );
void TestCode( int* pricePerPiece );

int _tmain( int argc, _TCHAR* argv[] )
{
	int pricePerPiece[11] = { 0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30 };
	
	//원하는 테스트 횟 수
	int testCount = 10;

	//테스트 결과 출력
	for ( int i = 0; i < testCount; ++i )
	{
		printf_s( "%d번째 결과: ", i );
		TestCode(pricePerPiece);
	}
	

	getchar();
	return 0;
}

int RodCutBottomUp( int* pricePerPiece, int totalLen, int* maxPriceTable )
{
	int tempValue = 0;
	int subMaxValue = -1;

	maxPriceTable[0] = 0;

	if ( maxPriceTable[totalLen] != -1 )
	{
		return maxPriceTable[totalLen];
	}

	for ( int firstCutPos = 1; firstCutPos <= totalLen; ++firstCutPos )
	{
		for ( int secondCutPos = 1; secondCutPos <= firstCutPos; ++secondCutPos )
		{
			tempValue = pricePerPiece[secondCutPos] + maxPriceTable[firstCutPos - secondCutPos];

			if (tempValue > subMaxValue)
			{
				subMaxValue = tempValue;
			}
		}
		maxPriceTable[firstCutPos] = subMaxValue;
	}
	
	return maxPriceTable[totalLen];
	
}

void TestCode(int* pricePerPiece)
{
	int totalLen = rand() % 11;

	int* maxPriceTable = new ( int[totalLen + 1] );
	for ( int i = 0; i <= totalLen; ++i )
	{
		maxPriceTable[i] = -1;
	}

	int totalPrice = RodCutBottomUp( pricePerPiece, totalLen, maxPriceTable );

	std::cout << "Rod 길이" << totalLen << ", " << totalPrice << std::endl;

	delete[] maxPriceTable;
}
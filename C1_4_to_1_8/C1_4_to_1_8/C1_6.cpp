#include "stdafx.h"
#include <iostream>

int TableRecordedRecursiveRodCut( int* pricePerPiece, int totalLen, int* maxPriceTable );

int _tmain( int argc, _TCHAR* argv[] )
{
	int pricePerPiece[11] = { 0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30 };
	int totalLen = 4;

	int* maxPriceTable = new int[totalLen + 1];

	for ( int i = 0; i <= totalLen; ++i )
	{
		maxPriceTable[i] = -1;
	}
	int totalPrice = TableRecordedRecursiveRodCut( pricePerPiece, totalLen, maxPriceTable );

	std::cout << totalPrice << std::endl;

	delete[] maxPriceTable;

	getchar();
	return 0;
}

int TableRecordedRecursiveRodCut( int* pricePerPiece, int totalLen, int* maxPriceTable )
{
	int maxPrice = -1;
	int processPrice = 0;

	if ( maxPriceTable[totalLen] != -1 )
	{
		return maxPriceTable[totalLen];
	}

	if ( totalLen == 0 )
	{
		return 0;
	}

	for ( int precedentPiece = 1; precedentPiece <= totalLen; ++precedentPiece )
	{
		processPrice = pricePerPiece[precedentPiece] + TableRecordedRecursiveRodCut( pricePerPiece, totalLen - precedentPiece, maxPriceTable );

		if ( processPrice > maxPrice )
		{
			maxPrice = processPrice;
		}
	}

	maxPriceTable[totalLen] = maxPrice;

	return maxPrice;
}
#include "stdafx.h"
#include <iostream>

int MiniRecursiveRodCut( int* pricePerPiece, int totalLen );

int _tmain( int argc, _TCHAR* argv[] )
{
	int pricePerPiece[11] = { 0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30 };

	int totalLen = 4;

	int maxPrice = MiniRecursiveRodCut( pricePerPiece, totalLen );

	std::cout << maxPrice << std::endl;

	getchar();
	return 0;
}

int MiniRecursiveRodCut( int* pricePerPiece, int totalLen )
{
	int maxPrice = -1;
	int processPrice = 0;

	if (totalLen == 0)
	{
		return 0;
	}

	for ( int precedentPiece = 1; precedentPiece <= totalLen; ++precedentPiece )
	{
		processPrice = pricePerPiece[precedentPiece] + MiniRecursiveRodCut( pricePerPiece, totalLen - precedentPiece );

		if ( processPrice > maxPrice )
		{
			maxPrice = processPrice;
		}
	}
	return maxPrice;
}
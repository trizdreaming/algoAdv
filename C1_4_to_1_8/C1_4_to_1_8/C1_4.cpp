// C1_4_to_1_8.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>


void RecursiveRodCut( int totalLen, int cutlinePos, int* posCutStatus, int* pricePerPiece, int* maxPrice );
int PriceCalculator( int totalLen, int* posCutStatus, int* pricePerPiece );

int _tmain(int argc, _TCHAR* argv[])
{
	int pricePerPiece[11] = { 0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30 };
	
	//lod length value
	int totalLen = 4;
	int* posCutStatus = new ( int[totalLen] );


	for ( int i = 0; i < totalLen; ++i )
	{
		posCutStatus[i] = 0;
	}

	int totalPrice = 0;
	RecursiveRodCut( totalLen, 1, posCutStatus, pricePerPiece, &totalPrice );

	std::cout << totalPrice << std::endl;
	
	delete[] posCutStatus;

	getchar();
	return 0;
}

void RecursiveRodCut( int totalLen, int cutlinePos, int* posCutStatus, int* pricePerPiece, int* maxPrice )
{
	if ( cutlinePos == totalLen )
	{
		int totalPrice = PriceCalculator( totalLen, posCutStatus, pricePerPiece );

		if (totalPrice > *maxPrice)
		{
			*maxPrice = totalPrice;
		}
	}
	else
	{
		posCutStatus[cutlinePos] = 0;
		RecursiveRodCut( totalLen, cutlinePos + 1, posCutStatus, pricePerPiece, maxPrice );

		posCutStatus[cutlinePos] = 1;
		RecursiveRodCut( totalLen, cutlinePos + 1, posCutStatus, pricePerPiece, maxPrice );
	}
}

int PriceCalculator(int totalLen, int* posCutStatus, int* pricePerPiece)
{
	int prevCutPos = 0;
	int totalPrice = 0;

	for ( int i = 1; i < totalLen; ++i )
	{
		if ( posCutStatus[i] == 1 )
		{
			totalPrice += pricePerPiece[i - prevCutPos];
			prevCutPos = i;
		}
	}

	totalPrice += pricePerPiece[totalLen - prevCutPos];

	return totalPrice;
}
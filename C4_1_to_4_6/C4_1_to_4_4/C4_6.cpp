// C4_1_to_4_4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>

#define _MAX(x, y) ((x > y)? x : y)

typedef struct ITEM
{
	int weight;
	int value;
} item_t;

void MakeItemList( int start, int end, std::vector<item_t*>& stolenItem );
int KnapsackBottomUp( std::vector<item_t*>& stolenItem, int itemNum, int packSize );

int _tmain( int argc, _TCHAR* argv[] )
{
	std::vector<item_t*>* stolenItem = new std::vector < item_t* >;

	//ItemList 제작 함수
	MakeItemList( 10, 60, *stolenItem );
	MakeItemList( 20, 100, *stolenItem );
	MakeItemList( 30, 120, *stolenItem );


	//////////////////////////////////////////////////////////////////////////
	//본 코드
	int maxValue = KnapsackBottomUp( *stolenItem, stolenItem->size(), 50 );

	printf_s( "%d\n", maxValue );

	//////////////////////////////////////////////////////////////////////////
	//ItemList 제거 함수
	for ( auto& iter : *stolenItem )
	{
		auto toBeDelete = iter;

		if ( toBeDelete != nullptr )
		{
			delete toBeDelete;
			toBeDelete = nullptr;
		}
	}

	delete stolenItem;


	getchar();
	return 0;
}

int KnapsackBottomUp( std::vector<item_t*>& stolenItem, int itemNum, int packSize )
{
	int** resultTable = new ( int*[itemNum + 1] );
	for ( int i = 0; i <= itemNum; ++i )
	{
		resultTable[i] = new ( int[packSize + 1] );
		memset( resultTable[i], 0, sizeof( int )*packSize + 1 );
	}


	for ( int num = 1; num <= itemNum; ++num )
	{
		for ( int capa = 1; capa <= packSize; ++capa)
		{
			if ( stolenItem[num-1]->weight > packSize )
			{
				resultTable[num][capa] = 0;
			}
			else
			{
				resultTable[num][capa] = _MAX( resultTable[num - 1][capa], resultTable[num - 1][capa - stolenItem[num - 1]->weight] + stolenItem[num - 1]->value );
			}
		}
	}

	int maxValue = resultTable[itemNum][packSize];

	for ( int i = 0; i <+itemNum; ++i )
	{
		delete[] resultTable[i];
	}

	delete[] resultTable;


	return maxValue;
}

void MakeItemList( int weight, int value, std::vector<item_t*>& stolenItem )
{
	item_t* tempItem = new item_t;
	tempItem->weight = weight;
	tempItem->value = value;

	stolenItem.push_back( tempItem );
}

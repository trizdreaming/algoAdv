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
int KnapsackRecursion( std::vector<item_t*>& stolenItem, int itemNum, int packSize );

int _tmain( int argc, _TCHAR* argv[] )
{
	std::vector<item_t*>* stolenItem = new std::vector < item_t* > ;

	//ItemList 제작 함수
	MakeItemList( 10, 60, *stolenItem );
	MakeItemList( 20, 100, *stolenItem );
	MakeItemList( 30, 120, *stolenItem );


	//////////////////////////////////////////////////////////////////////////
	//본 코드
	int maxValue = KnapsackRecursion( *stolenItem, stolenItem->size(), 50 );

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

int KnapsackRecursion( std::vector<item_t*>& stolenItem, int itemNum, int packSize )
{
	if (itemNum <= 0 || packSize <= 0)
	{
		return 0;
	}

	if (stolenItem[itemNum-1]->weight > packSize)
	{
		return KnapsackRecursion( stolenItem, itemNum - 1, packSize );
	}
	else
	{
		return _MAX( KnapsackRecursion( stolenItem, itemNum - 1, packSize ), KnapsackRecursion( stolenItem, itemNum - 1, packSize - stolenItem[itemNum - 1]->weight ) + stolenItem[itemNum - 1]->value  );
	}
}


//그냥 입력인자를 받아 item 리스트로 만들어 줌
//마지막 인자를 기준으로 오름차순 정렬은?! C4_5 정렬 적용
void MakeItemList( int weight, int value, std::vector<item_t*>& stolenItem )
{
	item_t* tempItem = new item_t;
	tempItem->weight = weight;
	tempItem->value = value;

	stolenItem.push_back( tempItem );


	//테스트 결과 잘 되네 
	for ( auto& iter = stolenItem.begin(); iter != stolenItem.end(); ++iter )
	{
		printf_s( "%d  ", ( *iter )->value );
	}

	printf_s( "\n" );
}

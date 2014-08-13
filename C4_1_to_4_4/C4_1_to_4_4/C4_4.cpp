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

void InsertActivityTable( int start, int end, std::vector<item_t*>& stolenItem );
int KnapsackRecursion( std::vector<item_t*>& stolenItem, int itemNum, int packSize );

int _tmain( int argc, _TCHAR* argv[] )
{
	std::vector<item_t*>* stolenItem = new std::vector < item_t* > ;

	//actTable 제작 함수
	InsertActivityTable( 10, 60, *stolenItem );
	InsertActivityTable( 20, 100, *stolenItem );
	InsertActivityTable( 30, 120, *stolenItem );


	//////////////////////////////////////////////////////////////////////////
	//본 코드
	int maxValue = KnapsackRecursion( *stolenItem, stolenItem->size(), 50 );

	printf_s( "%d\n", maxValue );

	//////////////////////////////////////////////////////////////////////////
	//actTable 제거 함수
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


//종료 값 비교를 통해 오름차순 list로 만들어 주는 함수
void InsertActivityTable( int weight, int value, std::vector<item_t*>& stolenItem )
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

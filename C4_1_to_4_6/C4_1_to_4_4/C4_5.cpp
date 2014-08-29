// C4_1_to_4_4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>

typedef struct ITEM
{
	int weight;
	int value;
	int density;
} item_t;

void MakeItemList( int start, int end, std::vector<item_t*>& stolenItem );
float FracKnapsack( std::vector<item_t*>& stolenItem, int itemNum, int packSize );
void PrintItemList( std::vector<item_t*>& stolenItem );
void SortBasedDensity( std::vector<item_t*>& stolenItem );

//������ ���� ���� ������ �غ�
struct DensityCompare
{
	bool operator()( ITEM*& item1, ITEM*& item2 )
	{
		return item1->density > item2->density;
	}
};

int _tmain( int argc, _TCHAR* argv[] )
{
	std::vector<item_t*>* stolenItem = new std::vector < item_t* >;

	//ItemList ���� �Լ�
	MakeItemList( 20, 100, *stolenItem );
	MakeItemList( 30, 120, *stolenItem );
	MakeItemList( 10, 60, *stolenItem );


	//////////////////////////////////////////////////////////////////////////
	//�� �ڵ�
	float maxValue = FracKnapsack( *stolenItem, stolenItem->size(), 50 );

	printf_s( "%f\n", maxValue );

	//////////////////////////////////////////////////////////////////////////
	//ItemList ���� �Լ�
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

void SortBasedDensity( std::vector<item_t*>& stolenItem )
{
	//���� ���� Ȯ�ο� ����Ʈ ��
	std::cout << "���� ��" << std::endl;
	PrintItemList( stolenItem );

	std::sort( stolenItem.begin(), stolenItem.end(), DensityCompare() );

	std::cout << "���� ��" << std::endl;
	PrintItemList( stolenItem );
}

void PrintItemList( std::vector<item_t*>& stolenItem )
{
	for ( auto& iter = stolenItem.begin(); iter != stolenItem.end(); ++iter )
	{
		std::cout << ( *iter )->density << "||";
	}
	std::cout << std::endl;
}

float FracKnapsack( std::vector<item_t*>& stolenItem, int itemNum, int packSize )
{
	float value = 0;

	//density ä��� ��
	for ( auto& iter = stolenItem.begin(); iter != stolenItem.end(); ++iter )
	{
		( *iter )->density = ( *iter )->value / ( *iter )->weight;
	}

	//density �������� �������� ���� �Լ�
	SortBasedDensity( stolenItem );

	for ( int id = 0; id < itemNum; ++id )
	{
		if ( packSize > stolenItem[id]->weight )
		{
			value += stolenItem[id]->value;
			packSize -= stolenItem[id]->weight;
		}
		else
		{
			value += stolenItem[id]->density * packSize;
			break;
		}
	}

	return value;
}



void MakeItemList( int weight, int value, std::vector<item_t*>& stolenItem )
{
	item_t* tempItem = new item_t;
	tempItem->weight = weight;
	tempItem->value = value;

	stolenItem.push_back( tempItem );
}

// C4_1_to_4_4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>

#define _MAX(x, y) ((x > y)? x : y)

typedef struct ACT
{
	int startTime;
	int endTime;
} act_t;

void InsertActivityTable( int start, int end, std::vector<act_t*>& actTable );
int ActivitySelectionWithIterGreedy( std::vector<act_t*>& actTable, int actTableSize );

int _tmain( int argc, _TCHAR* argv[] )
{
	std::vector<act_t*>* actTable = new std::vector < act_t* > ;

	//actTable ���� �Լ�
	InsertActivityTable( 1, 4, *actTable );
	InsertActivityTable( 3, 5, *actTable );
	InsertActivityTable( 0, 6, *actTable );
	InsertActivityTable( 5, 7, *actTable );
	InsertActivityTable( 3, 9, *actTable );
	InsertActivityTable( 5, 9, *actTable );
	InsertActivityTable( 6, 10, *actTable );
	InsertActivityTable( 8, 11, *actTable );
	InsertActivityTable( 8, 12, *actTable );
	InsertActivityTable( 2, 14, *actTable );
	InsertActivityTable( 12, 16, *actTable );



	//////////////////////////////////////////////////////////////////////////
	//�� �ڵ�
	int result = ActivitySelectionWithIterGreedy( *actTable, actTable->size() );

	printf_s( "%d \n", result );


	//////////////////////////////////////////////////////////////////////////
	//actTable ���� �Լ�
	for ( auto& iter : *actTable )
	{
		auto toBeDelete = iter;

		if ( toBeDelete != nullptr )
		{
			delete toBeDelete;
			toBeDelete = nullptr;
		}
	}

	delete actTable;


	getchar();
	return 0;
}

int ActivitySelectionWithIterGreedy( std::vector<act_t*>& actTable, int actTableSize )
{
	//��Ե� ù ��°�� �ϴϱ� �̹� �ϳ��� �� �� ġ��
	int maxNum = 1, lastInsertedActId = 0;

	if ( actTableSize <= 0 )
	{
		return 0;
	}

	for ( int nextId = 1; nextId < actTableSize; ++nextId )
	{
		if (actTable[nextId]->startTime >= actTable[lastInsertedActId]->endTime)
		{
			++maxNum;
			lastInsertedActId = nextId;
		}
	}

	return maxNum;
}


//���� �� �񱳸� ���� �������� list�� ����� �ִ� �Լ�
void InsertActivityTable( int start, int end, std::vector<act_t*>& actTable )
{
	act_t* tempAct = new act_t;
	tempAct->startTime = start;
	tempAct->endTime = end;

	actTable.push_back( tempAct );


	//�׽�Ʈ ��� �� �ǳ� 
	for ( auto& iter = actTable.begin(); iter != actTable.end(); ++iter )
	{
		printf_s( "%d  ", ( *iter )->endTime );
	}

	printf_s( "\n" );
}

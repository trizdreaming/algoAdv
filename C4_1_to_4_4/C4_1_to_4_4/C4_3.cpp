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

	//actTable 제작 함수
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
	//본 코드
	int result = ActivitySelectionWithIterGreedy( *actTable, actTable->size() );

	printf_s( "%d \n", result );


	//////////////////////////////////////////////////////////////////////////
	//actTable 제거 함수
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
	//어떻게든 첫 번째는 하니깐 이미 하나는 한 셈 치자
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


//종료 값 비교를 통해 오름차순 list로 만들어 주는 함수
void InsertActivityTable( int start, int end, std::vector<act_t*>& actTable )
{
	act_t* tempAct = new act_t;
	tempAct->startTime = start;
	tempAct->endTime = end;

	actTable.push_back( tempAct );


	//테스트 결과 잘 되네 
	for ( auto& iter = actTable.begin(); iter != actTable.end(); ++iter )
	{
		printf_s( "%d  ", ( *iter )->endTime );
	}

	printf_s( "\n" );
}

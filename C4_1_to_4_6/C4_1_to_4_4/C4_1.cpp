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
int ActivitySelectionRecusion1( std::vector<act_t*>& actTable, int startPoint, int endPoint, int startTime, int endTime );
int ActivitySelectionRecusion2( std::vector<act_t*>& actTable, int startTime, int endTime, int actTableSize );

int _tmain(int argc, _TCHAR* argv[])
{
	std::vector<act_t*>* actTable = new std::vector<act_t*>;

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

	int result1 = ActivitySelectionRecusion1( *actTable, 0, actTable->size()-1, 0, (*actTable)[10]->endTime );

	printf_s( "%d \n", result1 );

 	int result2 = ActivitySelectionRecusion2( *actTable, 0, (*actTable)[10] ->endTime, actTable->size() );

	printf_s( "%d \n", result2 );

	//////////////////////////////////////////////////////////////////////////
	//actTable 제거 함수
	for (auto& iter: *actTable)
	{
		auto toBeDelete = iter;
		
		if (toBeDelete != nullptr)
		{
			delete toBeDelete;
			toBeDelete = nullptr;
		}
	}

	delete actTable;


	getchar();
	return 0;
}

int ActivitySelectionRecusion1( std::vector<act_t*>& actTable, int startPoint, int endPoint, int startTime, int endTime )
{
	int maxNumOfAct = 0;

	if ( startPoint > endPoint )
	{
		return 0;
	}

	//printf_s( "%d", actTable[0]->startTime );

	if (startPoint == endPoint)
	{
		if (actTable[startPoint]->startTime >= startTime && actTable[startPoint]->endTime <= endTime)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}

	for ( int point = startPoint; point <= endPoint; ++point )
	{
		maxNumOfAct = _MAX(maxNumOfAct, ActivitySelectionRecusion1(actTable, startPoint, point-1, startTime, actTable[point]->startTime ) 
							+ ActivitySelectionRecusion1(actTable, point+1, endPoint, actTable[point]->endTime, endTime) 
							+ ActivitySelectionRecusion1(actTable, point, point, startTime, endTime));
	}
	//printf_s( "%d \n", maxNumOfAct );
	return maxNumOfAct;
}



int ActivitySelectionRecusion2( std::vector<act_t*>& actTable, int startTime, int endTime, int actTableSize )
{
	if ( startTime > endTime )
	{
		return 0;
	}

	int tempMaxCount=0, maxCount = 0;

	for ( int i = 0; i < actTableSize; ++i )
	{
		if ( actTable[i]->startTime >= startTime && actTable[i]->endTime <= endTime )
		{
			tempMaxCount = 1 + ActivitySelectionRecusion2( actTable, startTime, actTable[i]->startTime, actTableSize ) + ActivitySelectionRecusion2( actTable, actTable[i]->endTime, endTime, actTableSize );
		}

		if ( tempMaxCount > maxCount )
		{
			maxCount = tempMaxCount;
		}
	}
	return maxCount;
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

// C3_5_to_3_6.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <float.h>
#include <memory.h>


float OptimalBSTRecur( float* pi, float* qi, int sId, int eId, int depth );
float OptimalBSTMemo( float* pi, float* qi, int sId, int eId, int depth, float** resultTable );
float OptimalBSTBottomUp( float* pi, float* qi, int eId, float** resultTable, float** depthTable, int** rootTable );

int _tmain(int argc, _TCHAR* argv[])
{
	float pi[] = { 0.0f, 0.15f, 0.10f, 0.05f, 0.10f, 0.20f };
	float qi[] = { 0.05f, 0.10f, 0.05f, 0.05f, 0.05f, 0.10f };

	float result1 = OptimalBSTRecur( pi, qi, 1, 5, 1 );

	printf_s( "recursive: %f\n", result1 );

	int tableSize = sizeof( pi ) / sizeof( float );

	float** resultTable = new float*[tableSize + 1];
	for ( int i = 0; i <= tableSize; ++i )
	{
		resultTable[i] = new float[tableSize + 1];
		//float는 이렇게 저장하면 오류 값
		//memset( resultTable[i], -1, sizeof( float )*(tableSize + 1) );
	}

	for ( int i = 0; i <= tableSize; ++i )
	{
		for ( int j = 0; j <= tableSize; ++j )
		{
			resultTable[i][j] = -1.0f;
		}
	}


	float result2 = OptimalBSTMemo(pi, qi, 1, 5, 1, resultTable);

	printf_s( "Memo: %f\n", result2 );


	//resultTable 다시 초기화(재사용)
	for ( int i = 0; i <= tableSize; ++i )
	{
		for ( int j = 0; j <= tableSize; ++j )
		{
			resultTable[i][j] = -1.0f;
		}
	}


	float** depthTable = new float*[tableSize + 1];
	for ( int i = 0; i <= tableSize; ++i )
	{
		depthTable[i] = new float[tableSize + 1];
	}

	for ( int i = 0; i <= tableSize; ++i )
	{
		for ( int j = 0; j <= tableSize; ++j )
		{
			depthTable[i][j] = 0.0f;
		}
	}

	int** rootTable = new int*[tableSize];
	for ( int i = 0; i < tableSize; ++i )
	{
		rootTable[i] = new int[tableSize];
	}

	for ( int i = 0; i < tableSize; ++i )
	{
		for ( int j = 0; j < tableSize; ++j )
		{
			rootTable[i][j] = 0;
		}
	}


	float result3 = OptimalBSTBottomUp( pi, qi, 5, resultTable, depthTable, rootTable );

	printf_s( "BottomUp: %f\n", result3 );
	

	//////////////////////////////////////////////////////////////////////////
	//자원 해제 부
	//////////////////////////////////////////////////////////////////////////
	for ( int i = 0; i < tableSize; ++i )
	{
		delete[] rootTable[i];
	}
	delete[] rootTable;

	for ( int i = 0; i <= tableSize; ++i )
	{
		delete[] depthTable[i];
	}
	delete[] depthTable;

	for ( int i = 0; i <= tableSize; ++i )
	{
		delete[] resultTable[i];
	}
	delete[] resultTable;

	getchar();
	return 0;
}

float OptimalBSTRecur( float* pi, float* qi, int sId, int eId, int depth )
{

	if (sId -1 == eId)
	{
		return depth * qi[eId];
	}
	
	float minVal = FLT_MAX;
	
	for ( int root = sId; root <= eId; ++ root )
	{
		float temp = depth * pi[root] + OptimalBSTRecur( pi, qi, sId, root - 1, depth + 1 ) + OptimalBSTRecur( pi, qi, root + 1, eId, depth + 1 );

		if ( minVal > temp )
		{
			minVal = temp;
		}
	}

	//검색 기대값 리턴
	return minVal;
}

float OptimalBSTMemo(float* pi, float* qi, int sId, int eId, int depth, float** resultTable)
{
	if (resultTable[sId][eId] != -1.0f)
	{
		return resultTable[sId][eId];
	}

	if (sId -1 == eId)
	{
		resultTable[sId][eId] = depth* qi[eId];
		return resultTable[sId][eId];
	}

	float minVal = FLT_MAX;
	
	for ( int root = sId; root <= eId; ++root )
	{
		float temp = depth * pi[root] + OptimalBSTMemo( pi, qi, sId, root - 1, depth + 1, resultTable ) + OptimalBSTMemo( pi, qi, root + 1, eId, depth + 1, resultTable );

		if (minVal > temp)
		{
			minVal = temp;
		}
	}

	resultTable[sId][eId] = minVal;

	return minVal;
}

float OptimalBSTBottomUp(float* pi, float* qi, int eId, float** resultTable, float** depthTable, int** rootTable )
{
	for ( int i = 1; i <= eId + 1; ++i )
	{
		resultTable[i][i - 1] = qi[i - 1];
		depthTable[i][i - 1] = qi[i - 1];
	}

	for ( int subLen = 1; subLen <= eId; ++ subLen )
	{
		for ( int subStartId = 1; subStartId <= eId - subLen + 1; ++subStartId )
		{
			int subEndId = subStartId + subLen - 1;
			resultTable[subStartId][subEndId] = FLT_MAX;
			depthTable[subStartId][subEndId] = depthTable[subStartId][subEndId - 1] + pi[subEndId] + qi[subEndId];

			for ( int root = subStartId; root <= subEndId; ++ root )
			{
				float temp = resultTable[subStartId][root - 1] + resultTable[root + 1][subEndId] + depthTable[subStartId][subEndId];

				if (resultTable[subStartId][subEndId]>temp)
				{
					resultTable[subStartId][subEndId] = temp;
					rootTable[subStartId][subEndId] = root;
				}
			}
		}
	}


	return resultTable[1][eId];
}
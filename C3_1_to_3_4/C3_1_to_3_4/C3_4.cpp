// C3_1_to_3_4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#define _MAX(x,y) ((x>y)? x : y)

enum COMPARESTATUS
{
	STATUS_NONE,

	BOTH,
	STR1,
	STR2,

	STATUS_MAX
};

int LcsBottomUpWithResult( std::string& str1, std::string& str2, int** seqResultTable );
void PrintLcs( std::string& str1, int str1Len, std::string& str2, int str2Len, int** seqResultTable );

int _tmain( int argc, _TCHAR* argv[] )
{
	std::string x = "abcbdab";
	std::string y = "bdcaba";

	int** seqResultTable = new( int*[x.length() + 1] );
	for ( unsigned int i = 0; i < x.length() + 1; ++i )
	{
		seqResultTable[i] = new ( int[y.length() + 1] );
		memset( seqResultTable[i], 0, sizeof( int )*( y.length() + 1 ) );
	}


	int resultLcs = LcsBottomUpWithResult( x, y, seqResultTable );

	printf_s( "%d\n", resultLcs );
	PrintLcs( x, x.length(), y, y.length(), seqResultTable );

	for ( unsigned int i = 0; i < x.length() + 1; ++i )
	{
		delete[] seqResultTable[i];
	}
	delete[] seqResultTable;

	getchar();
	return 0;

	return 0;
}

int LcsBottomUpWithResult( std::string& str1, std::string& str2, int** seqResultTable )
{
	int** resultTable = new( int*[str1.length() + 1] );
	for ( unsigned int i = 0; i < str1.length() + 1; ++i )
	{
		resultTable[i] = new ( int[str2.length() + 1] );
		memset( resultTable[i], 0, sizeof( int )*( str2.length() + 1 ) );
	}

	for ( unsigned int str1SubLen = 1; str1SubLen <= str1.length(); ++str1SubLen )
	{
		for ( unsigned int str2SubLen = 1; str2SubLen <= str2.length(); ++str2SubLen )
		{
			//0번재 문자열부터 비교해야하기 때문에 -1을 하는 것
			//문자열은 0 ~ length-1까지 
			//length 는 \0 임
			if ( str1[str1SubLen - 1] == str2[str2SubLen - 1] )
			{
				resultTable[str1SubLen][str2SubLen] = resultTable[str1SubLen - 1][str2SubLen - 1] + 1;
				seqResultTable[str1SubLen][str2SubLen] = BOTH;
			}
			else
			{
				//resultTable[str1SubLen][str2SubLen] = _MAX( resultTable[str1SubLen - 1][str2SubLen], resultTable[str1SubLen][str2SubLen - 1] );
				//원래 문장을 둘로 정확히 나눠야 함

				if ( resultTable[str1SubLen - 1][str2SubLen] >= resultTable[str1SubLen][str2SubLen - 1] )
				{
					resultTable[str1SubLen][str2SubLen] = resultTable[str1SubLen - 1][str2SubLen];
					seqResultTable[str1SubLen][str2SubLen] = STR1;
				}
				else
				{
					resultTable[str1SubLen][str2SubLen] = resultTable[str1SubLen][str2SubLen - 1];
					seqResultTable[str1SubLen][str2SubLen] = STR2;
				}

			}
		}
	}

	int lcsLen = resultTable[str1.length()][str2.length()];

	//결과 테이블 출력 코드
	for ( unsigned int i = 0; i <= str1.length(); ++i )
	{
		for ( unsigned int j = 0; j <= str2.length(); ++j )
		{
			printf_s( "%2d", resultTable[i][j] );
		}
		printf_s( "\n" );
	}

	printf_s( "////////////////////////////\n" );

	for ( unsigned int i = 0; i <= str1.length(); ++i )
	{
		for ( unsigned int j = 0; j <= str2.length(); ++j )
		{
			printf_s( "%2d", seqResultTable[i][j] );
		}
		printf_s( "\n" );
	}

	printf_s( "////////////////////////////\n" );

	for ( unsigned int i = 0; i < str1.length() + 1; ++i )
	{
		delete[] resultTable[i];
	}
	delete[] resultTable;


	return lcsLen;
}

void PrintLcs( std::string& str1, int str1Len, std::string& str2, int str2Len, int** seqResultTable )
{
	if (str1Len == 0 || str2Len == 0)
	{
		return;
	}

	switch ( seqResultTable[str1Len][str2Len] )
	{
		case BOTH:
			PrintLcs( str1, str1Len - 1, str2, str2Len - 1, seqResultTable );
			printf_s( "%c", str1[str1Len - 1] );
			break;
		case STR1:
			PrintLcs( str1, str1Len - 1, str2, str2Len, seqResultTable );
			break;
		case STR2:
			PrintLcs( str1, str1Len, str2, str2Len - 1, seqResultTable );
		default:
			break;
	}
}

// C3_1_to_3_4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#define _MAX(x,y) ((x>y)? x : y)

int LcsBottomUp( std::string& str1, std::string& str2 );

int _tmain( int argc, _TCHAR* argv[] )
{
	std::string x = "abcbdab";
	std::string y = "bdcaba";

	//printf_s( "%c", x[1] );

	int resultLcs = LcsBottomUp( x, y );

	printf_s( "%d\n", resultLcs );

	getchar();
	return 0;
}

int LcsBottomUp( std::string& str1, std::string& str2 )
{
	//이런 꼼수는 좋지 않은 걸로
	//원래는 첫자리에 한개씩 늘리려고 했었다
// 	str1.insert( 0, "0" );
// 	str2.insert( 0, "0" );
// 
// 	printf_s( "%s\n", str1.c_str() );
// 	printf_s( "%s\n", str2.c_str() );

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
			if (str1[str1SubLen-1] == str2[str2SubLen-1])
			{
				resultTable[str1SubLen][str2SubLen] = resultTable[str1SubLen - 1][str2SubLen - 1] + 1;
			}
			else
			{
				resultTable[str1SubLen][str2SubLen] = _MAX(resultTable[str1SubLen-1][str2SubLen], resultTable[str1SubLen][str2SubLen-1]);
			}
		}
	}

	int lcsLen = resultTable[str1.length()][str2.length()];

	//결과 테이블 출력 코드
	for ( int i = 0; i <= str1.length(); ++i )
	{
		for ( int j = 0; j <= str2.length(); ++j )
		{
			printf_s( "%2d", resultTable[i][j] );
		}
		printf_s( "\n" );
	}

	for ( unsigned int i = 0; i < str1.length() + 1; ++i )
	{
		delete[] resultTable[i];
	}
	delete[] resultTable;


	return lcsLen;
}



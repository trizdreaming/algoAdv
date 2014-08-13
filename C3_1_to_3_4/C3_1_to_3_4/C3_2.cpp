// C3_1_to_3_4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#define _MAX(x,y) ((x>y)? x : y)

int LcsMemoiztion( std::string str1, int str1SubLen, std::string str2, int str2SubLen, int** resultTable );

int _tmain( int argc, _TCHAR* argv[] )
{
	std::string x = "abcbdab";
	std::string y = "bdcaba";

	int** resultTable = new( int*[x.length()+1] );
	for ( unsigned int i = 0; i < x.length() + 1; ++i )
	{
		resultTable[i] = new ( int[y.length() + 1] );
		memset( resultTable[i], -1, sizeof( int )*( y.length() + 1 ) );
	}

	int lcsLen = LcsMemoiztion( x, x.length(), y, y.length(), resultTable );

	printf_s( "%d \n", lcsLen );

	
	for (unsigned int i = 0; i < x.length() + 1; ++i )
	{
		delete[] resultTable[i];
	}
	delete[] resultTable;

	getchar();
	return 0;
}

int LcsMemoiztion( std::string& str1, int str1SubLen, std::string& str2, int str2SubLen, int** resultTable )
{
	int lcsLen;

	if (resultTable[str1SubLen][str2SubLen] != -1)
	{
		return resultTable[str1SubLen][str2SubLen];
	}

	if (str1SubLen == 0 || str2SubLen == 0)
	{
		return 0;
	}

	if (str1[str1SubLen] == str2[str2SubLen])
	{
		lcsLen = LcsMemoiztion( str1, str1SubLen - 1, str2, str2SubLen - 1, resultTable ) + 1;
	}
	else
	{
		lcsLen = _MAX( LcsMemoiztion( str1, str1SubLen - 1, str2, str2SubLen, resultTable ), LcsMemoiztion( str1, str1SubLen, str2, str2SubLen - 1, resultTable ) );
	}

	resultTable[str1SubLen][str2SubLen] = lcsLen;

	return lcsLen;
}
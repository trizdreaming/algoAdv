// C3_1_to_3_4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#define _MAX(x,y) ((x>y)? x : y)

int Lcs( std::string &str1, int str1SubLen, std::string &str2, int str2SubLen, char* subsequence );

int _tmain(int argc, _TCHAR* argv[])
{
	std::string x = "abcbdab";
	std::string y = "bdcaba";

	char* subsequence = new (char[x.length()+1]);
	memset( subsequence, 0, sizeof( char )* x.length() );

	int lcsLen = Lcs( x, x.length(), y, y.length(), subsequence );

	printf_s( "%d \n", lcsLen );

	//재귀 호출 순서가 달라서 정확한 표현이 안되고
	//서브 시퀀스에 있는 원소들을 확인할 수는 있음
	//정확한 확인을 위해서는 2차원 배열로 만들고 2차원 배열에서 i, j가 겹치는 부분에 대해서 확인하고 가져와야 할 듯
	for ( unsigned int i = 0; i < x.length(); ++i )
	{
		printf_s( "%c", subsequence[i] );
	}

	delete[] subsequence;

	getchar();
	return 0;
}

int Lcs( std::string& str1, int str1SubLen, std::string& str2, int str2SubLen, char* subsequence )
{
	int lcsLen;

	if (str1SubLen == 0 || str2SubLen == 0)
	{
		return 0;
	}

	//마지막 원소가 겹치면 겹치는 원소를 제외하고 다시 확인
	if (str1[str1SubLen] == str2[str2SubLen])
	{
		subsequence[str1SubLen] = str1[str1SubLen];
		lcsLen = Lcs( str1, str1SubLen - 1, str2, str2SubLen - 1, subsequence ) + 1;
	}

	//마지막 원소가 겹치지 않으면, 둘 중 하나만 줄여서 다시 확인
	//둘 중 어느 것을 줄일지는 모르기 때문에 둘다 할 것
	//둘은 독립적이기 때문에 두 결과 중 더 큰 결과가 longest임
	//따라서 max로 확인
	else
	{
		lcsLen = _MAX( Lcs( str1, str1SubLen, str2, str2SubLen - 1, subsequence ), Lcs( str1, str1SubLen - 1, str2, str2SubLen, subsequence ) );
	}

	return lcsLen;
}


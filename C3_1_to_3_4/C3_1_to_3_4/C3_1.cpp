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

	//��� ȣ�� ������ �޶� ��Ȯ�� ǥ���� �ȵǰ�
	//���� �������� �ִ� ���ҵ��� Ȯ���� ���� ����
	//��Ȯ�� Ȯ���� ���ؼ��� 2���� �迭�� ����� 2���� �迭���� i, j�� ��ġ�� �κп� ���ؼ� Ȯ���ϰ� �����;� �� ��
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

	//������ ���Ұ� ��ġ�� ��ġ�� ���Ҹ� �����ϰ� �ٽ� Ȯ��
	if (str1[str1SubLen] == str2[str2SubLen])
	{
		subsequence[str1SubLen] = str1[str1SubLen];
		lcsLen = Lcs( str1, str1SubLen - 1, str2, str2SubLen - 1, subsequence ) + 1;
	}

	//������ ���Ұ� ��ġ�� ������, �� �� �ϳ��� �ٿ��� �ٽ� Ȯ��
	//�� �� ��� ���� �������� �𸣱� ������ �Ѵ� �� ��
	//���� �������̱� ������ �� ��� �� �� ū ����� longest��
	//���� max�� Ȯ��
	else
	{
		lcsLen = _MAX( Lcs( str1, str1SubLen, str2, str2SubLen - 1, subsequence ), Lcs( str1, str1SubLen - 1, str2, str2SubLen, subsequence ) );
	}

	return lcsLen;
}


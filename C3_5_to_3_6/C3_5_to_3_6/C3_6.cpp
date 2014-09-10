// C3_5_to_3_6.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

int LongestIncreasingSeq( int* seq, int seqSize );

int _tmain( int argc, _TCHAR* argv[] )
{
	int seq[] = { 3, 2, 1, 4, 0, 2, 3, 9, 4, 6, 5 };
	int seqSize = sizeof( seq )/sizeof(int);
	
	int result = LongestIncreasingSeq( seq, seqSize );
	printf_s( "%d\n", result );


	getchar();
	return 0;
}

int LongestIncreasingSeq( int* seq, int seqSize )
{
	int maxlen = 0;
	int* length = new int[seqSize];
	for ( int i = 0; i < seqSize; ++i )
	{
		length[i] = 1;
	}


	for ( int i = 1; i < seqSize; ++i )
	{
		for ( int j = 0; j < i; ++j )
		{
			if ( seq[i] == seq[j]+1 && length[i] < length[j]+1 )
			{
				length[i] = length[j] + 1;

				if ( maxlen < length[i] )
				{
					maxlen = length[i];
				}
			}
		}
	}
	
	delete[] length;
	return maxlen;
}

//references
//http://piml.tistory.com/2
//http://moogi.new21.org/tc/421
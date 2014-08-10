#include <iostream>

int FiboBottomTop( int idx );

int main( void )
{
	int idx = 10;
	
	printf_s( "%d \n", FiboBottomTop(idx) );

	getchar();
	return 0;
}

int FiboBottomTop( int idx )
{
	int result = 0;
	int* fiboBank = new int[idx + 1];

	fiboBank[0] = 0;
	fiboBank[1] = 1;

	if (idx >= 2)
	{
		for ( int i = 2; i <= idx; ++i )
		{
			fiboBank[i] = fiboBank[i - 1] + fiboBank[i - 2];
		}
	}

	result = fiboBank[idx];

	delete[] fiboBank;

	return result;
}

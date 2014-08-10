#include <iostream>

//전방 선언
int Fibo( int idx );


int main( void )
{
	int idx = 10;
	int result = 0;

	for ( int i = 0; i <= idx; ++i )
	{
		std::cout << i <<"번 FiboNum:  ";
		result = Fibo( i );
		std::cout << result << std::endl;
	}
	
	getchar();
	return 0;
}

int Fibo( int idx )
{
	if (idx < 2)
	{
		return idx;
	}
	else
	{
		return Fibo( idx - 1 ) + Fibo( idx - 2 );
	}
}

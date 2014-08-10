#include <iostream>
#include <vector>


//���� ����
int Fibo( int idx );
int FiboTopDown( int idx, std::vector<int>& fibobank );


int main( void )
{
	int idx = 10;
	int result;

	std::vector<int> fibobank;
	//vector�� ��ü�� �̸� ä��� ������� ����
	fibobank.resize( idx+1 );

	for ( int i = 0; i <= idx; ++i )
	{
		fibobank[i] = -1;
	}

	FiboTopDown( idx, fibobank );
	printf_s( "%d \n", fibobank[idx] );

	//testcase
	for ( int i = 5; i < idx; ++i )
	{
		FiboTopDown( i, fibobank );
	}

	//print test case
	for ( int i = 0; i <= idx; ++i )
	{
		//5���� �׸񿡼��� -1�� ���
		printf_s( "%d \n", fibobank[i] );
	}

	getchar();
	return 0;
}

int Fibo( int idx )
{
	if ( idx < 2 )
	{
		return idx;
	}
	else
	{
		return Fibo( idx - 1 ) + Fibo( idx - 2 );
	}
}

int FiboTopDown( int idx, std::vector<int>& fibobank )
{
	if (fibobank[idx] != -1)
	{
		return fibobank[idx];
	}

	if (idx < 2)
	{
		fibobank[idx] = idx;
	}
	else
	{
		fibobank[idx] = Fibo( idx - 1 ) + Fibo( idx - 2 );
	}

	return fibobank[idx];
}

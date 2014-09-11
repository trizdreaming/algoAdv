// C5_1.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "structures.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BYTES 256
#define SWAP(x,y) int temp; temp= a[x]; \
					a[x] = a[y]; \
					a[y] = temp;
#define MAXBITSPERCODE 100

heap_t* HeapCreate( int size, long* freqs );
void HeapClean( heap_t* heap );
void HeapSort( heap_t* heap );
void HeapAdd( heap_t* heap, int c );

huffcode_t** CreateHuffmanCode( long *freqs );
void CleanHoffmancode( huffcode_t** codes );

void CreateFreq( char* inputs, long* freqs );
void ConvertToBit( int c, int n, char* s );

int _tmain(int argc, _TCHAR* argv[])
{
	char* inputs = "abbbbca";

	huffcode_t** result = nullptr;
	char strBit[MAXBITSPERCODE] = { 0, };
	long freqs[BYTES] = { 0, };


	CreateFreq( inputs, freqs );
	
	result = CreateHuffmanCode( freqs );

	for ( int i = 0; i < BYTES; ++i )
	{
		if (result[i] != nullptr)
		{
			ConvertToBit( result[i]->code, result[i]->bits, strBit );
			printf_s( "%c [%d] %s \n", i, result[i]->code, strBit );
		}
	}

	CleanHoffmancode( result );

	getchar();
	return 0;
}

//heap�� ����Ÿ �ڵ忡�� ����

heap_t* HeapCreate( int size, long* freqs )
{
	heap_t* h = (heap_t*)malloc( sizeof( heap_t ) );
	//���� �����͸� ������ �ִ� �迭
	h->dataNode = (int *)malloc( sizeof( int )*size );
	
	//���� ������ ���� ������
	//���� ������ ��� �÷��� ������ ���� ������
	h->curDataSize = h->increaseSize = size;

	//���� ������ ����
	h->dataCounter = 0;

	//�������� ���� ���̺�
	h->freqInfo = freqs;
	return h;
}

void HeapClean( heap_t* heap )
{
	free( heap->dataNode );
	free( heap );
}


//���� ���� ���� ������ ������ �ϴ� ��
void HeapSort( heap_t* heap )
{
	int i = 1, j = 2;
	int *a = heap->dataNode;

	while ( i < heap->dataCounter )
	{
		//�ش� ���ڿ� �ִ� �������ø� �������� �ؼ� �������ð� ���� ���� �������� ������ ��
		if ( heap->freqInfo[a[i-1]] >= heap->freqInfo[a[i]])
		{
			//���࿡ �̹� �����Ǿ� ������ �� ����� �� ĭ ����
			//ex) 0, 1 �񱳿��� 1, 2 �񱳰� �ǵ��� ��
			i = j;
			++j;
		}
		else
		{
			//sorting �Ǿ� ���� ������ �迭 ���� �ڷḦ swap
			SWAP( i - 1, i );
			
			//������ 3������ ���ϱ� ����
			--i;
			i = ( i == 0 ) ? ++j : i;
		}
	}
}

void HeapAdd( heap_t* heap, int c )
{
	//heap�� ������ ī���Ͱ� ��ü ��Ƶ� ������ �������� ũ��
	if ((heap->dataCounter+1)> heap->curDataSize)
	{
		//�����͸� �߰��� ������ �߰� Ȯ�� �� ��
		heap->dataNode = (int*)realloc( heap->dataNode, heap->curDataSize + heap->increaseSize );
		heap->curDataSize += heap->increaseSize;
	}
	heap->dataNode[heap->dataCounter] = c;
	heap->dataCounter++;
	HeapSort( heap );
}

int HeapRemove( heap_t* heap )
{
	if (heap->dataCounter > 0)
	{
		heap->dataCounter--;
		return heap->dataNode[heap->dataCounter];
	}
	return false;
}

huffcode_t** CreateHuffmanCode( long *freqs )
{
	huffcode_t **codes = nullptr;
	heap_t *heap = nullptr;
	long efreqs[BYTES * 2] = { 0, };
	int preds[BYTES * 2] = { 0, };
	int extf = BYTES;
	int r1 = 0, r2 = 0;

	memcpy_s( efreqs, sizeof( efreqs ), freqs, sizeof( long )*BYTES );

	heap = HeapCreate( BYTES * 2, efreqs );
	if ( heap == NULL ) return NULL;

	//�������ø� Ȱ���� �� ������ ����
	//�̹� efreqs�� �Է� ���� freq�� ������ ����
	for ( int i = 0; i < BYTES; i++ )
	{
		if ( efreqs[i] > 0 )
		{
			HeapAdd( heap, i );
		}
	}

	while ( heap->dataCounter > 1 )
	{
		//�ּ� freq node ����
		r1 = HeapRemove( heap );
		r2 = HeapRemove( heap );

		//�ش� node ���� �� �ű� ��� �߰�
		efreqs[extf] = efreqs[r1] + efreqs[r2];
		HeapAdd( heap, extf );


		preds[r1] = extf;
		preds[r2] = -extf;
		extf++;
	}
	//root�� �ִ� ��
	//���� huffman tree�� preds�� ����
	r1 = HeapRemove( heap );
	preds[r1] = r1;
	HeapClean( heap );

	codes = (huffcode_t**)malloc( sizeof( huffcode_t * )*BYTES );

	//codeȭ �ϴ� ��
	int bc, bn, ix=0;
	for ( int i = 0; i < BYTES; i++ )
	{
		bc = 0; bn = 0;
		if ( efreqs[i] == 0 ) { codes[i] = NULL; continue; }
		ix = i;

		//2���� code�� ����� ��
		//preds�� ����Ǿ� �ִ� ���� �������� ����Ʈ ������ ���� ����
		while ( abs( preds[ix] ) != ix )
		{
			bc |= ( ( preds[ix] >= 0 ) ? 1 : 0 ) << bn;
			//���� �ڸ����� �����ϴ� �Լ�
			ix = abs( preds[ix] );
			bn++;
		}
		codes[i] = (huffcode_t*)malloc( sizeof( huffcode_t ) );
		codes[i]->bits = bn;
		codes[i]->code = bc;
	}
	return codes;
}

void CleanHoffmancode( huffcode_t** codes )
{
	for ( int i = 0; i < BYTES; ++i )
	{
		free( codes[i] );
	}
	free( codes );
}

void CreateFreq( char* inputs, long* freqs )
{
	char* temp = inputs;

	while ( *temp != '\0' )
	{
		//�� �ش��ϴ� �迭�� �߰��ϰ�
		//inputs�� �ϳ��� �����ϵ��� ��
		freqs[*temp] += 1;
		*temp++;
	}
}

void ConvertToBit( int c, int n, char* s )
{
	//2���� string���� ������ �Լ�
	s[n] = '\0';
	while ( n>0 )
	{
		s[n - 1] = ( c % 2 ) + '0';
		c >>= 1;
		--n;
	}
}

//references
//http://rosettacode.org/wiki/Huffman_coding#Alternative

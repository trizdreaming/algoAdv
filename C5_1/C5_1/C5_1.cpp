// C5_1.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
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

//heap은 로제타 코드에서 참조

heap_t* HeapCreate( int size, long* freqs )
{
	heap_t* h = (heap_t*)malloc( sizeof( heap_t ) );
	//실제 데이터를 가지고 있는 배열
	h->dataNode = (int *)malloc( sizeof( int )*size );
	
	//현재 데이터 영역 사이즈
	//향후 증가할 경우 늘려갈 데이터 영역 사이즈
	h->curDataSize = h->increaseSize = size;

	//현재 데이터 개수
	h->dataCounter = 0;

	//프리퀀시 정보 테이블
	h->freqInfo = freqs;
	return h;
}

void HeapClean( heap_t* heap )
{
	free( heap->dataNode );
	free( heap );
}


//가장 작은 같이 끝으로 가도록 하는 힙
void HeapSort( heap_t* heap )
{
	int i = 1, j = 2;
	int *a = heap->dataNode;

	while ( i < heap->dataCounter )
	{
		//해당 숫자에 있는 프리퀀시를 기준으로 해서 프리퀀시가 작은 것을 뒤쪽으로 가도록 함
		if ( heap->freqInfo[a[i-1]] >= heap->freqInfo[a[i]])
		{
			//만약에 이미 정리되어 있으면 비교 대상을 한 칸 증가
			//ex) 0, 1 비교에서 1, 2 비교가 되도록 함
			i = j;
			++j;
		}
		else
		{
			//sorting 되어 있지 않으면 배열 내부 자료를 swap
			SWAP( i - 1, i );
			
			//스왑후 3번부터 비교하기 위함
			--i;
			i = ( i == 0 ) ? ++j : i;
		}
	}
}

void HeapAdd( heap_t* heap, int c )
{
	//heap의 데이터 카운터가 전체 잡아둔 데이터 개수보다 크면
	if ((heap->dataCounter+1)> heap->curDataSize)
	{
		//데이터를 추가할 영역을 추가 확보 할 것
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

	//프리퀀시를 활용해 힙 구조를 만듦
	//이미 efreqs는 입력 받은 freq를 복사한 상태
	for ( int i = 0; i < BYTES; i++ )
	{
		if ( efreqs[i] > 0 )
		{
			HeapAdd( heap, i );
		}
	}

	while ( heap->dataCounter > 1 )
	{
		//최소 freq node 제거
		r1 = HeapRemove( heap );
		r2 = HeapRemove( heap );

		//해당 node 제거 후 신규 노드 추가
		efreqs[extf] = efreqs[r1] + efreqs[r2];
		HeapAdd( heap, extf );


		preds[r1] = extf;
		preds[r2] = -extf;
		extf++;
	}
	//root를 넣는 것
	//실제 huffman tree는 preds에 있음
	r1 = HeapRemove( heap );
	preds[r1] = r1;
	HeapClean( heap );

	codes = (huffcode_t**)malloc( sizeof( huffcode_t * )*BYTES );

	//code화 하는 곳
	int bc, bn, ix=0;
	for ( int i = 0; i < BYTES; i++ )
	{
		bc = 0; bn = 0;
		if ( efreqs[i] == 0 ) { codes[i] = NULL; continue; }
		ix = i;

		//2진수 code를 만드는 것
		//preds에 저장되어 있는 값을 기준으로 쉬프트 연산을 통해 삽입
		while ( abs( preds[ix] ) != ix )
		{
			bc |= ( ( preds[ix] >= 0 ) ? 1 : 0 ) << bn;
			//다음 자릿수로 증가하는 함수
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
		//각 해당하는 배열에 추가하고
		//inputs를 하나씩 증가하도록 함
		freqs[*temp] += 1;
		*temp++;
	}
}

void ConvertToBit( int c, int n, char* s )
{
	//2진수 string으로 제작한 함수
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

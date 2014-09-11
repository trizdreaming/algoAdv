typedef struct HUFFCODE
{
	int bits;
	int code;
} huffcode_t;

typedef struct HUFFHEAP
{
	int *dataNode;
	int dataCounter;
	int curDataSize;
	int increaseSize;
	long* freqInfo;
} heap_t;
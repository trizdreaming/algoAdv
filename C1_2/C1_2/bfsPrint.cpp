#include <iostream>
#include <queue>

#define NOT_NUM INT_MAX

struct NODE
{
	int data = NOT_NUM;
	NODE *leftChild = nullptr;
	NODE *rightChild = nullptr;
};

void InsertTree( int insertData, NODE* leafNode );
void PrintTreeByBFS( NODE* root );

int main( void )
{
	NODE* rootNode = new NODE;

	int nodeTheNum = 5;

	for ( int i = 0; i < nodeTheNum; ++i )
	{
		InsertTree( rand()%10, rootNode );
	}

	PrintTreeByBFS( rootNode );

	getchar();
	return 0;
}

void InsertTree( int insertData, NODE* leafNode )
{
	if ( leafNode->data == NOT_NUM )
	{
		leafNode->data = insertData;
		return;
	}

	if ( insertData < leafNode->data )
	{
		if ( leafNode->leftChild )
		{
			InsertTree( insertData, leafNode->leftChild );
		}
		else
		{
			leafNode->leftChild = new NODE;
			leafNode->leftChild->data = insertData;
		}
	}
	else if ( insertData >= leafNode->data )
	{
		if ( leafNode->rightChild )
		{
			InsertTree( insertData, leafNode->rightChild );
		}
		else
		{
			leafNode->rightChild = new NODE;
			leafNode->rightChild->data = insertData;
		}
	}
}

void PrintTreeByBFS( NODE* root )
{
	if (root == nullptr)
	{
		return;
	}

	std::queue<NODE*> tempQueue;
	tempQueue.push( root );

	while ( !tempQueue.empty() )
	{
		NODE* tempNode = tempQueue.front();
		printf_s( "%d \n",  tempNode->data);

		if ( tempNode->leftChild != nullptr )
		{
			tempQueue.push( tempNode->leftChild );
		}
		if ( tempNode->rightChild != nullptr )
		{
			tempQueue.push( tempNode->rightChild );
		}

		delete tempNode;
		tempQueue.pop();
	}

}

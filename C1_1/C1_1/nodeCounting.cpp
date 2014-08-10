#include <iostream>

#define NOT_NUM INT_MAX

struct NODE
{
	int data = NOT_NUM;
	NODE *leftChild = nullptr;
	NODE *rightChild = nullptr;
};

void InsertTree(int insertData, NODE* leafNode);
int CountNode( NODE* root );

int main( void )
{
	NODE* rootNode = new NODE;

	int nodeTheNum = 5;

	for ( int i = 0; i < nodeTheNum; ++i )
	{
		InsertTree( rand() % 100, rootNode );
	}

	int calcedNodeNum = 0;
	calcedNodeNum = CountNode( rootNode );

	printf_s( "%d", calcedNodeNum );

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

int CountNode( NODE* root )
{
	if (root == nullptr)
	{
		return 0;
	}

	int result = 0;
	result = CountNode( root->leftChild ) + CountNode( root->rightChild ) + 1;

	delete root;

	return result;
}

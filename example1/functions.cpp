#include "PoolManager.h"
#include <iostream>
struct Node
{
	Node* pNext;
	int nData;
};

int main()
{

	Node* pNode = NULL;
	Node* pRoot = NULL;
	int nNoOfNodes =0;
	std::cout << "No Of Nodes" << std::endl;
	std::cin >> nNoOfNodes;
	while(nNoOfNodes--)
	{
		if(pRoot == NULL)
		{
			pNode = (Node*) CPoolManager::GetInst().GetChunk(sizeof(Node));
			pNode->pNext = NULL;
			pNode->nData = 0;
			pRoot = pNode;
		}
		std::cin >> pNode->nData;
		pNode->pNext =(Node*) CPoolManager::GetInst().GetChunk(sizeof(Node));
		pNode = pNode->pNext;
	}
	std::cout << "Printing out" << std::endl;
	Node* temp = pRoot;
	while(temp->pNext != NULL)
	{
		std::cout << temp->nData << std::endl;
		temp = temp->pNext;
	}

}

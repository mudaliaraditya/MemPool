//custom header
#include "MemoryPool.h"
#include "PoolManager.h"

//std header
#include <thread>

CPoolManager& p = CPoolManager::GetInst();

void OtherRandThread()
{
	char l = 'a' -1;
	std::vector<char*> lcChars;
	for(int i = 0;i < 26;i++)
	{
		l++;
		char* pVal;
		pVal = (char*)p.GetChunk(sizeof(char));
		*pVal = l;
		lcChars.push_back(pVal);
	}
	for(auto& a : lcChars)
	{
		std::cout << *a << std::endl;
	}
	return;
}

int main(int argc,char* argv[])
{
	std::thread lc(OtherRandThread);
	//OtherRandThread();
	int* lpnVar1 = (int*)p.GetChunk(sizeof(int));
	p.ReleaseChunk((void*)lpnVar1);
	lpnVar1  = (int*)p.GetChunk(sizeof(int));
	int* lpnVar2 = (int*)p.GetChunk(sizeof(int));
	int* lpnVar3 = (int*)p.GetChunk(sizeof(int));
	int* lpnVar4 =(int*) p.GetChunk(sizeof(int));
	p.ReleaseChunk((void*)lpnVar4);
	lpnVar4 = (int*) p.GetChunk(sizeof(int));
	int* lpnVar5 =(int*) p.GetChunk(sizeof(int));
	*lpnVar1 = 1;
	*lpnVar2 = 2;
	*lpnVar3 = 3;
	*lpnVar4 = 4;
	*lpnVar5 = 5;
	std::cout << *lpnVar1 << " "<< *lpnVar2 << " " << *lpnVar3 << " "<< *lpnVar4 << " " << std::endl;
	if(lc.joinable())
	{
		lc.join();
	}
}

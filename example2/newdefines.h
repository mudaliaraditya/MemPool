#ifndef NEW_DEFINES
#define NEW_DEFINES
#include "PoolManager.h"

void* operator new(std::size_t siz)
{
	CPoolManager& p = CPoolManager::GetInst();
	void* pAddr = p.GetChunk(siz);
	return pAddr;
}

void operator delete(void* pVoid)
{
	CPoolManager::GetInst().ReleaseChunk(pVoid);
	return;
}









#endif

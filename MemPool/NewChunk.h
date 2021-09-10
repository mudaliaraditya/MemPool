#ifndef NEW_DEFINES
#define NEW_DEFINES
#include "PoolManager.h"
#include<new>
void* operator new(std::size_t siz)
{
	CPoolManager& p = CPoolManager::GetInst();
	void* pAddr = p.GetChunk(siz);
	return pAddr;
}

void* operator new(std::size_t siz,const std::nothrow_t &tag) noexcept
{
	try
	{
		CPoolManager& p = CPoolManager::GetInst();
		void* pAddr = p.GetChunk(siz);
		return pAddr;
	}
	catch(std::exception& e)
	{
		return nullptr;
	}
	catch(...)
	{
		return nullptr;
	}
}

void* operator new[](std::size_t siz)
{
	CPoolManager& p = CPoolManager::GetInst();
	void* pAddr = p.GetChunk(siz);
	return pAddr;
}

void* operator new[](std::size_t siz,const std::nothrow_t &tag) noexcept
{
	try
	{
		CPoolManager& p = CPoolManager::GetInst();
		void* pAddr = p.GetChunk(siz);
		return pAddr;
	}
	catch(std::exception& e)
	{
		return nullptr;
	}
	catch(...)
	{
		return nullptr;
	}
}

void operator delete(void* pVoid)
{
	CPoolManager::GetInst().ReleaseChunk(pVoid);
	return;
}

void operator delete[](void* pVoid)
{
	CPoolManager::GetInst().ReleaseChunk(pVoid);
	return;
}







#endif

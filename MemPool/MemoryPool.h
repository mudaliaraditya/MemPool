#ifndef MEMORY_POOL
#define MEMORY_POOL
//custom header
#include"MemoryDefines.h"
#include "Mallocator.hpp"

//std header
#include<vector>
#include<map>
#include<iostream>
#include<cstring>
#include<mutex>

typedef std::map<long long,long long,std::less<long long>,Mallocator< std::pair<const long long, long long> > > UsedChunksToBytes;
typedef std::multimap<long long,long long,std::less<long long>,Mallocator< std::pair<const long long, long long> > > FreeByteToChunks;


class CMemoryPool
{
	public:
	friend class CPoolManager;
	~CMemoryPool()
	{
		free(m_chunk);
	}

	static CMemoryPool& GetInst()
	{
		static CMemoryPool s_MemoryPool(MEMORY_POOL_SIZE);
		return s_MemoryPool;
	}

	void* GetChunk(size_t nBytes)
	{
		std::unique_lock<std::mutex> lcLock(m_cMutex);
		FreeByteToChunks::iterator lcIter = m_cFreeByteToChunks.find(nBytes);
		if(lcIter != m_cFreeByteToChunks.end())
		{
			m_cUsedChunksToBytes[lcIter->second] = nBytes;
			void* pResvAddr =(void*) lcIter->second;
			m_cFreeByteToChunks.erase(lcIter);
			return pResvAddr;
		}
		if(nBytes > m_nSizeOfTotalChunk)
		{
			throw std::runtime_error("More Memory requested greater than total memory defined");
		}
		if(m_nFreeBytes < nBytes)
		{
			return nullptr;
		}
		char* PrevFreeChunk = m_cFreeChunk;
		std::pair<UsedChunksToBytes::iterator,bool > lcRetVal = m_cUsedChunksToBytes.insert(std::make_pair((MemAddrs)PrevFreeChunk,nBytes));
		if(lcRetVal.second == false)
		{
			return nullptr;
		}
		m_cFreeChunk = m_cFreeChunk + nBytes;
		m_nFreeBytes = m_nFreeBytes - nBytes;
		if (m_nFreeBytes == 0)
		{
		}
		return PrevFreeChunk;
	}

	bool ReleaseChunk(void* pUsedChunk)
	{
		std::unique_lock<std::mutex> lcLock(m_cMutex);
		UsedChunksToBytes::iterator lcIter =  m_cUsedChunksToBytes.find((MemAddrs)pUsedChunk);
		if(lcIter == m_cUsedChunksToBytes.end())
		{
			throw std::runtime_error("invalid Memory");
		}
		long long lnBytes = lcIter->second;
		std::memset(pUsedChunk,0,lnBytes);
		m_cUsedChunksToBytes.erase((MemAddrs)pUsedChunk);
		FreeByteToChunks::iterator iter = m_cFreeByteToChunks.insert(std::make_pair(lnBytes, (MemAddrs)pUsedChunk));
		if(iter == m_cFreeByteToChunks.end())
		{
			throw std::runtime_error("invalid Memory");
		}
		return true;
	}



	private:
	
	CMemoryPool(size_t nMaxChunk)
	{
		std::unique_lock<std::mutex> lcLock(m_cMutex);
		m_nSizeOfTotalChunk = nMaxChunk;
		m_nFreeBytes = nMaxChunk;
		m_chunk = (char*)malloc(m_nSizeOfTotalChunk);
		m_cFreeChunk = m_chunk;
		memset(m_chunk,0,(m_nSizeOfTotalChunk));
	}

	std::mutex m_cMutex;
	UsedChunksToBytes m_cUsedChunksToBytes;
	FreeByteToChunks    m_cFreeByteToChunks;
	char* m_chunk;
	long long   m_nSizeOfTotalChunk;
	long long   m_nFreeBytes;
	char* m_cFreeChunk;
};

#endif

#ifndef MEMORY_POOL
#define MEMORY_POOL
//custom header
#include"MemoryDefines.h"

//std header
#include<vector>
#include<map>
#include<iostream>
#include<cstring>
#include<mutex>

class CMemoryPool
{
	public:
	friend class CPoolManager;
	~CMemoryPool()
	{
		delete[] m_chunk;
	}

	void* GetChunk(size_t nBytes)
	{
		std::unique_lock<std::mutex> lcLock(m_cMutex);
		std::multimap<long long,void*>::iterator lcIter = m_cFreeByteChunks.find(nBytes);
		if(lcIter != m_cFreeByteChunks.end())
		{
			std::cout << "found a free chunk" << std::endl;
			m_cUsedChunksToBytes[lcIter->second] = nBytes;
			void* pResvAddr = lcIter->second;
			m_cFreeByteChunks.erase(lcIter);
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
		std::cout << "creating a new chunk" << std::endl;
		char* PrevFreeChunk = m_cFreeChunk;
		m_cUsedChunksToBytes[(void*)PrevFreeChunk] = nBytes;
		m_cFreeChunk = m_cFreeChunk + nBytes;
		m_nFreeBytes = m_nFreeBytes - nBytes;
		if (m_nFreeBytes == 0)
		{
			std::cout << "you have exhausted your memory" << std::endl;
		}
		return PrevFreeChunk;
	}

	bool ReleaseChunk(void* pUsedChunk)
	{
		std::unique_lock<std::mutex> lcLock(m_cMutex);
		std::map<void*,long long>::iterator lcIter =  m_cUsedChunksToBytes.find(pUsedChunk);
		if(lcIter == m_cUsedChunksToBytes.end())
		{
			throw std::runtime_error("invalid Memory");
		}
		std::cout << "Releasing Chunk" << std::endl;
		long long lnBytes = lcIter->second;
		//std::memset(pUsedChunk,0,lnBytes);
		m_cUsedChunksToBytes.erase(pUsedChunk);
		auto iter = m_cFreeByteChunks.insert(std::make_pair(lnBytes, pUsedChunk));
		if(iter == m_cFreeByteChunks.end())
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
		m_chunk = new char[m_nSizeOfTotalChunk];
		m_cFreeChunk = m_chunk;
		memset(m_chunk,0,(m_nSizeOfTotalChunk));
	}

	std::mutex m_cMutex;
	std::map<void*,long long> m_cUsedChunksToBytes;
	std::multimap<long long,void*> m_cFreeByteChunks;
	char* m_chunk;
	long long   m_nSizeOfTotalChunk;
	long long   m_nFreeBytes;
	char* m_cFreeChunk;
};

#endif

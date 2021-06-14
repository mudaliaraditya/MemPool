#ifndef POOL_MANAGER_H
#define POOL_MANAGER_H
//custom header
#include "MemoryPool.h"
#include "MemoryDefines.h"


//std header
#include <vector>
#include <unordered_map>

//custom typedefs
typedef std::vector<CMemoryPool*,Mallocator<CMemoryPool*> > MemoryPoolStore;
typedef std::unordered_map<MemAddrs,size_t,std::hash<MemAddrs>,std::equal_to<MemAddrs>,Mallocator<std::pair<const MemAddrs,size_t> > > ChunkMemoryToMemoryPoolNo;



class CPoolManager
{
	private:

		CPoolManager(size_t nMaxChunk)
		{
			std::unique_lock<std::mutex> lcLock(m_cMutex);

			m_nMaxChunkSize = nMaxChunk;
		}

	public:

		static CPoolManager& GetInst()
		{
			static CPoolManager s_cPool(MEMORY_POOL_SIZE);

			return s_cPool;
		}

		void* GetChunk(size_t nBytes)
		{
			std::unique_lock<std::mutex> lcLock(m_cMutex);

			if(nBytes == 0)
			{
				return nullptr;
			}

			void* pAddress = nullptr;
			size_t lnCounter = 0;
			
			for(auto& pool : m_cMemoryPoolStore)
			{
				pAddress = pool->GetChunk(nBytes);
				if(pAddress != nullptr)
				{
					m_ChunkMemoryToMemoryPoolNo[(MemAddrs)pAddress] = lnCounter;

					return pAddress;
				}

				lnCounter++;
			}
			void* pMem = malloc(sizeof(CMemoryPool));
			memset(pMem,0,sizeof(CMemoryPool));
			CMemoryPool* pPool = new(pMem)CMemoryPool(m_nMaxChunkSize);
			pAddress = pPool->GetChunk(nBytes);
			if(pAddress != nullptr)
			{
				m_ChunkMemoryToMemoryPoolNo[(MemAddrs)pAddress] = lnCounter;

				m_cMemoryPoolStore.push_back(pPool);

				return pAddress;
			}

			throw std::runtime_error("Error in allocating Memory");
		}

		bool ReleaseChunk(void* pMemory)
		{
			std::unique_lock<std::mutex> lcLock(m_cMutex);

			auto lcIter = m_ChunkMemoryToMemoryPoolNo.find((MemAddrs)pMemory);
			if(lcIter == m_ChunkMemoryToMemoryPoolNo.end())
			{
				return false;
			}

			size_t lnMemoryPoolNo = m_ChunkMemoryToMemoryPoolNo[(MemAddrs)pMemory];

			return m_cMemoryPoolStore[(lnMemoryPoolNo)]->ReleaseChunk(pMemory);
		}


		~CPoolManager()
		{
			std::unique_lock<std::mutex> lcLock(m_cMutex);

			for(auto& pool : m_cMemoryPoolStore)
			{
				pool->~CMemoryPool();
				free(pool);
			}
		}

	private:
		MemoryPoolStore			         m_cMemoryPoolStore;
		ChunkMemoryToMemoryPoolNo        m_ChunkMemoryToMemoryPoolNo;
		size_t									m_nMaxChunkSize;
		std::mutex								m_cMutex;
};















#endif

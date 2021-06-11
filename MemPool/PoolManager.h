#ifndef POOL_MANAGER_H
#define POOL_MANAGER_H
//custom header
#include "MemoryPool.h"
#include "MemoryDefines.h"

//std header
#include <vector>
#include <unordered_map>

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
					m_ChunkMemoryToMemoryPoolNo[pAddress] = lnCounter;

					return pAddress;
				}

				lnCounter++;
			}

			CMemoryPool* pPool = new CMemoryPool(m_nMaxChunkSize);
			pAddress = pPool->GetChunk(nBytes);
			if(pAddress != nullptr)
			{
				m_ChunkMemoryToMemoryPoolNo[pAddress] = lnCounter;

				m_cMemoryPoolStore.push_back(pPool);

				return pAddress;
			}

			throw std::runtime_error("Error in allocating Memory");
		}

		bool ReleaseChunk(void* pMemory)
		{
			std::unique_lock<std::mutex> lcLock(m_cMutex);

			auto lcIter = m_ChunkMemoryToMemoryPoolNo.find(pMemory);
			if(lcIter == m_ChunkMemoryToMemoryPoolNo.end())
			{
				return false;
			}

			size_t lnMemoryPoolNo = m_ChunkMemoryToMemoryPoolNo[pMemory];

			return m_cMemoryPoolStore[(lnMemoryPoolNo)]->ReleaseChunk(pMemory);
		}


		~CPoolManager()
		{
			std::unique_lock<std::mutex> lcLock(m_cMutex);

			for(auto& pool : m_cMemoryPoolStore)
			{
				delete pool;
			}
		}

	private:
		std::vector<CMemoryPool*>			m_cMemoryPoolStore;
		std::unordered_map<void*,size_t> m_ChunkMemoryToMemoryPoolNo;
		size_t									m_nMaxChunkSize;
		std::mutex								m_cMutex;
};















#endif

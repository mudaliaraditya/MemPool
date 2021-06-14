#ifndef DEFINES_MEMORY_POOL
#define DEFINES_MEMORY_POOL

//#include <set>
//#include <functional>

#define MEMORY_POOL_SIZE (1024*1024*99)

typedef long long MemAddrs;

template<typename T>
inline void CallDestructor(T* t)
{
	t->~T();
}

#define CNEW(CLASS, ...)\
{	 (new (CPoolManager::GetInst().GetChunk(sizeof(CLASS))) (CLASS) ( __VA_ARGS__ )) }

#define DNEW(PTR)\
{CallDestructor(PTR); CPoolManager::GetInst().ReleaseChunk((void*) PTR);}

#define DOBJ(OBJ)\
{	DNEW(&OBJ); }

#define COBJ(CLASS, ...)\
{	 *(new (CPoolManager::GetInst().GetChunk(sizeof(CLASS))) (CLASS) ( __VA_ARGS__ )) }





#endif

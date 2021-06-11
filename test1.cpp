//custom header
#include "PoolManager.h"

//std header
#include <set>
#include <functional>
#include <thread>

class A;
class AB;

class AB
{
	public:
	bool operator()(const int& a,const int& b) const
	{
		return b >a;
	}
};

#define REF(TYPE) std::reference_wrapper<TYPE>

std::set< REF(int),AB > m_cSET;


class A
{
	public:
	int b;
	A(int a)
	{
		b = a;
	}



	~A()
	{
		std::cout << "calling dtor" << std::endl;
	}
};

void OtherRandThread()
{
	char l = 'a' -1;
	std::vector<char*> lcChars;
	for(int i = 0;i < 26;i++)
	{
		l++;
		char* pVal;
		pVal = CNEW(char); //(char*)p.GetChunk(sizeof(char));
		*pVal = l;
		lcChars.push_back(pVal);
	}
	for(auto& a : lcChars)
	{
		std::cout << " OtherRandThread "<< (int)*a << " " << (long long)a << std::endl;
	}
	std::this_thread::sleep_for(std::chrono::seconds(2));
	return;
}


int main()
{
	std::thread lcThread(OtherRandThread);
	char lcPrevChar = ('a' - 1);
	std::vector<char*> lcVecOfAlphabets;
	for(int i =0; i < 26; i++ )
	{
		char* a = CNEW(char);//Get Memory From Pool
		*a = lcPrevChar + 1;
		lcPrevChar = *a;
		std::cout << " Before release "<< (int)*a << " "<< (long long)a << std::endl;
		if(!CPoolManager::GetInst().ReleaseChunk(a))
		{
			exit(-1);
		}
		a =(char*) CPoolManager::GetInst().GetChunk(sizeof(char));//Reclaiming Memory
		lcVecOfAlphabets.push_back(a);
		std::cout << " After Reclaim " << (int)*a << " "<< (long long)a << std::endl;
	}
	std::cout << "End of Adding to Store" << std::endl;
	for(auto a : lcVecOfAlphabets)
	{
		std::cout << " main "<< (int)*a << " "<< (long long)a << std::endl;
		DNEW(a);
	}
	lcVecOfAlphabets.clear();
	std::cout << std::endl;
	int& a = COBJ(int);
	m_cSET.insert(a);
	A& b = COBJ(A,1);//Creating a Reference Obj
	DOBJ(b);//Destroying a Reference Obj
	if(lcThread.joinable())
	{
		lcThread.join();
	}
}

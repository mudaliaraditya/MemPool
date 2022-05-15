#include "NewChunk.h"
#include <iostream>
#include <thread>
#include <unistd.h>
#define NO_OF_ELEMENTS (1024 * 1024 )
class A
{
	public:
		A()
		{
		}

		~A()
		{
			std::cout << "dtor for A" << std::endl;
		}


};

void Test1(int nNo)
{
	int* pArr = nullptr;
	pArr = new int[NO_OF_ELEMENTS];
	for(int i = 0;i< NO_OF_ELEMENTS ;i++)
	{
		pArr[i] = i;
	}
	for(int i = 0;i< NO_OF_ELEMENTS ;i++)
	{
		usleep(100);
		if(pArr[i] != i)
		{
			std::cout << "ERROR" << std::endl;
			exit(0);
		}
		std::cout << "tNo:[" << nNo << "]"<< pArr[i] << std::endl;
	}
	delete[] pArr;
	return;
}


int main(int argc,char** argv)
{
	std::thread t1(Test1,1);
	std::thread t2(Test1,2);
	std::thread t3(Test1,3);
	std::thread t4(Test1,4);
	int* p = new int();
	A* a = new A();
	delete a;
	delete p;
	t1.join();
	t2.join();
	t3.join();
	t4.join();
}


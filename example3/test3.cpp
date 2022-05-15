#include "NewChunk.h"
#include <iostream>

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

int main(int argc,char** argv)
{
	int* p = new int();
	A* a = new A();
	delete a;
	delete p;
}


#include "test.h"

void Test()
{
	std::vector<int*> lcDynamicArrayInt;
	for(int i = 0;i < MAX_Q_SIZE; i++)
	{
		lcDynamicArrayInt.push_back(new int(i));
	}
	for(int i = 0;i < MAX_Q_SIZE; i++)
	{
		delete lcDynamicArrayInt[i];
	}
	lcDynamicArrayInt.clear();
	return;

}

void StartBenchMark()
{
	auto start = std::chrono::steady_clock::now();
	std::thread* t[NO_OF_THREADS];
	for(int i = 0;i < NO_OF_THREADS;i++)
	{
		t[i] = new std::thread(Test);
	}
	for(int i = 0;i < NO_OF_THREADS;i++)
	{
		t[i]->join();
		delete t[i];
	}
	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed_seconds = end-start;
	std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
}

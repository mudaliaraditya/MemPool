
CXXFLAGS="--std=c++11"
CXXFLAGS+="-g"
CXXFLAGS+="-Og"
CXXFLAGS+="-I../MemPool"
CXXFLAGS+="-lpthread"


all : test3.out



test3.out : test3.o
	g++ -o $@ $^ ${CXXFLAGS} 



clean :
	rm *.o
	rm *.out

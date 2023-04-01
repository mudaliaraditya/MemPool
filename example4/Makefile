

CXX=g++
CXXFLAGS="--std=c++11"
CXXFLAGS+="-g"
CXXFLAGS+="-O3"
CXXFLAGS+="-I../MemPool"
CXXFLAGS+="-lpthread"


all : test4.out



test4.out : test4.o
	${CXX} -o $@ $^ ${CXXFLAGS} 



clean :
	rm *.o
	rm *.out

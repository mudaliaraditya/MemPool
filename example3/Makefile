

CXX=clang++
CXXFLAGS="--std=c++11"
CXXFLAGS+="-g"
CXXFLAGS+="-O3"
CXXFLAGS+="-I../MemPool"
CXXFLAGS+="-lpthread"


all : test3.out



test3.out : test3.o
	${CXX} -o $@ $^ ${CXXFLAGS} 



clean :
	rm *.o
	rm *.out


CXXFLAGS="--std=c++11"
CXXFLAGS+="-g"
CXXFLAGS+="-I../MemPool"
CXXFLAGS+="-O3"
CXXFLAGS+="-lpthread"


all : functions.out


functions.out : functions.o 
	${CXX} -o $@ $^ ${CXXFLAGS}


clean :
	rm *.o
	rm *.out

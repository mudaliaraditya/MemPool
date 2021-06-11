
CXXFLAGS="--std=c++11"
CXXFLAGS+="-g"
CXXFLAGS+="-IMemPool"
CXXFLAGS+="-O3"
CXXFLAGS+="-lpthread"


all : a.out


a.out : test.o 
	${CXX} -o $@ $^ ${CXXFLAGS}


clean :
	rm *.o
	rm *.out

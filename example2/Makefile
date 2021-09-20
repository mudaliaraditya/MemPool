
CXXFLAGS="--std=c++11"
CXXFLAGS+="-g"
CXXFLAGS+="-I../MemPool"
CXXFLAGS+="-O3"
CXXFLAGS+="-lpthread"


all : a.out b.out


a.out : test1.o 
	${CXX} -o $@ $^ ${CXXFLAGS}

b.out : test2.o
	${CXX} -o $@ $^ ${CXXFLAGS}



clean : 
	rm *.o
	rm *.out

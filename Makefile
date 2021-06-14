
CXXFLAGS="--std=c++11"
CXXFLAGS+="-g"
CXXFLAGS+="-IMemPool"
CXXFLAGS+="-O3"
CXXFLAGS+="-lpthread"


all : a.out b.out example/a.out


a.out : test1.o 
	${CXX} -o $@ $^ ${CXXFLAGS}

b.out : test2.o
	${CXX} -o $@ $^ ${CXXFLAGS}

example/a.out : example/test.o
	cd example && make


clean : 
	rm *.o
	rm *.out
	cd example && make clean

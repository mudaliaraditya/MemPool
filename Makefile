
CXXFLAGS="--std=c++11"
CXXFLAGS+="-g"
CXXFLAGS+="-IMemPool"
CXXFLAGS+="-O3"
CXXFLAGS+="-lpthread"


all : a.out example/a.out


a.out : main.o 
	${CXX} -o $@ $^ ${CXXFLAGS}

b.out : cmain.o
	${CXX} -o $@ $^ ${CXXFLAGS}

example/a.out : example/main.o
	cd example && make


clean : 
	rm *.o
	rm *.out
	cd example && make clean


CXXFLAGS="--std=c++11"
CXXFLAGS+="-g"
CXXFLAGS+="-I../MemPool"
CXXFLAGS+="-O3"
CXXFLAGS+="-lpthread"



all : StdNew MemPoolNew 

StdNew : StdNew.cpp test.*
	${CXX} -o $@ $^ ${CXXFLAGS}


MemPoolNew : MemPoolNew.cpp test.*
	${CXX} -o $@ $^ ${CXXFLAGS}


clean :
	rm MemPoolNew
	rm StdNew

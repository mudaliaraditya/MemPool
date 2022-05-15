CXX=g++

CXXFLAGS="--std=c++11"
CXXFLAGS+="-g"
CXXFLAGS+="-O3"
CXXFLAGS+="-I../MemPool"
CXXFLAGS+="-lpthread"
#CXXFLAGS+="--static"




all : libLib.so libLib-static.a test5.out a-static.out 





test5.out : libLib.so main.cpp
	${CXX} -o $@ $^ -L. -lLib ${CXXFLAGS} 

a-static.out : libLib-static.a main.cpp
	${CXX} -o $@ $^ -L. -lLib-static ${CXXFLAGS} -DNEW_DEFINES


libLib.so : Lib.cpp
	${CXX} -o $@ $^ -fPIC --shared ${CXXFLAGS}

libLib-static.a : Lib.cpp
	${CXX} -c   $^ -fPIC --shared ${CXXFLAGS}
	ar rcs  $@ *.o
	rm *.o


clean :
	rm *.so
	rm *.out

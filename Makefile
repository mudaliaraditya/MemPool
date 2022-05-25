 




all : example1/functions.out example2/a.out example2/b.out example3/test3.out example4/test4.out example5/test5.out



example1/functions.out :
	cd example1 && make

example2/a.out :
	cd example2 && make


example2/ab.out :
	cd example2 && make


example3/test3.out :
	cd example3 && make


example4/test4.out :
	cd example4 && make



example5/test5.out :
	cd example5 && make

clean : 
	cd example1 && make clean
	cd example2 && make clean
	cd example3 && make clean
	cd example4 && make clean
	cd example5 && make clean


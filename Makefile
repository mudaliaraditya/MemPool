



all : example1/functions.out example2/a.out example2/b.out example3/test3.out


example1/functions.out :
	cd example1 && make


example2/a.out :
	cd example2 && make


example2/ab.out :
	cd example2 && make


example3/test3.out :
	cd example3 && make


clean : 
	cd example1 && make clean
	cd example2 && make clean
	cd example3 && make clean

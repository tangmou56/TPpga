all: e1.o e2.o e3.o e4.o e5.o
	gcc -o exe1 e1.o
	gcc -o exe2 e2.o
	gcc -o exe3 e3.o
	gcc -o exe4 e4.o
	gcc -o exe5 e5.o
e1.o:e1.c
	gcc -c e1.c
	
e2.o:e2.c
	gcc -c e2.c

e3.o:e3.c
	gcc -c e3.c
	
e4.o:e4.c
	gcc -c e4.c
		
e5.o:e5.c
	gcc -c e5.c
	
clean : 
	rm *.o
	rm exe*
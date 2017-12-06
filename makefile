objects = main.c matrix.c

edit : $(objects)
	cc -o edit $(objects)

main.o : matrix.h
matrix.c: matrix.h

.PHONY : clean	
clean :
	rm edit $(objects
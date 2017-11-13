FLAGS = -Wall
DEPENDENCES = fichier.h

main : main.o
	gcc $(FLAGS) -o $@ $^

%.o: %.c $(DEPENDENCES)
	gcc $(FLAGS) -c $<

clean:
	rm *.o main

archive:
	tar cvf MASSE_Robin.tar.gz *.c *.h Makefile

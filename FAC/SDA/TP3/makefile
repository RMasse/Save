test : lib/nat.o testn.c
	gcc lib/nat.o testn.c -o test
lib/nat.o : nat.c include/nat.h include/bool.h
	gcc -c nat.c -o lib/nat.o
clean :
	rm lib/*.o
clean_all :
	rm test lib/*.o

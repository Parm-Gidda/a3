#Learned and adpated how to make a makefile from https://www.youtube.com/watch?v=_r7i5X0rXJk Username: Paul Programming
output: list.o my_malloc.o mem_test.o
	g++ list.o my_malloc.o mem_test.o -o mem_test

list.o: list.c
	g++ -c list.c

my_malloc.o: my_malloc.c
	g++ -c my_malloc.c

mem_test.o: mem_test.c 
	g++ -c mem_test.c

clean:
	rm *.o mem_test

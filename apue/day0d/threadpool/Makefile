.PHONY: clean main

main: threadpool.o main.o condition.o
	gcc $^ -o $@ -lpthread -lrt

%.o:%.c
	gcc -c $^ -o $@

clean :
	rm -rf *.o


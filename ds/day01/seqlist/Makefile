.PHONY: clean 

OBJS=seqlist.o main.o

main: $(OBJS)
	@gcc $^ -o $@

%.o : %.c
	@gcc -c $^ -o $@

clean:
	@rm -rf *.o main

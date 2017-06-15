.PHONY: clean

OBJS = dcirclelist.o main.o
TARGS = main
cc = gcc 
FLAGS = -g -c -std=c99 

$(TARGS): $(OBJS)
	@$(cc) $^ -o $@

%.o : %.c
	@$(cc) $(FLAGS) $^ -o $@

clean:
	@rm -rf *.o main 

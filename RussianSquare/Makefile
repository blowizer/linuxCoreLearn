.PHONY: clean

OBJS = RussianSquare.o 
TARGS = main
cc = gcc 
FLAGS = -g -c -std=c99 -l keyboard -L ./keyboard -l linklist -L ./linklist -l dcirclelist -L ./dcirclelist

$(TARGS): $(OBJS)
	@$(cc) $^ -o $@  -l keyboard -L ./keyboard -l linklist -L ./linklist -l dcirclelist -L ./dcirclelist

%.o : %.c
	@$(cc) $(FLAGS) $^ -o $@ 

clean:
	@rm -r *.o main 

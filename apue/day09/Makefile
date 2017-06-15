.PHONY: clean

snd: snd.c
	gcc $^ -o $@

rcv: rcv.o
	gcc $^ -o $@
rcv.o : rcv.c
	gcc -c $^ -o $@

clean:
	rm -f *.o

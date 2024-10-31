flags=-Wall -O2 -std=c2x
ldflags=

all: clean tree 

tree: tree.o
		cc ${flags} $^ -o $@ ${ldflags}

tree.o: tree.c
		cc ${flags} -c $^

test: tree
		./tree

clean:
		rm -f *.o tree
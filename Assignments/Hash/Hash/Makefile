INCLUDE_DIRS := Includes
CC 			 := g++
CFLAGS 		 := -I$(INCLUDE_DIRS) -g

OBJS 		 := hash.o main.o AVL/avl.o
DEPS 		 := hash.h AVL/avl.h

.PHONY: clean all

all: hash.o main.o AVL/avl.o output

clean:
	rm $(OBJS) output

hash.o: hash.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

main.o: mainHash.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

AVL/avl.o: AVL/avl.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

output: ${OBJS}
	$(CC) -o $@ $^ $(CFLAGS)
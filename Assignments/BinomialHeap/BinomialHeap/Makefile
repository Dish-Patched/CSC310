INCLUDE_DIRS := Includes
CC 			 := g++
CFLAGS 		 := -I$(INCLUDE_DIRS) -g

OBJS 		 := binomial.o main.o
DEPS 		 := binomial.h

.PHONY: clean all

all: binomial.o main.o output

clean:
	rm $(OBJS) output

binomial.o: binomial.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

main.o: main.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

output: ${OBJS}
	$(CC) -o $@ $^ $(CFLAGS)
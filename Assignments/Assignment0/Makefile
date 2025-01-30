CFLAGS 		 := -I.

OBJS 		 := customErrorClass.o bst.o mainbst.o
DEPS 		 := customErrorClass.h bst.h

.PHONY: clean all

all: customErrorClass.o bst.o mainbst.o output

clean:
	rm $(OBJS) output

customErrorClass.o: customErrorClass.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

bst.o: bst.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

mainbst.o: mainbst.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

output: ${OBJS}
	$(CC) -o $@ $^ $(CFLAGS)
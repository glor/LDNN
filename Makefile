CC="gcc"
CFLAGS=-std=c11 -O0 -v -da -Q
OBJ := LDNN.o vector.o datamodel.o test.o

all: compile
compile: $(OBJ)
	$(CC) $(CFLAGS) -lm $(OBJ) -o test

%.o: %.c
	$(CC) $(CFLAGS) -c $<
clean:
	rm -f test *.o
run: all
	./test

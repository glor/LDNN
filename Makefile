CC="clang"
OBJ := LDNN.o vector.o datamodel.o test.o

all: compile
compile: $(OBJ)
	$(CC) -lm $(OBJ) -o test

%.o: %.c
	$(CC) -c $<
clean:
	rm -f test *.o
run: all
	./test

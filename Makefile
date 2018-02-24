CC = clang
LD = ld
CFLAGS = -std=c11# -O0 -v -da -Q
LDFLAGS = -lm #-lstatic
OBJ = LDNN.o clustering.o vector.o test.o

all: tester
tester: lib
	$(CC) $(CFLAGS) $(LDFLAGS) libLDDN.a test.c -o test

lib: $(OBJ)
	$(LD) -r LDNN.o clustering.o vector.o -o libLDDN.a

%.o: %.c
	$(CC) $(CFLAGS) -c $<
clean:
	rm -f test *.o *.a
test: all
	./test

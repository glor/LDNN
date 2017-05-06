CC="clang++"

all:
	$(CC) -lm -o LDNN LDNN.c
	
run: all
	./LDNN

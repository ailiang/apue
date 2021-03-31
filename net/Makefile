CC=g++ 
CPPFLAGS=-std=c++11 -g
LIB=

SRC=$(wildcard *.c)
OBJ=$(patsubst %.c,%.o, $(SRC))

serv: $(OBJ) 
	$(CC) -o $@ $(OBJ) $(LIB)
$(OBJ): %.o:%.c
	$(CC) $(CPPFLAGS) -c $<

clean:
	rm -f serv *.o

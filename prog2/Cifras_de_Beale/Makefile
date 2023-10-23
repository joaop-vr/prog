CC=gcc
CFLAG= -std=c99 -Wall 
LFLAG=
NAME=beale

all: $(NAME)

$(NAME): beale.o encode.o decode.o arq_chave.o
	$(CC) $(CFLAG) beale.o encode.o decode.o arq_chave.o -o $(NAME)

beale.o: codigos/beale.c codigos/beale.h
	$(CC) -c $(CFLAG) codigos/beale.c

encode.o: codigos/encode.c codigos/encode.h
	$(CC) -c $(CFLAG) codigos/encode.c

decode.o: codigos/decode.c codigos/decode.h
	$(CC) -c $(CFLAG) codigos/decode.c

arq_chave.o: codigos/arq_chave.c codigos/arq_chave.h
	$(CC) -c $(CFLAG) codigos/arq_chave.c

clean:
	rm -f *.o *.gch

purge: clean
	-rm -f $(NAME)
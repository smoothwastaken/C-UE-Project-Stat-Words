CC=gcc
CFLAGS=-std=c11 -Wpedantic -Wall -Wextra -fsanitize=address
LDLIBS=-lm
RM=rm -f
OBJ=statstxt.o listemots.o
EXE=statstxt
# Pour produire le fichier exécutable
$(EXE):$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXE) $(LDLIBS)
# Pour produire les fichiers objets
statstxt.o:statstxt.c listemots.h
	$(CC) $(CFLAGS) -c statstxt.c
utils.o:utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c
listemots.o:listemots.c listemots.h
	$(CC) $(CFLAGS) -c listemots.c
# Pour effacer les objets et les exécutables
clean:
	$(RM) $(OBJ) $(EXE)

CC=gcc
CFLAGS=-std=c11 -Wpedantic -Wall -Wextra
LDLIBS=-lm
RM=rm -f
OBJ=testlistemots.o listemots.o
EXE=testlistemots
# Pour produire le fichier exécutable
$(EXE):$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXE) $(LDLIBS)
# Pour produire les fichiers objets
testlistemots.o:testlistemots.c listemots.h
	$(CC) $(CFLAGS) -c testlistemots.c
listemots.o:listemots.c listemots.h
	$(CC) $(CFLAGS) -c listemots.c
# Pour effacer les objets et les exécutables
clean:
	$(RM) $(OBJ) $(EXE)
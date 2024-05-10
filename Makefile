CC=gcc
CFLAGS=-std=c11 -Wpedantic -Wall -Wextra -fsanitize=address
LDLIBS=-lm
RM=rm -f

# Fichiers objets pour le programme principal
OBJ_MAIN=testlistemots.o listemots.o
EXE=testlistemots

# Fichiers objets pour statstxt
OBJ_STATS=statstxt.o utils.o listemots.o
STATS_EXE=statstxt

# Fichiers objets pour analysermots
OBJ_ABALYSERMOTS=analysermots.o utils.o listemots.o
ABALYSERMOTS_EXE=analysermots

# Pour produire le fichier exécutable principal
$(EXE): $(OBJ_MAIN)
	$(CC) $(CFLAGS) $(OBJ_MAIN) -o $(EXE) $(LDLIBS)

# Pour produire le fichier exécutable statstxt
$(STATS_EXE): $(OBJ_STATS)
	$(CC) $(CFLAGS) $(OBJ_STATS) -o $(STATS_EXE) $(LDLIBS)

# Pour produire le fichier exécutable statstxt
$(ABALYSERMOTS_EXE): $(OBJ_ABALYSERMOTS)
	$(CC) $(CFLAGS) $(OBJ_ABALYSERMOTS) -o $(ABALYSERMOTS_EXE) $(LDLIBS)

# Pour produire les fichiers objets
testlistemots.o: testlistemots.c listemots.h
	$(CC) $(CFLAGS) -c testlistemots.c

listemots.o: listemots.c listemots.h
	$(CC) $(CFLAGS) -c listemots.c

statstxt.o: statstxt.c listemots.h
	$(CC) $(CFLAGS) -c statstxt.c

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c

# Pour effacer les objets et les exécutables
clean:
	$(RM) $(OBJ_MAIN) $(OBJ_STATS) $(EXE) $(STATS_EXE)

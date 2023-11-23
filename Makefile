#---------------------------------------------------------------------
# Arquivo	: Makefile
# Conteúdo	: compilar o programa main
# Autor		: Náthally Fernandes (nathallyfernandes@ufmg.br)
#---------------------------------------------------------------------
# Opções	: make all - compila tudo
#           : make run - compila o exécutavel 
#			: make clean - remove objetos e executável
#---------------------------------------------------------------------
CC = g++
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/main.o $(OBJ)/indice.o
HDRS = $(INC)/indice.hpp
CFLAGS = -Wall -c -g -I$(INC)

EXE = $(BIN)/pa11.out

run:  $(EXE)
	 ./$(EXE)

all:  $(EXE)

$(BIN)/pa11.out: $(OBJS)
	$(CC) -g -o $(BIN)/pa11.out $(OBJS) $(LIBS)

$(OBJ)/main.o: $(HDRS) $(SRC)/main.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/main.o $(SRC)/main.cpp

$(OBJ)/indice.o: $(HDRS) $(SRC)/indice.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/indice.o $(SRC)/indice.cpp  

 
	
clean:
	rm -f $(EXE) $(OBJS) gmon.out
CFLAGS = -Wall

OBJDIR = objects
BINDIR = bin
MODULESDIR = modules
HEADERDIR = header_files
SRC = main.c $(wildcard $(MODUlESDIR)/*.c)
OBJ = $(OBJDIR)/main.o $(patsubst $(MODULESDIR)/%.c, $(OBJDIR)/%.o, $(wildcard $(MODULESDIR)/*.c))

all: binfolder objfolder bin/main

bin/main: $(OBJ)
	@ echo "Compilando os arquivos objeto no executável"
	cc $(CFLAGS) $(OBJ) -o $@

binfolder:
	@ echo "Criando pasta dos binários"
	mkdir -p $(BINDIR)

objfolder:
	@ echo "Criando pasta dos objetos"
	mkdir -p $(OBJDIR)

$(OBJDIR)/main.o: main.c
	cc $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(MODULESDIR)/%.c $(HEADERDIR)/%.h
	cc $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm $(BINDIR)/* $(OBJDIR)/*
	rmdir $(BINDIR) $(OBJDIR)
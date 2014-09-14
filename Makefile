CC=g++
CFLAGS=-W -Wall -ansi -pedantic
CXXFLAGS=-Wall
LDFLAGS=-lSDLmain -lSDL
EXEC=v3d

OBJDIR=build/
SRCDIR=src/

SRCTEMP=Hello.cpp Main.cpp
OBJTEMP=$(SRCTEMP:.cpp=.o)
SRC=$(addprefix $(SRCDIR), $(SRCTEMP))
OBJ=$(addprefix $(OBJDIR), $(OBJTEMP))

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJDIR)Main.o: $(SRCDIR)Hello.h

$(OBJDIR)%.o: $(SRCDIR)%.cpp
	$(CC) -o $@ -c $< $(CXXFLAGS)


clean:
	rm -rf $(OBJDIR)*.o

mrproper: clean
	rm -rf $(EXEC)

.PHONY: clean mrproper all

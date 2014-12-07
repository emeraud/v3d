CC=g++
CFLAGS=-W -Wall -ansi -pedantic
CXXFLAGS=-Wall -g -std=c++11 -O2
LDFLAGS=-lSDLmain -lSDL -pthread
EXEC=v3d

OBJDIR=build/
SRCDIR=src/

SRCTEMP=Viewer.cpp Triangle.cpp Ray.cpp Tessellation3D.cpp \
KDTree.cpp Object3D.cpp Connector3D.cpp Scene3D.cpp \
Renderer.cpp AnimationManager.cpp Main.cpp

OBJTEMP=$(SRCTEMP:.cpp=.o)
SRC=$(addprefix $(SRCDIR), $(SRCTEMP))
OBJ=$(addprefix $(OBJDIR), $(OBJTEMP))

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

$(SRCDIR)BRDF.h: $(SRCDIR)Material.hpp $(SRCDIR)Types.hpp

$(OBJDIR)Main.o: $(SRCDIR)Viewer.hpp $(SRCDIR)AnimationManager.hpp $(SRCDIR)PreconfiguredScene.hpp \
$(SRCDIR)Scene3D.hpp $(SRCDIR)Renderer.hpp $(SRCDIR)Connector3D.hpp $(SRCDIR)Vec3D.h

$(OBJDIR)AnimationManager.o: $(SRCDIR)Viewer.hpp $(SRCDIR)Renderer.hpp $(SRCDIR)Scene3D.hpp

$(OBJDIR)Renderer.o: $(SRCDIR)Scene3D.hpp $(SRCDIR)Object3D.hpp \
$(SRCDIR)Ray.hpp $(SRCDIR)BRDF.hpp $(SRCDIR)Config.hpp $(SRCDIR)Types.hpp

$(OBJDIR)Scene3D.o: $(SRCDIR)Object3D.hpp

$(OBJDIR)Tessellation3D.o: $(SRCDIR)Triangle.h

$(OBJDIR)KDTree.o: $(SRCDIR)Tessellation3D.hpp $(SRCDIR)BoundingBox.hpp

$(OBJDIR)Connector3D.o: $(SRCDIR)Tessellation3D.hpp

$(OBJDIR)Object3D.o: $(SRCDIR)Tessellation3D.hpp $(SRCDIR)Material.hpp

$(OBJDIR)Triangle.o: $(SRCDIR)Triangle.h

$(OBJDIR)%.o: $(SRCDIR)%.cpp
	$(CC) -o $@ -c $< $(CXXFLAGS)


clean:
	rm -rf $(OBJDIR)*.o

mrproper: clean
	rm -rf $(EXEC)

print_vars:
	echo $(OBJ)

.PHONY: clean mrproper all

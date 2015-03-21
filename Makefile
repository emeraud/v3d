CC=g++
CFLAGS=-W -Wall -ansi -pedantic
CXXFLAGS=-Wall -g -std=c++11 -O2
LDFLAGS=-lSDLmain -lSDL -pthread
EXEC=v3d

OBJDIR=build/
SRCDIR=src/

SRCTEMP=Viewer.cpp Triangle.cpp Ray.cpp Tessellation3D.cpp \
KDTree.cpp Object3D.cpp Connector3D.cpp Scene3D.cpp \
Camera.cpp RenderingPipeline.cpp Renderer.cpp AnimationManager.cpp \
ModelObjectsHelper.cpp ModelScenesHelper.cpp ModelHelper.cpp Model.cpp \
Main.cpp

OBJTEMP=$(SRCTEMP:.cpp=.o)
SRC=$(addprefix $(SRCDIR), $(SRCTEMP))
OBJ=$(addprefix $(OBJDIR), $(OBJTEMP))

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

$(SRCDIR)BRDF.h: $(SRCDIR)Material.hpp $(SRCDIR)Types.hpp

$(OBJDIR)Main.o: $(SRCDIR)Model.hpp $(SRCDIR)ModelHelper.hpp $(SRCDIR)AnimationManager.hpp 

$(OBJDIR)ModelObjectsHelper.o: $(SRCDIR)Tessellation3D.hpp $(SRCDIR)Connector3D.hpp

$(OBJDIR)ModelScenesHelper.o: $(SRCDIR)Model.hpp $(SRCDIR)ModelObjectsHelper.hpp \
$(SRCDIR)Object3D.hpp $(SRCDIR)Scene3D.hpp $(SRCDIR)Camera.hpp \
$(SRCDIR)Vec3D.h $(SRCDIR)Material.hpp $(SRCDIR)Light.hpp $(SRCDIR)Types.hpp

$(OBJDIR)ModelHelper.o: $(SRCDIR)ModelHelper.hpp $(SRCDIR)ModelScenesHelper.hpp

$(OBJDIR)Model.o: $(SRCDIR)Scene3D.hpp $(SRCDIR)Camera.hpp $(SRCDIR)Types.hpp

$(OBJDIR)Viewer.o: $(SRCDIR)Config.hpp

$(OBJDIR)Camera.o: $(SRCDIR)Config.hpp

$(OBJDIR)AnimationManager.o: $(SRCDIR)Viewer.hpp $(SRCDIR)RenderingPipeline.hpp $(SRCDIR)Model.hpp

$(OBJDIR)RenderingPipeline.o: $(SRCDIR)Scene3D.hpp $(SRCDIR)Model.hpp \
$(SRCDIR)Renderer.hpp $(SRCDIR)Types.hpp

$(OBJDIR)Renderer.o: $(SRCDIR)Camera.hpp $(SRCDIR)Scene3D.hpp $(SRCDIR)Object3D.hpp \
$(SRCDIR)Ray.hpp $(SRCDIR)BRDF.hpp $(SRCDIR)Config.hpp $(SRCDIR)Types.hpp $(SRCDIR)Vec3D.h

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

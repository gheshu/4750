CXX = g++
EXE = Renderer.exe
 
INC_DIRS = -I./include
CXXFLAGS = $(INC_DIRS) -std=c++11 -Wfatal-errors -Wall #-fopenmp -DOMP_PARALLEL
LDFLAGS = -L./lib
LDLIBS = .\glfw3.dll -lglew32 -lopengl32 #-fopenmp
 
LINK = $(CXX) -o
COMPILE = $(CXX) -c
 
FILES = main.o renderer.o glsl_program.o image.o window.o input.o objimporter.o vec2.o vec3.o vec4.o mat3.o mat4.o util.o  entitygraph.o transformimporter.o resourcemanager.o camera.o depthbuffer.o
 
.PHONY: clean all run debug release
 
all: $(EXE)
 
debug:	CXXFLAGS += -DDEBUG -g
debug:	$(EXE)

release: CXXFLAGS += -O3
release: $(EXE)

run:	$(EXE)
	./$(EXE)

$(EXE):		$(FILES)
	$(LINK) $(EXE) $(FILES) $(LDFLAGS) $(LDLIBS) 
	
main.o: 	main.cpp
	$(COMPILE) $< $(CXXFLAGS)

%.o: 	%.cpp %.h
	$(COMPILE) $< $(CXXFLAGS)
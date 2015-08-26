CXX = g++
EXE = Renderer.exe
 
INC_DIRS = -I./include
CXXFLAGS = $(INC_DIRS) -std=c++11
LDFLAGS = .\glfw3.dll .\glew32.dll  -L./lib 
LDLIBS = -lopengl32
 
LINK = $(CXX) $(LDFLAGS) $(LDLIBS) -o
COMPILE = $(CXX) $(CXXFLAGS) -c
 
FILES = main.o renderer.o window.o 
 
.PHONY: clean all run debug release
 
all: $(EXE)
 
debug:	CXXFLAGS += -DDEBUG -g
debug:	$(EXE)

release: CXXFLAGS += -O3
release: $(EXE)
 
clean:
	rm -r *.o *.exe *.log

run:	$(EXE)
	clear
	./$(EXE) $(SCENE)

$(EXE): 	$(FILES)
	$(LINK) $(EXE) $(FILES)

%.o: 	%.cpp %.h
	$(COMPILE) $<
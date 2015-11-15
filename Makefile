CXX = g++
EXE = Renderer.exe
 
INC_DIRS = -I./include
CXXFLAGS = $(INC_DIRS) -std=c++11 -Wfatal-errors -Wall
LDFLAGS = -L./lib
LDLIBS = .\glfw3.dll -lglew32 -lopengl32
 
LINK = $(CXX) -o
COMPILE = $(CXX) -c
 
CPP_FILES = $(wildcard *.cpp)
OBJ_FILES = $(CPP_FILES:.cpp=.o)
 
.PHONY: clean all run debug release
 
all: $(EXE)
 
debug:	CXXFLAGS += -DDEBUG -g
debug:	$(EXE)

release: CXXFLAGS += -O3
release: $(EXE)

run:	$(EXE)
	./$(EXE)

clean:
	rm *.o $(EXE)

$(EXE):		$(OBJ_FILES)
	$(LINK) $(EXE) $(OBJ_FILES) $(LDFLAGS) $(LDLIBS) 
	
main.o: 	main.cpp
	$(COMPILE) $< $(CXXFLAGS)

%.o: 	%.cpp %.h
	$(COMPILE) $< $(CXXFLAGS)
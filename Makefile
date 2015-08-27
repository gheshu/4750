CXX = g++
EXE = Renderer.exe
 
INC_DIRS = -I./include
CXXFLAGS = $(INC_DIRS) -std=c++11 
LDFLAGS = -L./lib
LDLIBS = .\glfw3.dll -lglew32 -lopengl32 
 
LINK = $(CXX) -o
COMPILE = $(CXX) -c
 
FILES = main.o renderer.o window.o input.o
 
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
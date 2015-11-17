Currently builds with TDM-GCC-64, glew, and glfw3 on Windows.

Build instructions:
	build <drive letter> <optional target>
	
	targets:
			run: runs the program after building with default flags
			debug: builds with debug flags
			release: builds with optimization flags (-O3)
			parallel: builds (on compilers with openmp support) with threading and optimization
			
	clean.bat removes .o and .exe files.

Controls (requires build release to be interactive):
	W: move forward
	A: move left
	S: move backward
	D: move right
	
	Spacebar: move up
	Left Shift: move down
	
	Mouse: look around
	
	R: reset camera
	1: Moon
	2: TTU Cube
	
	Escape: close program
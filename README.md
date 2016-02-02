Currently builds with TDM-GCC-64, glew, and glfw3 on Windows.
Updated to build on Manjaro using g++, glew, openMP, and glfw3.

Build instructions for Windows:

	build drive target
	
	targets:
			run: runs the program after building with default flags
			debug: builds with debug flags
			release: builds with optimization flags (-O3)
			parallel: builds (on compilers with openmp support) with threading and optimization
			
	clean.bat removes .o and .exe files.
	
Build instructions for Linux:

	make -j parallel

Running instructions:

	make run

Controls:

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
	
![alt tag](http://i.imgur.com/0tsiSn2.png)
![alt tag](http://i.imgur.com/IUEuOcE.png)

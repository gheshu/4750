Currently builds with TDM-GCC-64, glew, and glfw3 on Windows, as well as clang++ and g++ on arch linux.

Windows Build Instructions:
	build <drive letter> <optional target>
	
	targets:
			run: runs the program after building with default flags
			debug: builds with debug flags
			release: builds with optimization flags (-O3)
			
	clean.bat removes .o and .exe files.

Linux Build Instructions:
	make -j release run

Controls (runs better with release target):
	W: move forward
	A: move left
	S: move backward
	D: move right
	
	Spacebar: move up
	Left Shift: move down
	
	Mouse: look around
	
	R: reset camera
	
	Escape: close program

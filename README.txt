Currently builds with TDM-GCC-64, glew, and glfw3 on Windows.

Build instructions:
	build <drive letter> <optional target>
	
	targets:
			run: runs the program after building with default flags
			debug: builds with debug flags
			release: builds with optimization flags (-O3)
			
	clean.bat removes .o and .exe files.
	commit.sh commits changes and prompts for repository log-in.
			
Running:
	Program will capture mouse. Press escape key to close program.
	Loads test.obj from directory and displays it using DDA and Bresenham line drawing algorithms.

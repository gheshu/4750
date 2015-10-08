Currently builds with TDM-GCC-64, glew, and glfw3 on Windows.

Build instructions:
	build <drive letter> <optional target>
	
	targets:
			run: runs the program after building with default flags
			debug: builds with debug flags
			release: builds with optimization flags (-O3)
			
	clean.bat removes .o and .exe files.

default build uses 29,620KB on win7 and has no leaks.
release build uses 33,724KB on win7 and has no leaks.
debug   build uses 29,620KB on win7 and has no leaks.
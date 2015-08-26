#include "renderer.h"
#include <iostream>

using namespace std;

int main()
{
	{
		Renderer renderer;
		renderer.init(1280, 720, 0);
		renderer.draw();
		renderer.destroy();
	}
	printf("Clean exit\n");
	std::cin.ignore();
	return 0;
}

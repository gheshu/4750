#include "renderer.h"
#include <iostream>

using namespace std;

int main()
{
	{
		Renderer renderer;
		renderer.init(800, 600, 0);
		renderer.draw();
		renderer.destroy();
	}
	printf("Clean exit\n");
	return 0;
}

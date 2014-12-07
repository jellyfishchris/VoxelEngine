#include <iostream>
#include "SDLEngine.h"

int main(int argc, char** argv)
{
	Engine* e = new SDLEngine();
	e->GameLoop();

	return 0;
}
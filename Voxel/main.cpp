#include "Engine.h"

int main(int argc, char** argv)
{
	GLenum init = glewInit();
	Engine e;
	e.Initialize(1200,1000,60);
	e.Execute();
	return 0;
}
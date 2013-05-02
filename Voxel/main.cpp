#include "Engine.h"

int main(int argc, char** argv)
{
	Engine e;
	e.Initialize(1200,1000,60);
	e.Execute();
	return 0;
}
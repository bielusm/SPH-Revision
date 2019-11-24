#define USE_MATH_DEFINES
#include "Program.h"


int main()
{
	Program *program = new Program(500,500);
	program->run();

	delete program;

	return 0;
}
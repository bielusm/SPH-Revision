#include "Program.h"


int main()
{
	Program *program = new Program(1000,1000);
	program->run();

	delete program;

	return 0;
}
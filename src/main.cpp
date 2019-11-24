#include "Program.h"


int main()
{
	Program *program = new Program();
	program->run();

	delete program;

	return 0;
}
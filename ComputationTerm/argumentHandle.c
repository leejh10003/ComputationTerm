#include "argumentHandle.h"
argcCheck argumentCheck(int argc, char *argv[])
{
	switch (argc)
	{
	case 2: if (strcmp(argv[1], "-h") != 0) return canContinue; else {};
	case 1:
	default:
		printf("usage: %s inputstring\n", argv[0]);
		return endProgram;
	}
}
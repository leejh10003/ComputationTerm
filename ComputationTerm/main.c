#define PCRE2_CODE_UNIT_WIDTH 8

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SSNCheck.h"
#include "argumentHandle.h"



int main(int argc, char *argv[]) {
	if (argumentCheck(argc, argv) == endProgram) return -1;
	switch (checkSSN(argv[1]))
	{
	case match:
		printf("VALID\n"); break;
	case notMatch:
		printf("INVALID\n"); break;
	case failed:
		printf("wrong in prce\n"); break;
	default:
		printf("Something in wrong\n"); break;
	}
}
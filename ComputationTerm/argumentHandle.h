#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef enum argcCheck {
	canContinue,
	endProgram
}argcCheck;

argcCheck argumentCheck(int argc, char *argv[]);
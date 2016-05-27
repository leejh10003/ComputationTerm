#pragma once
#define PCRE2_CODE_UNIT_WIDTH 8

#include "pcre2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef enum executionResult {
	matched,
	notMatched,
	executionFailed
}executionResult;
executionResult matchCheckInPcre(char pattern[], char inputString[]);
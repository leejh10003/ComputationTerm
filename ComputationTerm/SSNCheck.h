#pragma once
#include "pcreWrap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SSN_SIZE 13
typedef enum determineResult {
	match = matched,
	notMatch = notMatched,
	failed = executionFailed
}determineResult;

determineResult checkSSN(char inputString[]);
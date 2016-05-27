#include "pcreWrap.h"

typedef enum matchOrNot {
	match = matched,
	notMatch = notMatched
}matchOrNot;

typedef enum pcreBuildState {
	pass,
	fail
}pcreBuildState;







static matchOrNot findResult(pcre2_code* re, char inputString[])
{
	pcre2_match_data *match_data = pcre2_match_data_create(20, NULL);
	int rc;
	
	rc = pcre2_match(re, (PCRE2_SPTR)inputString, -1, 0, 0, match_data, NULL);
	pcre2_match_data_free(match_data);

	return rc <= 0 ? notMatch : match;
}



static pcreBuildState buildPcreCode(PCRE2_SPTR pattern, pcre2_code** re)
{
	PCRE2_SIZE erroffset;
	int errorcode;

	*re = pcre2_compile(pattern, -1, 0, &errorcode, &erroffset, NULL);

	if (*re == NULL) return fail;
	return pass;
}



executionResult matchCheckInPcre(char pattern[], char inputString[])
{
	executionResult result;
	pcre2_code *re;

	if (buildPcreCode(pattern, &re) == fail) return executionFailed;
	result = findResult(re, inputString);
	pcre2_code_free(re);

	return result;
}
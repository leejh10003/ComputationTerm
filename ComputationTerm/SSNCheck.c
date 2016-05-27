#include "SSNCheck.h"


determineResult genderCheck(int ssnVec[])
{
	switch (ssnVec[6])
	{
	case 1:
	case 2:
	case 3:
	case 4:
		return match;
	default:
		return notMatch;
	}
}


determineResult lengthCheck(char inputString[])
{
	return strlen(inputString) == SSN_SIZE + 1 ? match : notMatch;
}


int febMaxDay(int year, int day)
{
	if (year % 4 != 0)
		return 29;
	else
		if (year % 100 == 0)
			return 29;
		else
			return 30;
}


determineResult dayInRange(int year, int month, int day)
{
	switch (month)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		if (day < 32) return match; break;
	case 4:
	case 6:
	case 9:
	case 11:
		if (day < 31) return match; break;
	case 2:
		if (day < febMaxDay(year, day)) return match; break;
	}
	return notMatch;
}


determineResult yearMonthDayConstraintCheck(int ssnVec[])
{
	int year = ssnVec[0] * 10 + ssnVec[1];
	int month = ssnVec[2] * 10 + ssnVec[3];
	int day = ssnVec[4] * 10 + ssnVec[5];
	if (month > 12 || month == 0)
		return notMatch;
	return dayInRange(year, month, day);
}


int checksumCalculate(int ssnVec[])
{
	int sum = 0;
	int i;
	for (i = 0; i < SSN_SIZE - 1; i++)
		sum += ssnVec[i] * (i % 8 + 2);
	return 11 - (sum % 11);
}


determineResult checksumCheck(int ssnVec[])
{
	int predictedChecksum;

	predictedChecksum = checksumCalculate(ssnVec);
	return ssnVec[SSN_SIZE - 1] == predictedChecksum ? match : notMatch;
}


void ssnToIntVec(char inputString[], int ssnVec[])
{
	int i;
	for (i = 0; i < SSN_SIZE + 1 ; i++)
		if (i < 6)
			ssnVec[i] = inputString[i] - '0';
		else if (i == 6)
			continue;
		else
			ssnVec[i - 1] = inputString[i] - '0';

	return;
}


determineResult ssnNumericCheck(char inputString[])
{
	int ssnVec[SSN_SIZE];

	if (lengthCheck(inputString) == notMatch)
		return notMatch;

	ssnToIntVec(inputString, ssnVec);


	if (yearMonthDayConstraintCheck(ssnVec) == notMatch)
		return notMatch;

	if (genderCheck(ssnVec) == notMatch)
		return notMatch;

	if (checksumCheck(ssnVec) == notMatch)
		return notMatch;

	return match;
}


determineResult checkSSN(char inputString[])
{
	if (matchCheckInPcre("\\d{6}-\\d{6}", inputString) == notMatch || ssnNumericCheck(inputString) == notMatch)
		return notMatch;
	else
		return match;
}
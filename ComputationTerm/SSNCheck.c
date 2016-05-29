#include "SSNCheck.h"
typedef enum month {
	january=1,
	febuary,
	march,
	april,
	may,
	june,
	july,
	august,
	september,
	october,
	actober,
	november,
	december
}month;


static determineResult lengthCheck(char inputString[])
{
	/*
	 * This function checks length of string. I use this function because regular expression just checks sumstring is in string or not
	 */
	return strlen(inputString) == SSN_SIZE + 1 ? match : notMatch;
}


static int febMaxDay(int year, int day)
{
	/*
	 * This function returns max day of febuary based on year number.
	 */
	if (year % 4 != 0)
		return 29;
	else
		if (year % 100 == 0)
			return 29;
		else
			return 30;
}


static determineResult dayInRange(int year, int month, int day)
{
	/*
	 * This function checks day based on year and month. Feburary's max day is calculated by other function, febMaxDay.
	 */
	switch (month)
	{
	case january:
	case march:
	case may:
	case july:
	case august:
	case october:
	case december:
		if (day < 32) return match; break;
	case april:
	case june:
	case september:
	case november:
		if (day < 31) return match; break;
	case febuary:
		if (day < febMaxDay(year, day)) return match; break;
	}
	return notMatch;
}


static determineResult yearMonthDayConstraintCheck(int ssnVec[])
{
	/*
	 * This function extract date using ssnVec and check weather all number is in right form or not.
	 */
	int year = ssnVec[0] * 10 + ssnVec[1];
	int month = ssnVec[2] * 10 + ssnVec[3];
	int day = ssnVec[4] * 10 + ssnVec[5];
	if (month > 12 || month == 0)
		return notMatch;
	return dayInRange(year, month, day);
}


static int checksumCalculate(int ssnVec[])
{ 
	/*
	 * This function actually calculate checksum number using all number except checksum number.
	 */
	int sum = 0;
	int i;
	for (i = 0; i < SSN_SIZE - 1; i++)
		sum += ssnVec[i] * (i % 8 + 2);
	return 11 - (sum % 11);
}


static determineResult checksumCheck(int ssnVec[])
{
	/*
	 * This function weather or not checksum number is in right form or not.
	 */
	int predictedChecksum;

	predictedChecksum = checksumCalculate(ssnVec);
	return ssnVec[SSN_SIZE - 1] == predictedChecksum ? match : notMatch;
}


static void ssnToIntVec(char inputString[], int ssnVec[])
{
	/*
	 * This function convert SSN string into integer vector.
	 * Not a check routine, but needed for other checking.
	 */
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


static determineResult ssnNumericCheck(char inputString[])
{
	/*
	 * This function checks SSN is in right form in numeric terms.
	 */
	int ssnVec[SSN_SIZE];

	if (lengthCheck(inputString) == notMatch)
		return notMatch;

	ssnToIntVec(inputString, ssnVec);


	if (yearMonthDayConstraintCheck(ssnVec) == notMatch)
		return notMatch;


	if (checksumCheck(ssnVec) == notMatch)
		return notMatch;

	return match;
}


determineResult checkSSN(char inputString[])
{
	/*
	 * This Function is called from other file, main.c.
	 * This function determine checks weather or not SSN is in right form.
	 */
	if (matchCheckInPcre("\\d{6}-[1+2]\\d{6}", inputString) == notMatch || ssnNumericCheck(inputString) == notMatch)
		return notMatch;
	else
		return match;
}
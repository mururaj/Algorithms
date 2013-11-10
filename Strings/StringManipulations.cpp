#include<stdio.h>

#define MAXLENGTH 5
int strlength(char *inputString);

int main()
{
	char Str1[MAXLENGTH],Str2[MAXLENGTH];
	int strCompare(char *inputString1,char *inputString2);
	char *strConcat(char *Str1,char *Str2);
	int str1Length,str2Length;
	printf("Enter Str1\n");
	scanf("%s",Str1);
	printf("Enter Str2\n");
	scanf("%s",Str2);

	str1Length = strlength(Str1);
	str2Length = strlength(Str2);

	// Exit if strings go out of bounds
	if ( str1Length >= MAXLENGTH || str2Length >= MAXLENGTH )
	{
		printf("Array index out of bounds error\n");
		printf("Exiting \n");
		return 0;
	}

	printf("Length of %s %d \n",Str1,str1Length);
	printf("Length of %s %d \n",Str2,str2Length);

	if(strCompare(Str1,Str2))
	{
		printf("Str1 & Str2 are equal\n");
	}
	else
	{
		printf("Str1 & Str2 are unequal\n");
	}

	printf("Concatenation of Str1 & Str2 %s\n",strConcat(Str1,Str2));

	return 1;
}

/*
Func strlength: returns length of the inputString
Args:
"inputString" input string for which length to be computed
*/
int strlength(char *inputstring)
{
	int strlength = 0;

	// loop till end of the string
	while( *inputstring != '\0')
	{
		strlength++;
		inputstring++;
	}

	return strlength;
}


/*
Func strCompare: Check if two strings are equal. Returns
1 if equal otherwise 0
Args: 
"inputString1" first string 
"inputString2" second string
*/
int strCompare(char *inputString1,char *inputString2)
{

	// if length of the string are not equal, return 0
	if(strlength(inputString1) != strlength(inputString2))
	{
	return 0;
	}

	// Loop till end of one of the string
	while(*inputString1 != '\0')
	{
		if(*inputString1 != *inputString2)
		{
			return 0;
		}
		inputString1++;
		inputString2++;
	}

	return 1;
}

/*
Func strConcat: Append appendString to targetString and
returns concatenated String
Args:
"targetString" will hold source + append strings 
"appendString" String to be appended
*/
char *strConcat(char *targetString,char *appendString)
{
	char *tempString = targetString;
	int targetLength = strlength(targetString);

	// check if target string long enough to include appendString
	if(strlength(targetString) + strlength(appendString) > MAXLENGTH)
	{
		printf("The length of target string is not enough to append Str2\n");
	}

	// Move till end of targetString
	tempString = tempString + targetLength;

	// Loop till end of appendString
	while(*appendString != '\0')
	{

		// if length of target goes out of bound, break
		if(targetLength >= MAXLENGTH-1)
		{
		printf("targetLength %d >= MAXLENGTH-1\n",targetLength);
		break;
		}

		*tempString = *appendString;
		appendString++;
		tempString++;
		targetLength++;
	}
// String termination character
*tempString = '\0';

return targetString;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLENGTH 100

int spaceArr[MAXLENGTH];

int main()
{
	char inputStr[MAXLENGTH];
	char tmpChar;
	int lowerIndex,upperIndex,spaceArrIndex;
	int reverseString(int lowerIndex,int upperIndex,char str[]);

	printf("Enter your name\n");
	gets(inputStr);

	lowerIndex=0;
	upperIndex=strlen(inputStr)-1;
	spaceArrIndex = 0;
	
	reverseString(lowerIndex,upperIndex,inputStr);

	puts(inputStr);	
	
	

	while (spaceArr[spaceArrIndex] != -1)
	{
		if (spaceArrIndex == 0)
		{
			lowerIndex = 0;
		}
		else {
			lowerIndex = upperIndex + 2;
		}
		upperIndex = spaceArr[spaceArrIndex++] -1;
		
		printf("Calling with lowerIndex %d and upperIndex %d\n",lowerIndex,upperIndex);
		reverseString(lowerIndex,upperIndex,inputStr);

	}

	lowerIndex = upperIndex + 2;
	upperIndex = strlen(inputStr) -1;

	reverseString(lowerIndex,upperIndex,inputStr);
	
	puts(inputStr);

	return 0;
}


int reverseString(int lowerIndex,int upperIndex,char inputStr[])
{	
	int spaceArrIndex = 0;
	char tmpChar;
	int spaceFlag = 0;

	while (lowerIndex<upperIndex)
	{
		tmpChar = inputStr[lowerIndex];
		inputStr[lowerIndex] = inputStr[upperIndex];
		if (inputStr[upperIndex] == ' ')
		{
			spaceArr[spaceArrIndex++] = lowerIndex;
			spaceFlag = 1;
		}
		inputStr[upperIndex] = tmpChar;

		lowerIndex++;
		upperIndex--;
	}

	if (spaceFlag)
	{
		printf("Space array terminated\n");
		spaceArr[spaceArrIndex] = -1;
	}

	return 1;
}

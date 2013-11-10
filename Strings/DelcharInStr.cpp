/*
Author: Muruganantham Raju
Date: 01/17/2012
Program to delete chars in input string
*/
# include <stdio.h>
# define MAXSTRLEN 100
# define SEARCHLEN 256

int main()
{
	char oldString[MAXSTRLEN];
	char newString[MAXSTRLEN];
	int matchString[SEARCHLEN];
	int oldStringIndex=0,newStringIndex=0;
	char ch;

	// get input string
	printf("Please enter source string\n");
	gets(oldString);

	// Initialize match array
	for (int i=0;i<SEARCHLEN;i++)
	{
		matchString[i] = 0;
	}

	printf("Please enter delete chars. Enter ! to exit\n");
	// Get character and set equivalent index position to 1
	while ((ch = getchar()) != '!')
	{
		matchString[(int)ch] = 1;
	}

	while (oldString[oldStringIndex] != '\0')
	{
		// If this char is not found in removal list, store
		if (matchString[(int)oldString[oldStringIndex]] != 1 )
		{
			newString[newStringIndex++] = oldString[oldStringIndex];
		}
		oldStringIndex++;
	}

	// Terminate the new string
	newString[newStringIndex] = '\0';

	printf("String after removal %s \n",newString);
}

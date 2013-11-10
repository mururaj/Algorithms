#include <stdio.h>

#define ARRAYSIZE 5

int main(int argc, char *argv[])
{
	unsigned int inputArr[ARRAYSIZE];
	char tempStr[ARRAYSIZE][5];

	int sortStrArr(char [][5]);

	for (int i=0;i<ARRAYSIZE;i++)
	{
		scanf("%u",&inputArr[i]);
	}
	
	for (int i=0;i<ARRAYSIZE;i++)
	{
		sprintf(tempStr[i],"%d",inputArr[i]);
		printf("%s\n",tempStr[i]);		
	}
	
	sortStrArr(tempStr);

	return 1;
}

int sortStrArr(char strArr[][5])
{
	for (int i=0;i<ARRAYSIZE;i++)
	{

	}	
}

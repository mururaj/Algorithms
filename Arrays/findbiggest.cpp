#include <stdio.h>
#include <stdlib.h>
#define MAXLENGTH 10

int main()
{
	int a[MAXLENGTH];
	int printArray(int *);
	int thirdBiggest(int *);
	for (int i=0;i<MAXLENGTH;i++)
	{
		a[i] = rand() % 10 + 1;
	}

	printArray(a);

	printf("Third biggest element is %d",thirdBiggest(a));

	printArray(a);

	return 0;
}

int printArray(int *inputArr)
{
	for (int i=0;i<MAXLENGTH;i++)
	{
		printf("%d ",*(inputArr + i));
	}
}

int thirdBiggest(int *inputArr)
{
	int firstBig =0, secBig = 0, thirdBig =0;
	for (int i=0;i<MAXLENGTH;i++)
	{
		if ( *(inputArr + i) > firstBig )
		{
			thirdBig = secBig;
			secBig = firstBig;
			firstBig = *(inputArr + i);
		} else if ( *(inputArr + i) > secBig && *(inputArr + i) != firstBig )
		{
			thirdBig = secBig;
			secBig = *(inputArr + i);
		} else if ( *(inputArr + i) > thirdBig && *(inputArr + i) != secBig )
		{
			thirdBig = *(inputArr + i);
		}
	}

	return thirdBig;
}

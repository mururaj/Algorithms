#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLEN 6
int main()
{
	char str[MAXLEN];
	int tmp = 0 , num =0, i;
	
	printf("Enter input string");
	scanf("%s",str);

	
	for (i=0;i<strlen(str);i++)
	{
		if (i==0)
		{
			if (!isdigit(str[i]) && str[i] != '-')
			{
				printf("Non integer string\n");
				return 0;
			}
		}
		else if (!isdigit(str[i]))
		{
				printf("Non integer string\n");
				return 0;
		}
	}

	if (str[0] == '-')
	{
		i=1;
	}
	else 
	{
		i=0;
	}

	for (;i<strlen(str);i++)
	{
		 tmp = str[i] - '0';
		 num = num * 10 + tmp;		 
	}

	if (str[0] == '-')
	{
		num = num * -1;
	}
	
	printf("The converted number is %d \n", num);
	return 0;
}

#include <stdio.h>

int main()
{
	int num = 100;
	chat *str = (char *) num;
	
	printf("%s \n",str);
	return 0;
}

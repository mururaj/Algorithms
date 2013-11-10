#include <stdio.h>

int main()
{
	int a = 10, b =20;
	int c[8];
	static int d[] = { 1, 2, 3, 4, 5, 6 };
	int *p[] = { d, d+1, d+2, d+3, d+4, d+5, d+6 };
	printf("%d\n",&a - &b); // This is an undefined/unrecommended behavior
	printf("%d\n",&c[7] - &c[0]); // This is an undefined/unrecommended behavior

	for (int i=1;i<=6;i++)
	{
		printf("p=%p *p=%p **p=%d\n",p,*p,**p);
	}
	
	return 1;	
}

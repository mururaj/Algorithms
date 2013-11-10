#include <stdio.h>

struct byte
{
	unsigned a: 1;
	unsigned b: 1;
	unsigned c: 1;
	unsigned d: 1;
	unsigned e: 1;
	unsigned f: 1;
	unsigned g: 1;
	unsigned h: 1;
};

union bits {
	char ch;
	struct byte bit;
}ascii;

void decode(union bits b);

int main()
{
	do
	{
		ascii.ch = getchar();
		decode(ascii);
	}
	while (ascii.ch!='q');
	return 0;
}

void decode(union bits b)
{
	if (b.bit.h)
	{
		printf("1 ");
	} else
	{
		printf("0 ");
	}

	if (b.bit.g)
	{
		printf("1 ");
	} else
	{
		printf("0 ");
	}

	if (b.bit.f)
	{
		printf("1 ");
	} else
	{
		printf("0 ");
	}


	if (b.bit.e)
	{
		printf("1 ");
	} else
	{
		printf("0 ");
	}

	if (b.bit.d)
	{
		printf("1 ");
	} else
	{
		printf("0 ");
	}

	if (b.bit.c)
	{
		printf("1 ");
	} else
	{
		printf("0 ");
	}

	if (b.bit.b)
	{
		printf("1 ");
	} else
	{
		printf("0 ");
	}

	if (b.bit.a)
	{
		printf("1 ");
	} else
	{
		printf("0 ");
	}

	printf("\n");
	
}


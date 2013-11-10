#include <stdio.h>
#define NUMBITS 8

int main()
{
	unsigned int bit;
	unsigned int num = 5236784;

	void printBinary(unsigned int num);

	printBinary(num);

	bit = 1u << ( (sizeof(bit)* NUMBITS) -1 );

	// Reverse the bits in num
	for (int i=0;i<((sizeof(bit) * NUMBITS)/2);i++)
	{
		char leftBit,rightBit;

		//get the leftbit
		if (num & ( 1u << i ))
		{
			leftBit = '1';
		} else
		{
			leftBit = '0';
		}

		// get the rightbit
		if (num & ( bit >> i))
		{
			rightBit ='1';
		} else
		{
			rightBit = '0';
		}

		// swap the bits
		if (leftBit == '1')
		{
			num = num | ( bit >> i );
		} else
		{
			num = num & ~(bit >> i );
		}

		if (rightBit == '1')
		{
			num = num | ( 1u << i );
		} else
		{
			num = num & ~(1u << i );
		}
	}

	printBinary(num);

	return 0;
}

// Following function print the binary equivalent of given number
void printBinary(unsigned int num)
{
	unsigned int bit;

	// print binary equivalent of decimal number
	for (bit = 1u << ( (sizeof(bit)* NUMBITS) -1 );bit;bit = bit >> 1 )
	{
		printf("%c",num & bit? '1':'0');
	}

	printf("\n");

}

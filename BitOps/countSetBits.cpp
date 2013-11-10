#include <stdio.h>
#include <limits.h>
# define BYTE 8

int main()
{
	unsigned int num;
	unsigned int bitBybitCheck(unsigned int num);
	unsigned int LehmerCount(unsigned int num);
	unsigned int optimizedBitCheck(unsigned int num);
	printf("Enter an unsigned integer \n");
	scanf("%u",&num);
	printf("The number of set bits %u \n", bitBybitCheck(num));
	printf("The number of set bits %u \n", LehmerCount(num));
	printf("The number of set bits %u \n", optimizedBitCheck(num));
	return 0;
}

unsigned int bitBybitCheck(unsigned int num)
{
	int i =0, count =0;

	while (i< (sizeof(num) * BYTE))
	{
		if ( num & (1 << i))
		{
			count++;
		}
	 i++;
	}

	return count;

}

unsigned int LehmerCount(unsigned int num) {     
  unsigned int c; // c accumulates the total bits set in v
  for (c = 0; num; c++) 
    {   num &= num - 1; 	  
	}// clear the least significant bit set
  return c;
}

unsigned int optimizedBitCheck(unsigned int num)
{
	const int totalBits = sizeof(num) * CHAR_BIT;
	
	// Get the MSB
	unsigned int maskBit = 1u << (totalBits - 1);

	int i=0;
	unsigned int totalSetBits=0;

	while (i<totalBits)
	{
		// don't shift first time
		if (i != 0)
		{
			num = num << 1;
		}
		
		// always check if MSB is set
		if (num & maskBit)
		{
			++totalSetBits;
		}

		i++;
	}

	return totalSetBits;    
}

#include <stdio.h>

#define SET 1
#define CLEAR 0

typedef struct ipMsg
{
	unsigned char ipV4:1;
	unsigned char TCP:1;
	unsigned char urgentPtr:1;
};

int main()
{
	ipMsg dc1ipMsg;
	int bitPosition;
	int setField(int bitPosition, ipMsg *msg, int enabler);
	void checkIpMsgStatus(ipMsg msg);

	printf("setting ipV4 for DC1\n");
	bitPosition = 1;
	
	if (!setField(bitPosition,&dc1ipMsg,SET))
	{
		printf("Invalid bitPosition\n");
	}

	printf("Setting UDP for DC1\n");
	bitPosition = 2;

	if (!setField(bitPosition,&dc1ipMsg,CLEAR))
	{
		printf("Invalid bitPosition\n");
	}

	printf("Setting urgent pointer for DC1\n");
	bitPosition = 3;

	if (!setField(bitPosition,&dc1ipMsg,SET))
	{
		printf("Invalid bitPosition\n");
	}

	checkIpMsgStatus(dc1ipMsg);

	printf("The size of msg is %d\n",sizeof(dc1ipMsg));
	printf("The size of integer is %d\n",sizeof(int));
	
	
}

int setField(int bitPosition, ipMsg *msg, int enabler)
{
	switch(bitPosition)
	{
		case 1:
				msg->ipV4 = enabler;
				break;		
		case 2:
				msg->TCP = enabler;
				break;
		case 3:
				msg->urgentPtr = enabler;
				break;
		default:
				return 0;
	}
	return 1;
}


void checkIpMsgStatus(ipMsg msg)
{
		if (msg.ipV4)
		{
			printf("The message is IP4\n");
		} else
		{
			printf("The message is IP6\n");
		}

		if (msg.TCP)
		{
			printf("The protocol is TCP\n");
		} else
		{
			printf("The protocol is UDP\n");
		}


		if (msg.urgentPtr)
		{
			printf("Urgent Pointer is set\n");
		} else
		{
			printf("Urgent Pointer is unset\n");
		}

}

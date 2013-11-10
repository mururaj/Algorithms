#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define MAXLENGTH 20
#define BUFFERLENGTH 256

int main(int argc, char *argv[])
{
	char source[MAXLENGTH],target[MAXLENGTH];
	int rawCopy(char source[],char target[]);

	printf("Enter name of source file\n");
	gets(source);

	printf("Enter name of destination file\n");
	gets(target);

	if (strlen(source) >= MAXLENGTH || strlen(target) >=MAXLENGTH )
	{
		printf("Length of source and destination file name range exceeded\n");
		printf("Valid file name length: 1 to %d",MAXLENGTH-1);
		return 0;
	}

	if (rawCopy(source,target))
	{
		printf("File copy is successful\n");
	}
	else 
	{
		printf("File copy failed\n");
		return 0;
	}
	
	return 1;
}

int rawCopy(char source[],char target[])
{
	char buffer[BUFFERLENGTH];
	int numBytes;
	int sourceHandle, targetHandle;

	sourceHandle = open(source, O_RDONLY);

	if (sourceHandle == -1)
	{
		printf("Unable to open the source file\n");
		return 0;
	}

	targetHandle = open(target, O_CREAT | O_WRONLY, S_IWRITE);

	if (targetHandle == -1)
	{
		printf("Unable to create target file\n");
		return 0;
	}

	while(1)
	{
		numBytes = read(sourceHandle,buffer,BUFFERLENGTH);
		
		if (numBytes < 1)
		{
			break;
		}

		write(targetHandle,buffer,numBytes);
	}

	close(sourceHandle);
	close(targetHandle);

	return 1;
	

}

/* Aythor: Muruganantham Raju 
A simple program to encrypt and decrypt -
a file using 1's complement operator
*/

#include <stdio.h>
#include <string.h>

#define MAXLENGTH 30

int main()
{
	char sourceFileName[MAXLENGTH];
	int encryptFileLength = MAXLENGTH + 11;
	char encryptFileName[encryptFileLength];
	char decryptFileName[encryptFileLength];
	int encryptFile(char fileName[],char encryptFileName[]);
	int decryptFile(char encryptfileName[],char decryptFileName[]);
	
	printf("Enter the name of file\n");
	scanf("%s",sourceFileName);

	if (strlen(sourceFileName) > MAXLENGTH-1 || strlen(sourceFileName) < 1 )
	{
		printf("File name must be within range of 1 to %d\n",MAXLENGTH-1);
		return 0;
	}

	sprintf(encryptFileName,"%s_encrypted",sourceFileName);

	if (strlen(encryptFileName) > encryptFileLength-1 || strlen(encryptFileName) < 1 )
	{
		printf("File name must be within range of 1 to %d\n",encryptFileLength-1);
		return 0;
	}

	sprintf(decryptFileName,"%s_decrypted",sourceFileName);

	if (strlen(decryptFileName) > encryptFileLength-1 || strlen(decryptFileName) < 1 )
	{
		printf("File name must be within range of 1 to %d\n",encryptFileLength-1);
		return 0;
	}

	if (encryptFile(sourceFileName,encryptFileName))
	{
		if (!decryptFile(encryptFileName,decryptFileName))
		{
			printf("File decryption failed \n");
			return 0;
		}
	}
	else
	{
		printf("File encryption failed \n");
		return 0;
	}
	
	return 1;
}

/*
Func encryptFile: read input file char by char and 
store encrypted data into encrptFile
Args:
"fileName[]" source file name
"encryptFileName[]" name of encrypted file
*/
int encryptFile(char fileName[],char encryptFileName[])
{
	FILE *sfp,*enfp;
	char fileData;
	
	sfp = fopen(fileName,"r");
	enfp = fopen(encryptFileName,"w");

	
	if (sfp == NULL || enfp == NULL)
	{
		printf("Error in opening files\n");
		return 0;
	}

	//Read each character till EOF
	while ( (fileData = getc(sfp)) != EOF )
	{
		// write encrupted data into new file
		putc(~fileData,enfp);
	}

	fclose(sfp);
	fclose(enfp);

	return 1;
}

/*
Func decryptFile: read encrypted file char by char and 
decrypt data into decryptFile
Args:
"encryptFile[]" name of encryptFile
"decryptFile[]" name of decryptFile
*/
int decryptFile(char encryptFile[],char decryptFile[])
{
	FILE *enfp,*defp;
	char fileData;
	
	enfp = fopen(encryptFile,"r");
	defp = fopen(decryptFile,"w");

	if (enfp == NULL || defp == NULL)
	{
		printf("Error in opening files\n");
		return 0;
	}

	// Read encrypted file char by char
	while ( (fileData = getc(enfp)) != EOF )
	{
		// decrypt data and store in decryptFile
		putc(~fileData,defp);
	}

	fclose(enfp);
	fclose(defp);

	return 1;
}

/**
 * 
 * Inmplementation of "input_handeler.c"
 * 
*/


#include "input_handeler.h"

int ValidInput(char* inputPtr)
{

	char* inputCopyPtr = inputPtr;

	// assume that input has max size of 30
	int bracesCount = 0;
	int commaCount = 0;
		
	for(int checkedinputSize = 0; checkedinputSize <= 30; ++checkedinputSize, ++inputPtr)
	{
		if(*inputPtr == '(' || *inputPtr == ')')
		{
			++bracesCount;
		}

		else if(*inputPtr == ',')
		{
			++ commaCount;
		}
		
		// checking if number arg is valid which is between '(' and ','
		else if(bracesCount == 1 && commaCount == 0)
		{
			if(!isdigit(*inputPtr))
			{
				printf("\nInvlaid input: %s\n", inputCopyPtr);
				printf("Error: number argument can only be number\n");
				return -1;
			}
		}
		// checking if qt arg is valid which is between ',' and ')'
		else if(bracesCount == 1 && commaCount == 1)
		{
			// checking if it is a valid number
			if(!isdigit(*inputPtr))
			{
				printf("\nInvlaid input: %s\n", inputCopyPtr);
				printf("Error: qt argument can only be number\n");
				return -1;
			}
		}
		
	}

	if(bracesCount == 2 && commaCount	== 1)
	{
		return 1;
	}
	else
	{
		// error
		printf("\nInvlaid input: %s\n", inputCopyPtr);
		printf("Error: braces Count: %d, comma counnt: %d\n", bracesCount, commaCount);
		return -1;
	}
}

char* GetInputProcessName(char* inputPtr)
{
	// assumes that filename starts from the start of the
	// input till it reaches (
	
	char filename[30];
	int filenameLength = 0;

	while(*inputPtr != '(')
	{
		// do not parse ' '
		if(*inputPtr != ' ')
		{
			filename[filenameLength] = *inputPtr; 
			++filenameLength;
		}
		++inputPtr;
		
	}

	// as we now know the length of filename 
	// dynamically allocating memory according to the final length + 1 (for \0) 
	// of the char arr to return it 
	char* returnFileNamePtr = (char*)calloc(filenameLength +1, sizeof(char*));

	// copying the filename into the returnFileNamePtr
	for(int i = 0; i < filenameLength; ++i)
	{
		returnFileNamePtr[i] = filename[i];
	}
	return returnFileNamePtr;

}

char* GetInputNumArg(char* inputPtr)
{
	// assumes that Number argument starts after '('
	// and ends before ',' 
	
	char numArg[30];
	int numArgLength = 0;

	// getting to '(' char in the inputPtr
	while(*inputPtr != '(')
	{
		++inputPtr;
	}

	++inputPtr; // inputptr was pointing at '('

	// numArgs ends with ','
	while(*inputPtr != ',')
	{
		// do not parse ' '
		if(*inputPtr != ' ')
		{
			numArg[numArgLength] = *inputPtr; 
			++numArgLength;
		}
		++inputPtr;
	}

	// as we now know the length of numArg 
	// dynamically allocating memory according to the final length + 1 (for \0) 
	// of the char arr to return it 
	char* returnNumArgPtr = (char*)calloc(numArgLength +1, sizeof(char*));

	// copying the numArg into the returnNumArgPtr
	for(int i = 0; i < numArgLength; ++i)
	{
		returnNumArgPtr[i] = numArg[i];
	}

	return returnNumArgPtr;
}

char* GetInputQtArg(char* inputPtr)
{
	// assumes that qt argument starts after ','
	// and ends before ',' 
	
	char qtArg[30];
	int qtArgLength = 0;

	// getting to ',' char in the inputPtr
	while(*inputPtr	!= ',')
	{
		++inputPtr;
	}

	++inputPtr; // inputptr was pointing at ','

	// numArgs ends with ')'
	while(*inputPtr != ')')
	{
		// do not parse ' '
		if(*inputPtr != ' ')
		{
			qtArg[qtArgLength] = *inputPtr; 
			++qtArgLength;
		}
		++inputPtr;
	}

	// as we now know the length of qtArg 
	// dynamically allocating memory according to the final length + 1 (for \0) 
	// of the char arr to return it 
	char* returnQtArgPtr = (char*)calloc(qtArgLength +1, sizeof(char*));

	// copying the qtArg into the returnQtArgPtr
	for(int i = 0; i < qtArgLength; ++i)
	{
		returnQtArgPtr[i] = qtArg[i];
	}

	return returnQtArgPtr;
}

char IsInputBg(char* inputPtr)
{
	// a process is only bg if it is processName(n,qt)&
	// process&(n,qt) is not a background process
	for(int checkedinputSize = 0; checkedinputSize <= 29; ++checkedinputSize, ++inputPtr)
	{
		if(*inputPtr == ')' && *(inputPtr+1) == '&' )
		{
			return 1;
		}
	}	
	
	return 0;
}


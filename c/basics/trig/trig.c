#include <stdio.h>
#include "trig.h"

/* input limits */ 
#define MAX_LINES 40
#define MIN_LINES 0 
#define MAX_CHAR '~'
#define MIN_CHAR '!'

/* static functions */
static int PrintForFunc5(int lines, char ch, int spaces);
static int CheckParameters(int lines, char ch);
static void PrintLine (int size, char symbol);

int trig1(int lines, char ch)
{
    int i = 0;
    int status = 0;
 	
	if ((status = CheckParameters(lines, ch)) == TRIG_OK)
	{
		for (i = 1; i <= lines; ++i)
    	{
			PrintLine(i, ch);
            putchar('\n');
    	}
	}

	return status;
}

int trig2(int lines, char ch)
{
    int i = 0;
    int status = 0; 

	if ((status = CheckParameters(lines, ch)) == TRIG_OK)
	{
		for (i = lines; i > 0; --i)
    	{
			PrintLine(i, ch);
            putchar('\n');
    	}
	}

	return status;
}

int trig3(int lines, char ch)
{
	int status = 0;
	 	
	status = trig1(lines,ch);
	
	if (status == TRIG_OK)
	{
		status = trig2(lines - 1, ch);
	}

	return status;
    

}


int trig4(int lines, char ch)
{
    int i = 0;
    int status = 0;
    int size = 1;
    int spaces = lines - 1;
    
	if ((status = CheckParameters(lines, ch)) == TRIG_OK)    
	{
		for (i = 0; i < lines; ++i,--spaces, size += 2)
		{
        	PrintLine(spaces, ' ');
			PrintLine(size, ch);
        	putchar('\n');
    	}
	}

	return status; 
}

int trig5(int lines, char ch)
{
    return PrintForFunc5(lines, ch, 0);
}

static int PrintForFunc5(int lines, char ch, int spaces)
{
    int i = 0;
    int status = 0;
    int size = lines * 2 - 1;
    
	if ((status = CheckParameters(lines, ch)) == TRIG_OK)    
	{
    	for (i = 0; i < lines; ++i,++spaces, size -= 2)
   		{
		 	PrintLine(spaces, ' ');
			PrintLine(size, ch);
			putchar('\n');
		 }
	}
	
	return status; 
}

int trig6(int lines, char ch)
{
	int status = 0;
    
	if ((status = CheckParameters(lines, ch)) == TRIG_OK)
	{
		trig4(lines, ch);
    	PrintForFunc5(lines - 1, ch, 1);
	}

	return status;
}
/* ===================== static functions =============================*/
static int CheckParameters(int lines, char ch)
{
		
	if (ch < MIN_CHAR || ch > MAX_CHAR)
	{
		return CHAR_ERROR;
	} 
    
	if ( lines <= MIN_LINES|| lines > MAX_LINES)
	{
		return SIZE_ERROR;
	}
	
	return TRIG_OK;
}

static void PrintLine (int size, char symbol)
{
	int i = 0;

	for (i = 0; i < size ;++i)
    {
          putchar(symbol);
    }
}
        


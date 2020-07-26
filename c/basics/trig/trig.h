#define TRIG_OK 0
#define SIZE_ERROR -1
#define CHAR_ERROR -2

int trig1(int lines, char ch);
/*
input: 
lines - number of lines
ch- char symbol

output:
ch
ch ch
ch ch ch
ch ch ch ch

error:
error cases
ch error- return CHAR_ERROR (-1)
size error - return SIZE_ERROR (-2)

*/
int trig2(int lines, char ch);
/*
input: 
lines - number of lines
ch- char symbol

output:
ch ch ch ch
ch ch ch
ch ch
ch

error:
error cases
ch error- return CHAR_ERROR (-1)
size error - return SIZE_ERROR (-2)

*/
int trig3(int lines, char ch);
/*
input: 
lines - number of lines
ch- char symbol

output:
ch
ch ch
ch ch ch
ch ch ch ch
ch ch ch
ch ch
ch

error:
error cases
ch error- return CHAR_ERROR (-1)
size error - return SIZE_ERROR (-2)

*/
int trig4(int lines, char ch);
/*
input: 
lines - number of lines
ch- char symbol

output:
      ch
   ch ch ch
ch ch ch ch ch

error:
error cases
ch error- return CHAR_ERROR (-1)
size error - return SIZE_ERROR (-2)

*/
int trig5(int lines, char ch);
/*
input: 
lines - number of lines
ch- char symbol

output:
ch ch ch ch ch
   ch ch ch
      ch

error:
error cases
ch error- return CHAR_ERROR (-1)
size error - return SIZE_ERROR (-2)

*/
int trig6(int lines, char ch);
/*
input: 
lines - number of lines
ch- char symbol

output:

      ch
   ch ch ch
ch ch ch ch ch
   ch ch ch
      ch


error:
error cases
ch error- return CHAR_ERROR (-1)
size error - return SIZE_ERROR (-2)

*/



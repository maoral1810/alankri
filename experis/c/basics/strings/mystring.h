#define OK 0
#define INPUT_ERROR -2
#define ARR_LENGTH(x)(sizeof(x) / sizeof(x[0]))

int ReverseString(char *str);
/*
the function reverse string(in place) 

input:
str- string

output:
string in reverse string

error:
return INPUT_ERROR if str = null

*/
int DecToBin(int num);
/*
the function get integer and print is binary 

input:
str- string

output:
binary presentation of num

error:
return INPUT_ERROR if num < 0

*/

int Squeeze(char *str1, const char *str2);

int MyAtoi(char *str, int *res);

int MyItoa(int num, char *res);

int Location(char *s1, char *s2);
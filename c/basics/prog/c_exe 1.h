/* 
c_exe_1_h_ file 
programar: Maor Alankri
version: 1
last update: 31.10.19
*/

#define SUCSSES 0
#define NOT_IN_RANGE -1
#define FAIL 1

void CalAndPrint(int a, int b);
/*
the function calculate and print the resualst for 2 integers numbers:
1- a + b
2- a - b
3- a * b

input:
2 int

output:

non(only print)

error:


*/

int Factorial(int num);
/* 
the function get an integer and return the factorial of this integer 

intput: 
an integer number

output:
print the factorial of num

error:

SUCSSES if the number isn't in the limits of -20 < num < 20
else return FAIL

*/

int IsPalindrome(int num);
/* 
the function get an integer and check if the number is a palindrom

example:

1221 or 12221- is palindrome
1324 -isn't palindrome

intput: 
an integer number

output:

SUCSSES if is palindrome
FAIL if it isn't palindrome

error:
*/

int IsAccendingOrder(int num);
/* 
the function get an integer and check if the number is in accendingorder
example:

1234- is in accendig order
1324 - isn't in accending order

intput: 
an integer number

output:

SUCSSES if num is in  accendig order
FAIL if num isn't in accendig order
error:

*/

int IsPrimeNumber(int num);
/* 
the function get an integer and check if the number is prime
(divide only in 1 and himself)

example:

7- is prime number
6 - isn't prime number

intput: 
an integer number

output:

SUCSSES if num is prime 
FAIL if num isn't prime 

error:

*/

int ReverseNum(int num);
/* 
the function get an integer and return is mirror number

example:

num = 12435 res = 53421

intput: 
an integer number

output:

mirror number

error:

*/

void PrintAmstrongNum(void);

/* 
the function print all amstrung number from 1-999

intput: 


output:
print all amstrung number from 1-999


error:

*/


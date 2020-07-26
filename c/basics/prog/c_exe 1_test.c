#include "c_exe 1.h"
#include <stdio.h> 	    /* printf, scanf */ 

int main(void)
{
	int a = 0;
	int b = 0;
    int res  = 0;

	printf("\n======================= MultAndSum ======================\n");	
	printf("please insert 2 integer numbers\n");
	scanf("%d",&a);
	scanf("%d",&b);
	CalAndPrint(a,b);

	printf("\n========================= Factorial ========================\n");	
	printf("please enter a number for factorial\n");
	scanf("%d",&a);
    res = Factorial(a);
	!res ? printf("num isn't in range of int for factorial\n")
         : printf("the fectorial of %d is %d \n", a, res);

	printf("\n======================= IsPalindrome ========================\n");
    printf("please enter a number for Palindrome\n");
	scanf("%d",&a);	
	IsPalindrome(a) ? printf("isn't palindrome\n") : printf("is palindrome\n");
    
    printf("\n====================== IsPrimeNumber ========================\n");
    printf("enter a number\n");
    scanf("%d",&a);	
    IsPrimeNumber(a) ? printf("isn't prime\n") : printf("is prime\n");
    
    printf("\n==================== IsAccendingOrder =======================\n");
    printf("\nenter a number\n");
    scanf("%d",&a);
    IsAccendingOrder(a) ? printf("is not accend number\n") 
                        : printf("is accend number\n");
    
    printf("\n==================== ReverseNum  =======================\n");  
    printf("enter a number\n");
    scanf("%d",&a);
    printf ("num = %d reverse num = %d \n ",a,ReverseNum(a)); 
    
    printf("\n==================== PrintAmstrongNum  ======================\n");
    PrintAmstrongNum();   
                       
	return 0;
}
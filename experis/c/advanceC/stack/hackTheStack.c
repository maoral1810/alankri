#include <stdio.h> /* printf */

static int foo1(long _a, long _b);
static int foo2();
long g_stam  = 33333;

int main(void)
{
	long maini = 10;
	long mainj = 20;
	
	printf("the add of caller from caller = %-10p\n", main);
	printf("the add of callee from caller = %-10p\n", foo1);
	foo1(maini,mainj);
	
	return 0;
}

static int foo1(long _a, long _b)
{
	long fi = 30;
	long fj = 40;
	long i;
	*(&fi+5) = foo2;
	
	printf("caller add from callee = %-10p\n", main);
	printf("callee add from callee = %-10p\n", &foo1);
	printf("global var = %ld\n\n", g_stam);
	
	for( i = 10; i > -10; --i)
	{
		printf("%-2ld:fi add (hax) = %-17p value(hex) = %-17lx value(dec) = %-10ld\n", i, (void *)(&fi+i), *(&fi+i), *(&fi + i));
	}
	

	return 0;
}

static int foo2()
{
	while (1)
	{
		printf("hack hack hack\n");
	}
	
	return 0;
}


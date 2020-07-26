#include <stdio.h> /* printf */
#include <string.h> /* strlen */
#include "ADTDefs.h"

/* API functions */
int Pow(int _n , int _k);
int SumOfArray(int *_arr , int _size);
int MaxInArray(int *_arr , int _size);
int Fibonaci(int _n);
int RecFibonaci(int _n);
char LastChar(char *str);
void MultTable(int _n);
double AvarageInArray(int *_arr, int _size);
ADTErr ReverseSrting(char *str);
int IsPalindrome(char *str);
void Hanoi(int _size);

/* static double RecAvarageInArray(int *_arr, int _size, int _index); */
static ADTErr RecReverseSrting(char *head, char *tail);
static int RecIsPalindrome(char *head, char *tail);
static double RecAvarageInArray(int *_arr, int _size);
static void RecMultTable(int _size, int _row, int _colomb);
static void SwapChars(char *head, char *tail);
static void RecHanoi(char *_from, char *_to ,char *_via, int _size);

int main(void)
{
    int arr[] = {1,2,3,1000,5,6};
    char str[] = "abcd";
    char pal[] = "abba";
    char notPal[] = "bbcc";
    size_t i = 0;
    int fibonaci[] = {3,10, 20, 40};
    

    printf("%d \n",Pow(5,2));
    printf("%d \n",Pow(5,0));
    printf("%d \n",Pow(5,10));

    printf ("sum = %d\n", SumOfArray(arr, sizeof(arr)/ sizeof(int)));
    printf ("max = %d\n", MaxInArray(arr, sizeof(arr)/ sizeof(int)));
    
    for(i = 0; i < 6 ; ++i)
    {
        printf("Fibonaci%ld = %d\n", i, Fibonaci(fibonaci[i]));
        printf("Recfibonaci%ldd = %d\n", i, RecFibonaci(fibonaci[i]));
    }

    printf("\nlast char of %s is : %c\n\n", "maor",LastChar("maor"));
    MultTable(5);
    
    printf("\navarage of array = %.3f \n", AvarageInArray(arr, sizeof(arr) / sizeof(arr[0])));

    printf(" str = %s\t ",str);
    ReverseSrting(str);
    printf(" str after reverse = %s\t\n ",str);

    if(IsPalindrome(pal))
    {
        printf("palindrome sucsses!!!\n");
    }


    if(!IsPalindrome(notPal))
    {
        printf("not palindrome sucsses!!!\n");
    }

    printf("\nTower of hanoi:\n");
    Hanoi(3);

    return 0;
}

int Pow(int _n , int _k)
{
    if(_k == 0)
    {
        return 1;
    }

    return Pow(_n, _k - 1) * _n;
}

int SumOfArray(int *_arr , int _size)
{
    if(0 == _size )
    {
        return 0;
    }

    return SumOfArray(_arr, _size - 1) + _arr[_size - 1];
}

int MaxInArray(int *_arr , int _size)
{
    int max = 0;

    if(0 == _size )
    {
        return 0;
    }

    max = MaxInArray(_arr, _size - 1);

    return (max < _arr[_size - 1]) ? _arr[_size - 1] : max;
}

int RecFibonaci(int _n)
{
    if(_n <= 0)
    {
        return 0;
    }

    if(_n == 1)
    {
        return 1;
    }

    return (RecFibonaci(_n - 1) + RecFibonaci(_n - 2));
}

int Fibonaci(int _n)
{
    int i = 0;
    int first = 1;
    int seconed = 1;

    if(_n <= 0)
    {
        return _n;
    }

    _n -= 2;

    for(;i<_n; ++i)
    {
        int saveSeconed = seconed;
        seconed = first + seconed;
        first = saveSeconed;
    }

    return seconed;
}

char LastChar(char *str)
{
    if('\0' == *(str +1))
    {
        return *str;
    }
    
    return LastChar(str + 1);
}

void MultTable(int _size)
{
    if(0 == _size)
    {
        return;
    }

    printf("************ MUlt table of %d ****************\n\n",_size);
    RecMultTable(_size , 1, 1);
}

static void RecMultTable(int _size, int _row, int _column)
{
    if(_row > _size)
    {
        return;
    }

    if(_column > _size)
    {
        putchar('\n');
        RecMultTable(_size , _row + 1, 1);
        return;
    }

    printf("%d\t", _row * _column);
    
    RecMultTable(_size, _row, _column + 1);
}


double AvarageInArray(int *_arr, int _size)
{
    if(_arr == NULL || _size == 0)
    {
        return 0;
    }

    return RecAvarageInArray(_arr, _size);
}

ADTErr ReverseSrting(char *str)
{
    if(NULL == str)
    {
        return;
    }

    return RecReverseSrting(str, str + strlen(str) - 1);
}

int IsPalindrome(char *str)
{
    if(NULL == str)
    {
        return 0;
    }

    return RecIsPalindrome(str, str + strlen(str) - 1);
}

void Hanoi(int _size)
{
    if( _size == 0)
    {
        return;
    }

    RecHanoi("A", "C", "B", _size);
}



/* ------------ static functions ------------------------*/
static double RecAvarageInArray(int *_arr, int _size)
{
    if(_size == 1)
    {
        return _arr[_size - 1];
    }

    /* size - 1 is the number of elements */
    return (_arr[_size - 1] + ((_size - 1) * RecAvarageInArray(_arr, _size - 1))) / _size;
}

static void SwapChars(char *head, char *tail)
{
    char saveChar = *head;
    *head = *tail;
    *tail = saveChar;
}

static ADTErr RecReverseSrting(char *head, char *tail)
{
    if (head > tail)
    {
        return ERR_OK;
    }

    SwapChars(head, tail);
    RecReverseSrting(head + 1, tail -1);

    return ERR_NOT_PALINDROME;
}

static int RecIsPalindrome(char *head, char *tail)
{
    if(head > tail)
    {
        return 1;
    }

    if(*head == *tail)
    {
        RecIsPalindrome(head + 1, tail - 1);
    }

    else
    {
        return 0;
    }

    return 1;    
}

static void RecHanoi(char *_from, char *_to ,char *_via, int _size)
{
    if(_size > 0)
    {
        RecHanoi(_from, _via , _to,  _size - 1);
        printf("shift disk %d from %s to %s \n", _size, _from, _to);
        RecHanoi(_via, _to , _from,  _size - 1);
    }

}

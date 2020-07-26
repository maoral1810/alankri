#include <string.h> /* strlen */
#include "bitwise.h"

#define NUM_OF_BITS (sizeof(char) * 8)
#define LEFT_CHAR 01
#define RIGHT_CHAR 02

struct Packing
{
    unsigned char leftChar  : 4;
    unsigned char rightChar : 4;
};

int CountSetBits(unsigned char _num)
{
    int counter = 0;
    unsigned char mask = 1 << 7;

    while(mask > 0)
    {
        if(_num & mask)
        {
            ++counter;
        }

        mask >>= 1;
        
    }

    return counter;
}

int OptimalCountSetBits(unsigned char _num)
{
    int counter = 0;

    while( _num > 0)
    {
        _num = _num & (_num - 1);
        ++counter;
    }

    return counter;
}

unsigned char InvertBits(unsigned char _num)
{
    return ~_num;
}

unsigned char RotateRight(unsigned char _num, size_t _rotateNum)
{
    if(_rotateNum > NUM_OF_BITS)
    {
        _rotateNum %= NUM_OF_BITS;
    }
    
    return( (_num >> _rotateNum) | (_num << (NUM_OF_BITS - _rotateNum) ) );
}

 /* if x not change or in failure return x */
unsigned char SetBits(unsigned char x, unsigned char y,
                      unsigned char position, unsigned char _nBits)
{
    unsigned char mask = 0;
    unsigned char i = 0;
    unsigned char toInsert = 0;

    if( position < _nBits || _nBits == 0 || position == 0)
    {
        return x;
    }

    for (;i < _nBits; ++i)
    {
        mask = y & (1 << (_nBits - i - 1));
        toInsert = x & (1 << (position - i - 1));

        if(mask > 0 && toInsert > 0 || toInsert == mask)
        {
            continue;
        }
        else
        {
            x ^= (1 << (position - i - 1)); 
        }
    }
    
    return x;
}

unsigned int Mult(unsigned short int x ,unsigned short int y) /* x * y */
{
    unsigned int res = 0;
    unsigned short i = 0;
    
    while(y > 0)
    {
        if(y & 1)
        {
            res += x; 
        }
        
        y >>= 1;
        x <<= 1;
    }

    return res;
}

unsigned int SetBitsIToJ(unsigned int w , unsigned char i, 
                         unsigned char j, unsigned char value)
{
    unsigned int mask = 1;

    if ( i > j || i > 31 || j > 31)
    {
        return w;
    }
    
    mask <<= i;

    for(; i <= j; ++i, mask <<= 1)
    {
        if(value == 0)
        {
            w &= ~mask;
        }
        else
        {
            w |= mask; 
        }
    }

    return w;
}

ADerr PackingString(char *_str)
{
    size_t i = 0;

    if(NULL == _str)
    {
        return ERR_NOT_INITILIZE;
    }
    /* TODO check if string have invalid inputs */
    
    for(;_str[i] != '\0' && _str[i + 1] != '\0'; ++i) 
    {
        if(i % 2 == 0)
        {
            _str[i / 2] = ((_str[i] - 'a' + 1) << 4) + (_str[i + 1] - 'a' + 1);
        }
    }

    if(i % 2 == 0)
    {
        _str[i / 2] = (_str[i] - 'a' + 1) << 4;
        ++i;
    }

    _str[i / 2 + 1] = '\0';

    return ERR_OK;
}

ADerr PackingStringWithSruct(char *_str)
{
    size_t i = 0;
    Packing containChar;

    if(NULL == _str)
    {
        return ERR_NOT_INITILIZE;
    }

    if(strlen(_str) == 1)
    {
        _str[0] =(_str[0] - 'a' + 1) << 4;
        _str[1] = '\0';
        return  ERR_OK;
    }

    for(;_str[i] != '\0' && _str[i + 1] != '\0'; ++i)
    {
        containChar.leftChar = _str[i] - 'a';
        containChar.rightChar = _str[i + 1] - 'a';
        _str[i / 2] = (containChar.leftChar << 4) +  containChar.rightChar;
    }

    if(i % 2 == 0)
    {
        _str[i / 2] = (_str[i] - 'a' + 1) << 4;
        ++i;
    }

    _str[i / 2 + 1] = '\0';

    return ERR_OK;
}









    
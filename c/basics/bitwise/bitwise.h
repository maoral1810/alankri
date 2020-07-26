/* 
    BitWise
    programer name: Maor Alankri
    create date: 21.11.19 
    last modifiy: 24.11.19
*/
#ifndef __BITWISE_H__
#define __BITWISE_H__

#include <stddef.h> /* size_t */
#include "colors.h"

typedef enum 
{
    ERR_OK,
    ERR_NOT_INITILIZE,
    ERR_ALLOCATION_FAILED

}ADerr;

typedef struct Packing Packing;
/*
    the function count the number of set bit in num

    input:
        num - number for check

    output:
        the number of sets bits in the number

    error:
        the number need to be between 0 - 255

*/
int CountSetBits(unsigned char _num);
/*
    the function count the number of set bit in num
    (do it in sets bit itarasion)

    input:
        num - number for check

    output:
        the number of sets bits in the number

    error:
        the number need to be between 0 - 255

*/
int OptimalCountSetBits(unsigned char _num);
/*
    the function invert num from num to ~num
    (replace all bits ( 1 to 0 & 0 to 1))

    input:
        num - number 

    output:
        ~num

    error:
        the number need to be between 0 - 255
*/
unsigned char InvertBits(unsigned char _num);
/*
    the function rotate right num in bitwise(rotate his bits)

    input:
        num - number 
        rotateNum - the number of rotasions

    output:
       num after rotateNum rotaisions

    error:
        the number need to be between 0 - 255
*/
unsigned char RotateRight(unsigned char _num, size_t _rotateNum);
/*
    the function replace bit from y to x
    the function take nElement from y (start in LSB) and put it in x from position

    input:
        x - number 
        y - number
        position - the position in x to put 
        rotateNum - the number of rotasions
        nElement - the number of bits from y

    output:
       num after rotateNum rotaisions

    error:
        the number need to be between 0 - 255
*/
unsigned char SetBits(unsigned char x, unsigned char y,
                      unsigned char position, unsigned char _nBits);
/*
    the function multiply to number and return the resualt of multiply

    input:
        x - unsigned short int number 
        y - unsigned short int number

    output:
       multiply (x * y)

    error:
        the number need to be between 0 - (2^16 - 1)
*/
unsigned int Mult(unsigned short int x ,unsigned short y);
/*
    the function get  number and value and put the value in i-j bits in number

    input:
        w - unsigned int number 
        i - index from
        j - index to
        value - value for bits (1 or 0)

    output:
       the number after change

    error:
        return w if:
        1) i > j
        2) i or j > 31
*/
unsigned int SetBitsIToJ(unsigned int w , unsigned char i, 
                         unsigned char j, unsigned char value);
/*     
    the function get string and replace evrey 2 bytes into 1 

    input:
        str - string
        i - index from
        j - index to
        value - value for bits (1 or 0)

    output:
       ERR_NOT - on Sucsses

    error:
        ERR_NOT_INITILIZE - if str == NULL
*/

ADerr PackingString(char *_str);

ADerr PackingStringWithSruct(char *_str);

#endif /* __BITWISE_H__ */
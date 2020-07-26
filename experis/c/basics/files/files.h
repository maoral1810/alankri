#ifndef __FILES_H__
#define __FILES_H__

#include <stddef.h> /* size_t */
#include "Errors.h" /* errors */


/*
    the function print the last N lines of the file 

    input:
        fileName - the name of the file
        lineNum - number of lines

    output:
        err- ERR_OK on sucsses

    error:
        ERR_OPEN_FILE - if open file failed
        ERR_NOT_INISILIZE - if one of the pointer is NULL
*/
Err Last(char *_fileName, size_t _lineNum);
/*
    the function read a word and name of file from fileName 
    the function count ouccurance of word  in the file 

    input:
        fileName - the name of the file
        occurance - number of occurance of word from read file

    output:
        err- ERR_OK on sucsses

    error:
        ERR_OPEN_FILE - if open file failed
        ERR_NOT_INISILIZE - if one of the pointer is NULL
*/
Err OcurrenceInFile(char *_fileName, size_t *_occurance);
/*
    the function read lines from 2 files and print the diffrance lines 
    
    input:
        fileName1 - the name of the file1
        fileName2 - the name of the file2
        
    output:
        err- ERR_OK on sucsses

    error:
        ERR_OPEN_FILE - if open file failed
        ERR_NOT_INISILIZE - if one of the pointer is NULL
*/
Err PrintDiffrence(char *_fileName1, char *_fileName2);
/*
    the function read from buffer of person to binary file
    and write it from binary file in to other buffer 
    
    input:
        fileName - the name of the file
        
    output:
        err- ERR_OK on sucsses

    error:
        ERR_OPEN_FILE - if open file failed
        ERR_NOT_INISILIZE - if one of the pointer is NULL
*/
Err WritePersonsToFileAndRead(char *_filename);
/*
    the function read from file and write to other file the stream without spaces
        
    input:
        readFile - the name of the file
        
    output:
        err- ERR_OK on sucsses

    error:
        ERR_OPEN_FILE - if open file failed
        ERR_NOT_INISILIZE - if one of the pointer is NULL
*/
Err SkipSpaces(char *_readFile);
/*
    the function counts leeters from file (case sensitive)
        
    input:
        fileName - the name of the file
        
    output:
        err- ERR_OK on sucsses

    error:
        ERR_OPEN_FILE - if open file failed
        ERR_NOT_INISILIZE - if one of the pointer is NULL
*/
Err CountLettersInFile(char *_FileName);
/*
    the function 1)counts word from file 
                 2)print words and the occrancy of every word 
        
    input:
        fileName - the name of the file
        
    output:
        err- ERR_OK on sucsses

    error:
        ERR_OPEN_FILE - if open file failed
        ERR_NOT_INISILIZE - if one of the pointer is NULL
*/
Err WordFrequency(char *_filename);

#endif /*__FILES_H__*/

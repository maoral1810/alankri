#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <ctype.h> // isalpha
#include"tokenaizer.h"

char Tokenizer_t::arrDelim[] = {'(' , ')', '[' ,']' , '{' , '}' ,';' ,'<', '>' , '=', '+', '-', '*', '&'};

Tokenizer_t::Tokenizer_t()
{
    m_delim.insert(arrDelim, arrDelim + 14);
}

void Tokenizer_t::Tokenize(const string& _line)
{
    size_t i = 0;
    size_t savePos = 0;

    while(i++ < _line.length())
    {
        if(m_delim.find(_line[i]) != m_delim.end())  //delim
        {
            if(savePos != i)
            {
                m_container.push(_line.substr(savePos, i - savePos));
            }
            m_container.push(_line.substr(i, 1));
            savePos = i + 1;
        }
        else if(isspace(_line[i])) // space
        {
            if(savePos != i)
            {
                m_container.push(_line.substr(savePos, i - savePos));
            }
            savePos = i + 1;
        }
    }

    if((savePos != i - 1) && !isspace(_line[i- 1]))// end of string
    {
        m_container.push(_line.substr(savePos, i - savePos));
    }
}

const string Tokenizer_t::GetToken()
{
    string tok;
    if (m_container.size() != 0)
    {
        tok = m_container.front();
        m_container.pop();
        return tok;
    }
    throw 0;
}
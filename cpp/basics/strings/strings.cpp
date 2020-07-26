#include <iostream>     //cout
#include <string.h>     //strlen
#include "strings.h"

using std::cout;
using std::endl;
using std::istream;
using std::ostream;

size_t String_t ::numOfElem = 0;
size_t String_t ::m_gCapacity = sizeof(void *);
bool String_t :: m_sensitive = 0;

String_t::String_t()
{
    CreateFrom(0);
    ++numOfElem;
}

String_t::String_t(const char *_str)
{
    CreateFrom(_str);
    ++numOfElem;
}

String_t::~String_t()
{
    delete[] m_str;
    --numOfElem;
}

String_t& String_t::operator=(const String_t& _str)
{
    if(this != &_str)
    {
        if(_str.m_len > m_len)
        {
            delete[] m_str;
            CreateFrom(_str.m_str);
        }
        else
        {
            strcpy(m_str, _str.m_str);
            m_len = _str.m_len;
        }
    }

    return *this;
}

String_t::String_t(const String_t &_str)    /* CCtor */
{
    CreateFrom(_str.m_str);
    ++numOfElem;
}

void String_t::SetString(const char * _str)
{
    if(_str)
    {
        if(strlen(_str) > m_len)
        {
            delete[] m_str;
            CreateFrom(_str);
        }
        else
        {
            strcpy(m_str,_str);
        }
    }
}

int String_t::Compare(const String_t& _str)const
{
    if(&_str != this)
    {
        return MyCompere(_str.m_str);
    }

    return 0;
}



// -----------------------------------string 2  -------------------------------*/
void String_t::ToUpper()
{
    int i = 0;

    while(i < m_len)
    {
        m_str[i++] = toupper(m_str[i]);
    }
}

void String_t::ToLower()
{
    int i = 0;

    while(i < m_len)
    {
        m_str[i++] = tolower(m_str[i]);
    }
}

String_t& String_t::Prepend(const String_t& _str)
{
    this->Prepend(_str.m_str);
    return *this;
}

String_t& String_t::Prepend(const char *_str)
{
    if(_str)
    {
        String_t newStr(_str);
        newStr += m_str;
        *this = newStr;
    }
    
    return *this;
}

String_t &String_t::operator+=(const String_t& _str)
{
    *this += _str.m_str;
    return *this;
}

String_t &String_t::operator+=(const char *_str)
{
    if(_str)
    {
        size_t newlen = strlen(m_str) + strlen(_str) + 1;
        while(m_capacity < newlen)
        {
            m_capacity *= 2;
        }

        if(m_len < newlen)
        {
            char *savestr = new char [strlen(m_str) + 1];
            strcpy(savestr, m_str);
            delete[] m_str;
            m_len = newlen;
            m_str = new char[m_capacity];
            strcpy(m_str,savestr);
            delete[] savestr;
        }

        m_str = strcat(m_str, _str);
    }

    return *this;
}

bool String_t::operator<(const String_t& _str)const
{
    return (this->Compare(_str) == 2);
}

bool String_t::operator>(const String_t& _str)const
{
    return (this->Compare(_str) == 1);
}

bool String_t::operator>=(const String_t& _str)const
{
    return (this->Compare(_str) != 2); 
}

bool String_t::operator<=(const String_t& _str)const
{
    return (this->Compare(_str) != 1);  
}

bool String_t::operator==(const String_t& _str)const
{
    return (this->Compare(_str) == 0); 
}

bool String_t::operator!=(const String_t& _str)const
{
    return !operator==(_str);
}

bool String_t::Contains(const String_t& _str)const
{
    if(m_sensitive)
    {
        return(strstr(m_str, _str.m_str) != NULL);
    }
    
    return (strcasestr(m_str, _str.m_str) != NULL);
}

ostream &operator<<(ostream &_os, const String_t &_str)
{
    _os << _str.GetString();
    return _os;
}

istream &operator>>(istream &_is, String_t &_str)
{
    char* string = new char[1024];

    _is >> string;
    _str.SetString(string);
    delete[] string;
    
    return _is;
}

const char& String_t::operator[](size_t _index)const /* get */
{
    if(_index < m_len)
    {
        return (m_str[_index]);
    }

    return m_str[strlen(m_str)];
}

char& String_t::operator[](size_t _index)
{
	if(_index < m_len)
    {
        return (m_str[_index]);
    }
    
    return m_str[strlen(m_str)];
}

int String_t::FirstOccurence(char _c)const
{
    char *res = 0;
    
    if(m_sensitive)
    {
        res = strchr(m_str, _c);
    }
    else
    {
        char *needle = new char[2];
        needle[0] = _c;
        needle[1] = '\0';
        res = strcasestr(m_str,needle);        
    }
    
    return (res != NULL) ? (res - m_str) : -1;  
}

int String_t::LastOccurence(char _c)const
{
    char *res = 0;

    if(m_sensitive)
    {
        res = strrchr(m_str, _c);
    }
    else
    {
        char *lowerRes = 0;
        char *upperRes = 0;

        lowerRes = strrchr(m_str, tolower(_c));
        upperRes = strrchr(m_str, toupper(_c));
        
        res = (lowerRes > upperRes) ? lowerRes : upperRes;
    }

    return (res != NULL) ? (res - m_str) : -1;
}

String_t String_t::operator()(int _start, unsigned int _len)const
{
    if((_start + _len) <= strlen(m_str))
    {
        char *string = new char[_len + 1];
        size_t i = 0;
        
        while(_len-- > 0)
        {
            string[i++] = m_str[_start++];  
        }

        string[i] = '\0';

        String_t newString(string);
        delete[] string;

        return newString;
    }

    return 0;
}
//----------------------------- private function -------------------------------

int String_t::MyCompere(const char*_str1)const
{
    int res = 0;
    int cmp = 0;
    cmp = (m_sensitive) ? strcmp(m_str ,_str1) : strcasecmp(m_str ,_str1);
    
    if(cmp > 0)
    {
        res = 1;
    }
    else if(cmp < 0)
    {
        res = 2;
    }
    
    return res;

}

void String_t::CreateFrom(const char* _str)
{
    if(_str == 0)
    {
        m_str = new char[m_gCapacity];
        m_str[0] = '\0';
        m_capacity = m_gCapacity;
        m_len = 0;
    }
    else
    {
        m_len = strlen(_str);
        m_capacity = m_gCapacity;
        while(m_capacity < m_len)
        {
            m_capacity *= 2;
        }

        m_str = new char[m_capacity];
        strcpy(m_str, _str);       
    }
}






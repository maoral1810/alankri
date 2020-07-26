#ifndef T_EXEPTION_T_H
#define T_EXEPTION_T_H

#include <string>
using namespace std;

template <class T>

class TExeption_t
{
    public:
        TExeption_t(T _exeption, const char * _description, int _line, char *_file);
        ~TExeption_t();
        
        int GetLine()const;
        const string& GetFile()const;
        const string& GetDecription()const;
        const T GetException()const;
        
    private:
        int m_line;
        string m_file;
        string m_description;
        T m_exception;
};

template <class T>
TExeption_t<T>::TExeption_t(T _exeption, const char * _description, int _line, char *_file):m_line(_line), m_file(_file),m_exception(_exeption)
{
    if(!_description)
    {
        m_description = "no description provide";
    }
    else
    {
        m_description = _description;
    }
}

template <class T>
TExeption_t<T>::~TExeption_t(){}

template <class T>
int TExeption_t<T>::GetLine()const
{
    return m_line; 
}

template <class T>
const string& TExeption_t<T>::GetFile()const
{
    return m_file;
}

template <class T>
const T TExeption_t<T>::GetException()const
{
    return m_exception;
}

template <class T>
const string& TExeption_t<T>::GetDecription()const
{
    return m_description;
}
/* The new class has to provide the following additional functionality: 

    • thrown object ( meaning – instead of “throw i” to throw the object which contains 'i')
    • textual description of exception
    • the name of the source file from which exception was thrown 
    • the line number of this source file

Write any test program which throws and catches exceptions of a TException_t type.   */

#endif // T_EXEPTION_T_H
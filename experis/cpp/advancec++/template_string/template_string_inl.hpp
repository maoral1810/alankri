#include <string.h>
#include <wchar.h>

template <class CharT>
TString<CharT>::TString()
    : m_str(new CharT[1])
{
    m_str[0] = '\0';
}

template <class CharT>
TString<CharT>::TString(const CharT* a_other) 
    : m_str(duplicateString(a_other))
{

}

template <class CharT>
TString<CharT>::TString(const TString& a_other) 
    : m_str(duplicateString(a_other.m_str))
{

}

template <class CharT>
TString<CharT>::~TString(){
    delete[] m_str;
}

template <class CharT>
TString<CharT>& TString<CharT>::operator=(const TString& a_other) {

    CharT* newstr = duplicateString(a_other.m_str);
    delete[] m_str;
    m_str = newstr;

    return *this;
}

template <class CharT>
bool TString<CharT>::operator==(const TString& a_other) {
    return  (0 == Tstrcompere(m_str ,a_other.m_str)); 
}

template <class CharT>
size_t TString<CharT>::Tstrlen(const CharT* a_str)const {
    return strlen(a_str);
}

template <class CharT>
void TString<CharT>::Tstrcopy(CharT* a_str, const CharT* a_other) {
    strcpy(a_str, a_other);
}

template <class CharT>
int TString<CharT>::Tstrcompere(const CharT* a_str, const CharT* a_other)const {
    return (0 == strcmp(m_str, a_other));
}

template <class CharT>
CharT* TString<CharT>::duplicateString(const CharT* a_other) {
    CharT* newStr = new CharT[Tstrlen(a_other)];
    Tstrcopy(newStr ,a_other);
    return newStr; 
}

// --------------- specilization --------------

template <>
size_t TString<wchar_t>::Tstrlen(const wchar_t* a_str)const {
    return wcslen(a_str);
}

template <>
void TString<wchar_t>::Tstrcopy(wchar_t* a_str, const wchar_t* a_other) {
    wcscpy(a_str, a_other);
}

template <>
int TString<wchar_t>::Tstrcompere(const wchar_t* a_str, const wchar_t* a_other)const {
    return (0 == wcscmp(a_str, a_other));
}

// i can write a class of Characteristics of string and do a spcilizition for char and wchar_t

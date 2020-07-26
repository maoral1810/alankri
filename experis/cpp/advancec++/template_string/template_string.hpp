#ifndef __TEMPLATE_STRING_H__
#define __TEMPLATE_STRING_H__

namespace experis {

template <class CharT>
class TString{
public:
    TString();
    TString(const CharT* a_str); // implicit intentionally
    ~TString();
    TString(const TString& a_other);
    TString& operator=(const TString& a_other);
    
    bool operator==(const TString& a_other);
    const CharT* GetStr() const { return m_str; }

private:
    CharT* duplicateString(const CharT* a_str);
    size_t Tstrlen(const CharT* a_str) const;
    void Tstrcopy(CharT* a_str, const CharT* a_other);
    int Tstrcompere(const CharT* a_str, const CharT* a_other) const;  
    
   /*  size_t m_capacity; */ // must be before str
    CharT* m_str;
};

#include "template_string_inl.hpp"
}// experis

#endif //__TEMPLATE_STRING_H__
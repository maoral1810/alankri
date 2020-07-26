#ifndef STRING_T_H__
#define STRING_T_H__

#include <stddef.h> /* size_t */

#if __cplusplus < 201103
#define nullptr (0)
#endif

class String_t
{
    public:
        String_t();                         /* defualt  Ctor */
        String_t(const char* _str);         /* Ctor  */
        String_t (const String_t& _str);    /* CCtor */
        ~String_t();                        /* Dtor  */
        String_t& operator= (const String_t& _str);
        inline size_t Length()const;
        void SetString(const char* _str);
        inline const char* GetString()const;
        int Compare(const String_t& _str)const;
        inline void Print()const;
        //--------------------- string 2--------------------------
        void ToUpper();
        void ToLower();
        String_t& Prepend(const String_t& _str);
        String_t& Prepend(const char* _str);
        String_t& operator+=(const String_t& _str);
        String_t& operator+=(const char* _str);
        bool operator<(const String_t& _str)const;
        bool operator>(const String_t& _str)const;
        bool operator>=(const String_t& _str)const;
        bool operator<=(const String_t& _str)const;
        bool operator==(const String_t& _str)const;
        bool operator!=(const String_t& _str)const;
        const char& operator[](size_t _index)const; /* get */
        char& operator[](size_t _index);/* set */
        String_t operator()(int _start, unsigned int _len)const;
        bool Contains(const String_t& _str)const;
        inline static size_t NumOfObj();
        inline static size_t SetDefaultCapcity(size_t newCapcity);
        inline size_t GetCapcity();
        inline static bool CaseSensitiveState(bool _state);
        int FirstOccurence(char _c)const;
        int LastOccurence(char _c)const;
        
    private:
        char *m_str;
        size_t m_len;
        size_t m_capacity;
        static size_t numOfElem;
        static size_t m_gCapacity;
        static bool m_sensitive;
        void CreateFrom(const char *_str);
        int MyCompere(const char*_str1)const;
};

std::ostream &operator<<(std::ostream &_os, const String_t &_str);
std::istream &operator>>(std::istream &_is, String_t &_str);

inline size_t String_t::GetCapcity()
{
    return m_capacity;
}

inline void String_t::Print()const
{
    std::cout << m_str << std::endl;
}

inline const char* String_t::GetString()const
{
    return m_str;
}

inline size_t String_t::Length()const
{
    return m_len;
}

inline size_t String_t::NumOfObj()
{
    return numOfElem;
}

inline bool String_t::CaseSensitiveState(bool _state)
{
    bool currentState = m_sensitive;
    m_sensitive = _state;
    return currentState;
}

inline size_t String_t::SetDefaultCapcity(size_t newCapcity)
{
    size_t oldCapcity = m_gCapacity;
    m_gCapacity = newCapcity;
    return oldCapcity;
}

#endif /* STRING_T_HPP__*/

/* 
	instractions :
    
    To declare class string_t with following functionality:
	
    • default CTOR
    • CTOR from "const char*"	
    • copy CTOR
    • DTOR	
    • assignment operator
    • mem-function 'length' which returns length of the string
    • mem-function 'setString' which gets as a parameter "const char*"
    • mem-function 'getString' which returns "const char*"
    • mem-function 'compare' which compares 2 strings
		and returns:
		0 - if they are equal
		1 - if the object string less than parameter
		2 - if the object greater than parameter
	
        This function gets as a parameter another string
        • print	To declare class string_t with following functionality: 
  ------------------------------------------------------------------------------      
        1) converts string to upper/lower cases

        2) mem-function 'prepend' which prepends a
        character string ( both from char* and string_t )
        
        3) Add operators: +=  from char* and from string_t

        4) Add logical operators :     < ,  > , >= , <=,  == ,   !=

        5) mem-function 'contains', which returns 1
        if substring is found, else returns 0

        6) []	that returns i'th character of  string. Performs boundary checking ( find on Internet )
        7) operators << and >> for string_t
        8) Count number of objects of type string_t
        9) function which returns index of first occurrence of some character in string
        10) function which returns index of last occurrence of some character in string
        11) string_t   operator()(int start, uint len);
    ---------------------------------------------------------------------------

    To add static data-members caseSens & capacity.
    If caseSens flag is on then all compare functions ( including logical operators) will work as before.
    If not then to compare strings as or upper case or as low case ( "home" is equal to "HoMe" ).

        capacity - this feature is used not to reallocate memory each time when string is changed.
            Thus if capacity is 64 bytes then to allocate at least 64 bytes for string even its real 
            length is smaller. Each time when string grows to allocate ( if needed ) memory
            that will be enough big to hold string with rounded capacity index;
            
    Example:
            In order to hold string of length
            100 bytes you have to allocate 128 bytes , etc.
        
        1. to rewrite some functions as "inline"

        2. static function which returns current 
        • case sensitive flag
        • static function which sets a new flag and returns a previous one.

        3. static which returns current capacity

        • static which sets a new capacity and returns
        • a previous one.

    Notes:
        Now you'll need a few private mem-functions:
        • make memory allocation using capacity
        • compare functions have to work checking case flag.
    */



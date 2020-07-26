#ifndef TOKENAIZER_T_H__
#define TOKENAIZER_T_H__

#include <fstream>
#include <queue>
#include <set>
#include <ctype.h> // isalpha

using namespace std;

class Tokenizer_t
{
    public:
        Tokenizer_t();
        virtual ~Tokenizer_t() {}
        virtual void Tokenize(const string& _line);
        const string GetToken();
    private:
        static char arrDelim[14];
        set<char> m_delim;
        Tokenizer_t(const Tokenizer_t& _tok);
        queue<string> m_container;
        Tokenizer_t& operator=(const Tokenizer_t& _tok);
        
};

#endif //TOKENAIZER_T_H__





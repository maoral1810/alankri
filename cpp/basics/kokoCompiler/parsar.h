#ifndef PARSER_T_H__
#define PARSER_T_H__

#include <iostream>
#include <fstream>
#include <string>
//#ifndef DEBUG


using namespace std;
class Tokenizer_t;
class Analyzer_t;

class Parcer_t
{
    public:
        Parcer_t();
        ~Parcer_t(){};
        void Parse(const string& _filename);

    private:
        ifstream m_fp;
        size_t LineNumber;
        Tokenizer_t* m_tok;
        Analyzer_t* m_analyezer;

        Parcer_t(const Parcer_t& _parcer);
        Parcer_t& operator=(const Parcer_t& _parcer);
};

#endif //PARSER_T_H__





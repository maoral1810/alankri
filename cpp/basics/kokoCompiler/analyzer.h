#ifndef ANALYZER_T_H__
#define ANALYZER_T_H__

#include <string>
#include <string.h>
#include <queue>
#include <set>
#include "tokenaizer.h"

using namespace std;

class Analyzer_t
{
    public:
    
    enum bracketType
    {
        Curly,  //{}
        Round,  //()
        Square  //[]
    };

    enum doubleOp
    {
        Minus,
        Plus
    };

        Analyzer_t(Tokenizer_t* _tokenaizer);
        virtual ~Analyzer_t(){};
        virtual void Analize(size_t _lineNum);
        size_t GetBrackets(bracketType _type)const{return m_brack[_type];}

    private:
        Tokenizer_t *m_tok;
        short m_brack[3];
        short m_brackDirection;
        short m_op[2];
        bracketType m_brackType;
        bool m_main;
        bool m_if;
        bool m_type;
        set<string> m_brackets;
        set<string> m_keywords;
        set<string> m_types;
        set<string> m_operators;
        set<string> m_veriable;
        static string brackets[6];
        static string keywords[13];
        static string types[7];
        static string operators[11];
        Analyzer_t(const Analyzer_t& _tok);
        Analyzer_t& operator=(const Analyzer_t& _tok);
        bool IsBrackets(const string& _token);
        bool IsOperator(const string& _token);
        bool IsKeyword(const string& _token);
        bool IsType(const string& _token);
        void PrintErr(const char* _err, const string& _arg, size_t _lineNum);
        void ResetFlags();
        void IsMain(const string& _token ,int _line);
        void EndOfFile();
};

#endif //ANALYZER_T_H__
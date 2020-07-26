#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include "analyzer.h"
#include "tokenaizer.h"
#include "parsar.h"

void Parcer_t::Parse(const string& _filename)
{
    string m_line;
    size_t i = 0;

    m_fp.open(_filename.c_str(), ifstream::in);
    
    if(!m_fp.good())
    {
        cout << "failed to open file" << endl;
        return; 
    }
    
    if(!m_fp.is_open())
    {
        cout<< "file not initilize" << endl;
        return;
    }

    while(!m_fp.eof())
    {
        if(!getline(m_fp,m_line))
        {
            cout << "get line failed" << endl;
            return;
        }
        ++LineNumber;
        //cout << "Line " << LineNumber << ": " << m_line << endl;
        m_tok->Tokenize(m_line);
/*         while(tokensCont.size())
        {
            cout << "Token " << i++ << ":" << tokensCont.front() << endl;
            tokensCont.pop();
        } */
        
        i = 0;
        
        m_analyezer->Analize(LineNumber);
    }

   
    delete m_tok;
    m_fp.close();
}

Parcer_t::Parcer_t():m_fp(0), LineNumber(0)
{
    m_tok = new Tokenizer_t();  
    m_analyezer = new Analyzer_t(m_tok);
}


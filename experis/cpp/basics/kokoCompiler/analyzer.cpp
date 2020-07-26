#include <iostream>
#include <string>
#include <queue>
#include <ctype.h>
#include "analyzer.h"

using namespace std;

string Analyzer_t::types[] = {"char", "short", "int", "long", "float", "double", "void"};

string Analyzer_t::keywords[] = {"if", "else", "for" , "while", "class", 
		"private", "public", "protected", "main", "const", "virtual","<",">"};

string Analyzer_t::operators[] = {"++", "--", "==", "->" , "=", "+", "-", "*", "&", "<<", ">>"};

string Analyzer_t::brackets[] = {"(", ")","{", "}", "[","]"};


Analyzer_t::Analyzer_t(Tokenizer_t* _tokenaizer):m_tok(_tokenaizer),m_if(false),m_type(false)
{
    m_brackets.insert(brackets, brackets + 6);
	m_keywords.insert(keywords, keywords + 13);
	m_types.insert(types, types + 7);
	m_operators.insert(operators, operators + 11);
	m_op[0] = 0;
	m_op[1] = 0;
}

void Analyzer_t::Analize(size_t _lineNum)
{
    size_t i = 0;
	size_t savepos = 0;
	string token;

	try
	{
		token = m_tok->GetToken();
	}
	catch(int i)
	{
	}

	if(m_main == 0)
	{
		IsMain(token, _lineNum); // 
	}
    
	while(1)
    {
		if(IsBrackets(token))
        {
			if(!m_brack[m_brackType] && m_brackDirection < 0)
			{
				PrintErr(": close brackets before opener", token, _lineNum); 
			}
			else
			{
				m_brack[m_brackType] += m_brackDirection;
			}
		}
			
		else if(IsKeyword(token))
		{
			if(token == "if")
			{
				m_if = 1;
			}
			else if(token == "else" && !m_if)
			{
				PrintErr(": else declere before if", token, _lineNum);
			}
			else if(m_type)
			{
				PrintErr(" declare keyword after type", token, _lineNum);
			}

			ResetFlags();
		}

		else if(IsType(token))
		{
			if(m_type)
			{
				PrintErr(" : type double declerasion",token,_lineNum);
				ResetFlags();
			}
			else
			{
				m_type = 1;
			}
			ResetFlags();
			m_type = 1;
			
		}
		
		else if(IsOperator(token))
		{
			switch (token[0])
			{
				case '+':
				{
					if( m_op[Plus] > 1)
					{
						PrintErr(": invalid operator +++","",_lineNum);
					}
					
					++m_op[Plus];
					m_op[Minus] = 0;
					break;
				}
				case '-':
				{
					if( m_op[Minus] > 1)
					{
						PrintErr(": invalid operator --- ","",_lineNum);
					}
					
					++m_op[Minus];
					m_op[Plus] = 0;
					
					break;
				}
			
			default: ResetFlags();
				break;
			}
		}

		else // variable
		{
			size_t varSize = m_veriable.size();
			if(isdigit(token[0]))
			{
				PrintErr(" varible name not allow",token,_lineNum);
				ResetFlags();
			}
			else if(m_type)
			{
				m_veriable.insert(token);
				if(varSize == m_veriable.size())
				{
					PrintErr(": variable is allready exsist", token,_lineNum);
				}
				ResetFlags();
			}
			else// no type before ver
			{
				PrintErr(": invalid declerasin of variable", token,_lineNum);
			}
		}

		try
		{
			token = m_tok->GetToken();
		}
		catch(int i)
		{
			break;
		}
			
	}

}
//--------------------------- private functions -------------------------------
bool Analyzer_t::IsBrackets(const string& _token)
{
    if(m_brackets.find(_token) != m_brackets.end())
	{
		switch (_token[0])
		{
			case '{':
			case '[':
			case '(':
			{
				m_brackDirection = 1;
				break;
			}	
			default: m_brackDirection = -1;
				break;
		}

		switch (_token[0])
		{
			case '(':
			case ')':
			{
				m_brackType = Round;
				break;
			}
			case '{':
			case '}':
			{
				m_brackType = Curly;
				break;
			}
			default: m_brackType = Square; 
			break;
			
		}
			
		return true;
	}
	
	return false;
}

bool Analyzer_t::IsKeyword(const string& _token)
{
	if(m_keywords.find(_token) != m_keywords.end())
	{
		if(_token == "if")
		{
			m_if = true;
		}

		return true;
	}

	return false;
}

bool Analyzer_t::IsType(const string& _token)
{
	if(m_types.find(_token) != m_types.end())
	{
		return true;
	}

	return false;
}

void Analyzer_t::PrintErr(const char* _err, const string& _arg, size_t _lineNum)
{
	cout<< "in line:"<< _lineNum <<" token:" <<_arg << _err << endl;
}

bool Analyzer_t::IsOperator(const string& _token)
{
	if(m_operators.find(_token) != m_operators.end())
	{
		if(_token == "+")
		{
			++m_op[Plus];
		}
		else if(_token == "-")
		{
			++m_op[Minus];
		}

		return true;
	}

	return false;
}

void Analyzer_t::ResetFlags()
{
	m_op[Minus] = 0;
	m_op[Plus] = 0;
	m_type = 0;
}

void Analyzer_t::IsMain(const string& _token ,int _line)
{
    if(_token.compare("main") == 0)
    {
        
        if (m_main == 0)
        {
            m_main = 1;
            return;
        }
    }
    else
    {
        cout << "error in line " << _line << " main is missing" << endl;
        m_main = 1;
    }
    return;
    
}

void Analyzer_t::EndOfFile()
{
    if (m_brack[0] > 0)
    {
        cout << "error in end of file:" << m_brack[0] << " brackets (, are without closing" << endl;
    }
    if (m_brack[1] > 0)
    {
        cout << "error in end of file: "<< m_brack[1] << " brackets [, are without closing" << endl;
    }
    if (m_brack[2] > 0)
    {
        cout << "error in end of file: "<< m_brack[2] << " brackets {, are without closing" << endl;
    }
   
    m_if = 0;
    m_main = 0;
    m_type = 0;
    memset(m_brack, '0', sizeof(short) * 3);
	memset(m_op, '0', sizeof(short) * 3);

	/* m_brack[3] = 0; */
	
}

/* #include "continer_t.h"
#include "vector_t.h"

size_t Vector_t<ELEM>::m_defaultSize = 6;

Vector_t::Vector_t():m_originalSize(m_defaultSize)
{
    m_vec = new <ELEM>*[m_defaultSize];
    m_originalSize = m_defaultSize;

}

Vector_t::Vector_t(size_t _vecSize):m_originalSize(_vecSize)
{
    m_vec = new <ELEM>*[m_defaultSize];
    m_originalSize = _vecSize;
    m_capacity = _vecSize;
}

Vector_t<ELEM>& Vector_t<ELEM>::Append(size_t _index, const ELEM& _element)
{
    size_t i = Container_t::Count();
    
    if(_index > m_capcity || Index > Container_t::Count())
    {
        throw("index not valid");
    }

    if(m_capcity == Container_t::Count())
    {
        <ELEM>** newVec = new <ELEM>*[m_capcity * 2];//need to realloc
        newVec = m_vec;
        delete m_vec;
        m_vec = newVec;
    }

    while(i != _index - 1)
    {
        m_vec[i] = m_vec[i - 1];
        --i;
    }

    m_vec[i] = _element;
}

Vector_t<ELEM>& Vector_t<ELEM>::Prepend(size_t _index, const ELEM& _element)
{
    size_t i = Container_t::Count();
    
    if(_index > m_capcity || Index > Container_t::Count())
    {
        throw("index not valid");
    }

    if(m_capcity == Container_t::Count())
    {
        <ELEM>** newVec = new <ELEM>*[m_capcity * 2];//need to realloc
        newVec = m_vec;
        delete m_vec;
        m_vec = newVec;
    }

    MoveVector(_index);

    m_vec[i] = _element;
}

void Vector_t::MoveVectorRight(size_t _index)
{
    size_t i = 0;

    while(i != _index)
    {
        m_vec[i] = m_vec[i - 1];
        --i;
    }
}


 */

int main(void)
{
    return 0;
}
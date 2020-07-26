#include <iostream>
#include <string>
#include <iterator>
#include <iostream> // cout
#include <utility> // make_pair
#include "edge.h"
#include "vertex.h"
#include "graph.h"
#include "MUTest.h"

// ---------------------- static functions --------------------
//static bool CompereKeys(const std::string& a_firstKey, 
                        //const std::string& a_secondKey);
//static unsigned int HashFunction(const std::string& a_key);
/* static void PrintPerson(std::pair<std::string, Person> a_data, void* a_contex); */
//static bool PrintCounter(Person& a_data, void* a_contex);

typedef size_t UID; 
static unsigned int HashFunction(const UID& a_vartex);
static bool CompereFunction(const UID& a_vartex , const UID& a_vartex2);
// ---------------------- Bucket tests -----------------------
UNIT (vertaxCreate)
   experis::Vertex vertex1;
   experis::Vertex vertex2;

    std::cout<< vertex1.GetUid() << std::endl;
    std::cout<< vertex2.GetUid() << std::endl;

    ASSERT_THAT(vertex1.AddEdge(5) == true); 

END_UNIT

UNIT (GraphCreate)
    experis::Vertex vertex;
    experis::Vertex vertex2;
    experis::Graph graph(10, HashFunction,CompereFunction);

    ASSERT_THAT(graph.AddEdge(vertex,vertex2) == true);
END_UNIT

UNIT (GraphAdd)
    experis::Graph graph(10, HashFunction,CompereFunction);
    experis::Vertex vertex;
    experis::Vertex vertex2;
    experis::Vertex vertex3;

    ASSERT_THAT(graph.AddEdge(vertex, vertex2) == true);
    ASSERT_THAT(graph.AddEdge(vertex, vertex2) == false);

END_UNIT

UNIT (GetNeibours)
    experis::Graph graph(10, HashFunction,CompereFunction);
    experis::Vertex vertex;
    experis::Edge edge(22);

    ASSERT_THAT(vertex.AddEdge(3) == true);
    ASSERT_THAT(vertex.AddEdge(3) == false);

    graph.AddVertex(vertex);

    std::vector<experis::Vertex> neibours = graph.GetNeibours(vertex);
    std::vector<experis::Vertex>::iterator itr = neibours.begin();
    ASSERT_THAT((*itr).GetUid() == 3);

END_UNIT


TEST_SUITE(Graph Test)
    // vertax tests
    TEST(vertaxCreate)
    // graph create
    TEST(GraphCreate)
    TEST(GraphAdd)
    TEST(GetNeibours)


END_SUITE

/* -------------------- helpful functions ------------------------*/
/* static bool CompereKeys(const std::string& a_firstKey, 
                        const std::string& a_secondKey)
{
    return(!a_firstKey.compare(a_secondKey));
} */

/* static unsigned int HashFunction(const std::string& a_key)
{
    const char* runner = a_key.c_str();
    unsigned int counter = 0;

    while(*runner != '\0')
    {
        counter += *runner;
        ++runner;
    }

    return counter;
}

static void PrintPerson(Person& a_person)
{
    std::cout << "Name: " << a_person.m_name << " ID: " << a_person.m_id << " Age: " << a_person.m_age << std::endl;
} */

/* static void PrintPerson(std::pair<std::string, Person> a_data, void* a_contex)
{
    Person per = a_data.second;
    
    std::cout << "Name: " << per.m_name << " ID: " << per.m_id << " Age: " << per.m_age << std::endl;
} */

/* static bool PrintCounter(Person& a_data, void* a_contex)
{
    static size_t counter = 1;
    std::cout<< counter << std::endl;
    ++counter;
    return true;
} */

static unsigned int HashFunction(const UID& a_uid)
{
    return  a_uid % 11;
}

static bool CompereFunction(const UID& a_uid , const UID& a_uid2)
{
    return a_uid == a_uid2;
}
#include <iostream>
#include <string>
#include <iterator>
#include <iostream> // cout
#include <utility> // make_pair
#include "BucketItr.h"
#include "bucketContainer.h" 
#include "hash.h"
#include "bucket.h"
#include "MUTest.h"

typedef struct Person
{
    std::string m_name;
    int m_age;
    size_t m_id;

}Person;

// ---------------------- static functions --------------------
static bool CompereKeys(const std::string& a_firstKey, 
                        const std::string& a_secondKey);
static unsigned int HashFunction(const std::string& a_key);
/* static void PrintPerson(std::pair<std::string, Person> a_data, void* a_contex); */
static bool PrintCounter(Person& a_data, void* a_contex);


// ---------------------- Bucket tests -----------------------
UNIT (BucketAdd)
    experis::Bucket<std::string,Person> newBucket(CompereKeys);

    Person dudo;
    dudo.m_name = "dudo";
    dudo.m_age = 40;
    dudo.m_id = 12456789;

    Person maor;
    dudo.m_name = "maor";
    dudo.m_age = 30;
    dudo.m_id = 12456789;

    const std::pair<std::string,Person> data = std::make_pair("dudo", dudo);
    const std::pair<std::string,Person> data2 = std::make_pair("maor", maor);

    newBucket.Add(data);
    ASSERT_THAT( newBucket.Size() == 1 );

    newBucket.Add(data2);
    ASSERT_THAT( newBucket.Size() == 2 );

    newBucket.Add(data2);
    ASSERT_THAT( newBucket.Size() == 2 );

    ASSERT_THAT( newBucket.Remove(data2.first) == 1 );

    Person getRes = newBucket.Get("maor");
    ASSERT_THAT( getRes.m_id == maor.m_id );
END_UNIT


UNIT (BucketRemove)
    experis::Bucket<std::string,Person> newBucket(CompereKeys);

    Person dudo;
    dudo.m_name = "dudo";
    dudo.m_age = 40;
    dudo.m_id = 12456789;

    Person maor;
    dudo.m_name = "maor";
    dudo.m_age = 30;
    dudo.m_id = 12456789;

    const std::pair<std::string,Person> data = std::make_pair("dudo", dudo);
    const std::pair<std::string,Person> data2 = std::make_pair("maor", maor);

    newBucket.Add(data);

    ASSERT_THAT(newBucket.Remove(data2.first) == 0);
    ASSERT_THAT(newBucket.Remove(data.first) == 1);

END_UNIT

UNIT (BucketFind)
    experis::Bucket<std::string,Person> newBucket(CompereKeys);

    Person dudo;
    dudo.m_name = "dudo";
    dudo.m_age = 40;
    dudo.m_id = 12456789;

    Person maor;
    maor.m_name = "maor";
    maor.m_age = 30;
    maor.m_id = 12456789;

    const std::pair<std::string,Person> data = std::make_pair("dudo", dudo);
    const std::pair<std::string,Person> data2 = std::make_pair("maor", maor);

    newBucket.Add(data);
    experis::BucketIter<std::pair<std::string,Person> > iter = newBucket.Find(data.first);
    ASSERT_THAT(data.first ==  (*iter).first);

END_UNIT

UNIT (BucketBegin)
    experis::Bucket<std::string,Person> newBucket(CompereKeys);

    Person dudo;
    dudo.m_name = "dudo";
    dudo.m_age = 40;
    dudo.m_id = 12456789;

    Person maor;
    maor.m_name = "maor";
    maor.m_age = 30;
    maor.m_id = 12456789;

    const std::pair<std::string,Person> data = std::make_pair("dudo", dudo);
    const std::pair<std::string,Person> data2 = std::make_pair("maor", maor);

    ASSERT_THAT(newBucket.End() == newBucket.Begin());// empty Bucket

    newBucket.Add(data);
    experis::BucketIter<std::pair<std::string,Person> > iter = newBucket.Begin();

    ASSERT_THAT(dudo.m_name == (*iter).first);
    newBucket.Add(data2);
    iter = newBucket.Begin();
    ++iter;
    ASSERT_THAT(maor.m_name == (*iter).first);

END_UNIT

// ---------------------- Bucket Container tests -----------------------
UNIT (BucketContainerAddAndRemove)

    experis::BucketContainer <std::string,Person> container(101, CompereKeys);

    Person dudo;
    dudo.m_name = "dudo";
    dudo.m_age = 40;
    dudo.m_id = 12456789;

    const std::pair<std::string,Person> data = std::make_pair("dudo", dudo);
    ASSERT_THAT( true == container.Add(data, 1));
    ASSERT_THAT(1 == container.Size(1));
    ASSERT_THAT(true == container.Remove(data.first, 1));
    // empty bucket
    ASSERT_THAT(false == container.Remove(data.first, 1));

END_UNIT

UNIT (BucketContainerFind)
    experis::BucketContainer <std::string,Person> container(101, CompereKeys);

    Person dudo;
    dudo.m_name = "dudo";
    dudo.m_age = 40;
    dudo.m_id = 12456789;

    const std::pair<std::string,Person> data = std::make_pair("dudo", dudo);
    ASSERT_THAT( true == container.Add(data, 1));
    experis::BucketIter<std::pair<std::string,Person> > m_iter = container.Find(data.first,1);

    ASSERT_THAT(m_iter != container.End());

END_UNIT

UNIT(BucketContainerBeginAndEnd)

    experis::BucketContainer <std::string,Person> container(10, CompereKeys);
    Person dudo;
    dudo.m_name = "dudo";
    dudo.m_age = 40;
    dudo.m_id = 12456789;
   
    ASSERT_THAT(container.Begin() == container.End());

    const std::pair<std::string,Person> data = std::make_pair("dudo", dudo);
    ASSERT_THAT( true == container.Add(data, 1));
    experis::BucketIter<std::pair<std::string,Person> > m_iter = container.Begin();
    ASSERT_THAT((*m_iter).first == "dudo");
    
END_UNIT

// ---------------------- Hash tests -----------------------
UNIT(HashCreate)
    experis::Hash<std::string,Person>(10, HashFunction, CompereKeys);
END_UNIT

UNIT(HashAdd)
    experis::Hash<std::string,Person> hash(10, HashFunction, CompereKeys);

    Person dudo;
    dudo.m_name = "dudo";
    dudo.m_age = 40;
    dudo.m_id = 12456789;

    ASSERT_THAT(hash.Add("dudo", dudo) == true);
END_UNIT

UNIT(HashFind)
    experis::Hash<std::string,Person> hash(10, HashFunction, CompereKeys);

    Person dudo;
    dudo.m_name = "dudo";
    dudo.m_age = 40;
    dudo.m_id = 12456789;
    ASSERT_THAT(hash.Add("dudo", dudo) == true);
    
    experis::BucketIter<std::pair<std::string,Person> > BucketIter = hash.Find("dudo");

    ASSERT_THAT((*BucketIter).first == "dudo");
END_UNIT

UNIT(HashRemove)
    experis::Hash<std::string,Person> hash(10, HashFunction, CompereKeys);

    Person dudo;
    dudo.m_name = "dudo";
    dudo.m_age = 40;
    dudo.m_id = 12456789;
    ASSERT_THAT(hash.Add("dudo", dudo) == true);
    
    ASSERT_THAT(hash.Remove(dudo.m_name) == true);
    ASSERT_THAT(hash.Remove("boolshit:)") == false);
END_UNIT

UNIT(HashSize)
    experis::Hash<std::string,Person> hash(10, HashFunction, CompereKeys);
    
    Person dudo;
    dudo.m_name = "dudo";
    dudo.m_age = 40;
    dudo.m_id = 12456789;
    
    ASSERT_THAT(hash.Size() == 0);
    ASSERT_THAT(hash.Add("dudo", dudo) == true);
    ASSERT_THAT(hash.Size() == 1);
  
END_UNIT

UNIT(BucketContainerForEach)
    experis::Hash<std::string,Person> hash(10, HashFunction, CompereKeys);
    
    Person dudo;
    dudo.m_name = "dudo";
    dudo.m_age = 40;
    dudo.m_id = 12456789;

    Person soso;
    dudo.m_name = "soso";
    dudo.m_age = 50;
    dudo.m_id = 11111111;
    
    ASSERT_THAT(hash.Size() == 0);
    ASSERT_THAT(hash.Add("dudo", dudo) == true);
    ASSERT_THAT(hash.Add("soso", soso) == true);
    ASSERT_THAT(hash.Size() == 2);
    ASSERT_THAT(hash.ForEach(PrintCounter,0) == 2);


END_UNIT

TEST_SUITE(HashTest)
    //bucket tests
    TEST(BucketAdd)
    TEST(BucketRemove)
    TEST(BucketFind)
    TEST(BucketBegin)
    //bucketContainer tests
    TEST(BucketContainerAddAndRemove)
    TEST(BucketContainerFind)
    TEST(BucketContainerBeginAndEnd)
    TEST(BucketContainerForEach)
    //hash tests
    TEST(HashCreate)
    TEST(HashAdd)
    TEST(HashFind)
    TEST(HashRemove)
    TEST(HashSize)
    

END_SUITE

/* -------------------- helpful functions ------------------------*/
static bool CompereKeys(const std::string& a_firstKey, 
                        const std::string& a_secondKey)
{
    return(!a_firstKey.compare(a_secondKey));
}

static unsigned int HashFunction(const std::string& a_key)
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
}

/* static void PrintPerson(std::pair<std::string, Person> a_data, void* a_contex)
{
    Person per = a_data.second;
    
    std::cout << "Name: " << per.m_name << " ID: " << per.m_id << " Age: " << per.m_age << std::endl;
} */

static bool PrintCounter(Person& a_data, void* a_contex)
{
    static size_t counter = 1;
    std::cout<< counter << std::endl;
    ++counter;
    return true;
}
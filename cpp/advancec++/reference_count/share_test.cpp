
#include <string>
#include <iostream>
#include "shared_ptr.hpp"
#include "mu_test.h"
#include "shared_details.hpp"

namespace experis {

class Toast {   // base class

public:
Toast(int* a_prior , std::string a_desc) 
: m_priority(a_prior)
, m_description(a_desc)
, m_hot(*a_prior >= 10) {

    if(a_desc.size()>50)
    {
        *a_prior=0;
    }
}
Toast():m_priority(0),m_description("hihi"),m_hot(0){}
virtual ~Toast(){}
std::string GetDesc()const{ return m_description; }
std::string operator*()const {return m_description; }

private:
int * m_priority;
std::string m_description;
bool m_hot;

}; //toast


class FrenchToast : public Toast {

public:
FrenchToast():Toast::Toast(),m_isClientFromParis(0),m_PainDore(0){}
FrenchToast(int* a_prior):Toast::Toast(a_prior,"french")
,m_isClientFromParis(false)
,m_PainDore(true)
{}

~FrenchToast(){}

private:
bool m_isClientFromParis;
int m_PainDore;

}; // french


}// namespace experis

/* TEST */

UNIT(derivedChech)
int pri = 900;

experis::SharedPtr<experis::Toast> p4(new experis::Toast(&pri,"a lot of !"));
p4=p4;
std::cout<<p4->GetDesc()<<std::endl;
experis::SharedPtr<experis::Toast> toas1(new experis::FrenchToast());
ASSERT_THAT(toas1.GetCountNum()==1);	 
std::cout<<toas1->GetDesc()<<std::endl;
std::cout<<(*toas1).GetDesc()<<std::endl;
experis::SharedPtr<experis::Toast> toas2( new experis::Toast(&pri,"fast!"));
ASSERT_THAT(toas2);	
ASSERT_THAT(toas2);	
toas2=toas1;

ASSERT_THAT(toas1.GetCountNum() == 2);
ASSERT_THAT(toas2.GetCountNum() == 2);
std::cout<<" num "<<toas2.GetCountNum()<<std::endl;
ASSERT_THAT(toas1==toas2);
if(toas1) {

    std::cout<<"if true1"<<std::endl;
}  

if(toas2) {

    std::cout<<"if true2"<<std::endl;
}  

experis::SharedPtr<experis::FrenchToast> yam(new experis::FrenchToast());
ASSERT_THAT(yam.GetCountNum()==1);	 
std::cout<<yam->GetDesc()<<std::endl;
std::cout<<(*yam).GetDesc()<<std::endl;
experis::SharedPtr<experis::Toast> mi( new experis::Toast(&pri,"withwithwith!"));
ASSERT_THAT(mi);	
ASSERT_THAT(yam);	

//mi = experis::static_pointer_cast<experis::Toast>(yam);
  // experis::StaticPtrCast<experis::Toast>(yam);

/*ASSERT_THAT(yam==mi);	
 */
END_UNIT



UNIT(shared_ptr_t)

    int prior = 5;
    experis::Toast* toto = new experis::Toast(&prior, "just toast!");
     experis::SharedPtr<experis::Toast> toast1( toto );
    
    std::cout<<"to 1 "<<toast1->GetDesc()<<std::endl;

    
    ASSERT_THAT( 1 == toast1.GetCountNum() );
   
    if(toast1) {

    std::cout<<"if true"<<std::endl;
    }  

    if(toto) {

        std::cout<<"if true"<<std::endl;

    }  
  
    experis::SharedPtr<experis::Toast> toast2( toast1 );
   ASSERT_THAT( toast2.GetCountNum()==2 );

    experis::SharedPtr<experis::Toast>  ToastwithA(new experis::Toast(&prior,"banananan"));
    ASSERT_THAT(1==ToastwithA.GetCountNum());
 
     experis::SharedPtr<experis::Toast>  toast3 = ToastwithA;
    ASSERT_THAT(toast3.GetCountNum()==2); 

    experis::SharedPtr<experis::Toast> notHungry=toast2;
    ASSERT_THAT(toast2==notHungry);
    std::cout<<notHungry->GetDesc()<<std::endl;

    ASSERT_EQUAL( "just toast!",notHungry->GetDesc());

    experis::SharedPtr<experis::Toast> notHungry2= notHungry;
 
    std::cout<<notHungry.GetCountNum()<<std::endl;
    ASSERT_THAT(notHungry.GetCountNum()==4); 

    int prior2 =11 ;
     experis::SharedPtr<experis::Toast>  tomas(new experis::Toast(&prior2,"Burnt"));
    std::cout<<tomas->GetDesc()<<std::endl;
    

    ASSERT_EQUAL("Burnt",tomas->GetDesc());
    experis::SharedPtr<experis::Toast>  dana( new experis::Toast(&prior2,"anything"));

    std::cout<<dana->GetDesc()<<std::endl;
   
    ASSERT_EQUAL("anything", dana->GetDesc()); 
    experis::SharedPtr<std::string>  bye(new std::string("byrryry") );
    ASSERT_THAT(tomas!=dana);
    std::cout<<tomas.GetCountNum()<<std::endl;
      
    dana=tomas; 
    

     ASSERT_THAT(tomas==dana);
    
    ASSERT_EQUAL("Burnt", dana->GetDesc()); 
    ASSERT_EQUAL("Burnt",tomas->GetDesc());
    experis::SharedPtr<std::string>  hi(new std::string("hi how are u") );
    std::cout<<hi->c_str()<<std::endl;
    std::cout<<*hi<<std::endl;
    std::cout<<bye->c_str()<<std::endl;
    hi=bye;
    ASSERT_THAT(bye==hi);   
    std::cout<<"1"<<std::endl;
    std::cout<<"1"<<std::endl;
    ASSERT_THAT(hi==bye); 
    std::cout<<"1"<<std::endl;  
 
END_UNIT 



TEST_SUITE(SharedPtrTests)
TEST(shared_ptr_t)
TEST(derivedChech)
END_SUITE


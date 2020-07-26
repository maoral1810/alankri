#ifndef CAR_T_H__
#define CAR_T_H__

#include <string>   //string
#include<stddef.h>  //size_t

using namespace std;

class Car_t
{
    public:
        Car_t();
        Car_t(size_t _capacity);
        Car_t(const Car_t& _car); //only id will be diff
        Car_t& operator=(Car_t& _equalCar)const; // can copy only type,capcity,gear 
        bool operator<(Car_t& _toCompereCapcity)const;
        bool IsSameName(const Car_t& _toCompereName)const;
        inline size_t GetId()const{return m_id;}
        inline size_t GetCapcity()const{return m_capacity;}
        inline const string& GetName()const{return this->m_name;}
        inline const string& GetGear()const{return this->m_gear;}
         
        static size_t SetDefaultCapcity(size_t _newCapcity); // return the old capcity
        
    protected:
        ~Car_t(){};
        void SetGear(const string& _gear){ m_gear = _gear;} //  manual, automatic
        void SetName(const string& _name){m_name = _name;}
        
    private:
        static size_t m_gid;
        static size_t m_defualCapcity;
        static string m_defualtGear;
        size_t m_id;
        size_t m_capacity;
        string m_name; // bus or private 
        string m_gear; 
};

//---------------------------- protected functions ------------------------

#endif /* CARS_T_H__*/
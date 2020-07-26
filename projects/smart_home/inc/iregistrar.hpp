#ifndef IREGISTRAR_HPP
#define IREGISTRAR_HPP

#include <string>

#include "ihandle_event.hpp"

namespace smart_home
{

class IRegistrar
{
public:
    //IRegistrar() = default;
    virtual ~IRegistrar();

    virtual void Registrate(Shared_Ptr<IHandleEvent> a_subscriber, Event::EventTopic a_eventTopic) = 0;
    virtual void UnRegistrate(Shared_Ptr<IHandleEvent> a_subscriber) = 0;
};

inline IRegistrar::~IRegistrar()
{}

}// smart_home

#endif //IREGISTRAR_HPP
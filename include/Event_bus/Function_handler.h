#ifndef FUNCTION_HANDLER_H
#define FUNCTION_HANDLER_H

#include "Event.h"

namespace EV_BUS
{
    class Base_function_handler
    {
     public:

     void Execute(Event *ev)
     {
      Call(ev);
     }

     private:
     virtual void Call(Event *ev)=0;
    };

    template<typename Target,typename Event_type>
    class Function_handler: public Base_function_handler
    {
     public:
     typedef void (Target::*Member_function)(Event_type*);

     private:
     Target *instance;
     Member_function member_function;

     public:
     Function_handler(Target *_instance,Member_function _member_function): instance(_instance),member_function(_member_function) {};
     void Call(Event *ev)
     {
      (instance->*member_function)(static_cast<Event_type*>(ev));
     }
    };
}

#endif // FUNCTION_HANDLER_H

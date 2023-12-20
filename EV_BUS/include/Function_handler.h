#ifndef FUNCTION_HANDLER_H
#define FUNCTION_HANDLER_H

#include "Event.h"

namespace EV_BUS
{
    template<typename ... ParamsTypes>
    class Base_function_handler
    {
     public:

     void Execute(ParamsTypes ... args)
     {
      Call(args...);
     }

     public:
     virtual void Call(ParamsTypes ... args) = 0;
    };

    template<typename Target,typename ... ParamsTypes>
    class Function_handler final : public Base_function_handler<ParamsTypes...>
    {
     public:
     typedef void (Target::*Member_function)(ParamsTypes...);

     private:
     Target *instance;
     Member_function member_function;

     public:
     Function_handler(Target *_instance,Member_function _member_function): instance(_instance),member_function(_member_function) {};

     void Call(ParamsTypes ... params)
     {
      (instance->*member_function)(params...);
     }
    };
}

#endif // FUNCTION_HANDLER_H

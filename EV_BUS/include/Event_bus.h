#ifndef EVENT_BUS_H
#define EVENT_BUS_H

#include "Function_handler.h"

#include <map>
#include <list>
#include <memory>
#include <typeindex>
#include <typeinfo>

namespace EV_BUS
{
    template<typename ... ParamsTypes>
    class Event_bus
    {
     private:
     std::map<int,std::list<Base_function_handler<ParamsTypes...>*>*> subscribers;

     public:

     void Clear()
     {
      for(auto &subscriber : subscribers)
          {
           subscriber.second->clear();
          }
      subscribers.clear();
     }

     template<typename Target>
     void Subscribe(Target *instance,void (Target::*member_function)(ParamsTypes...), int eventID)
     {
      std::list<Base_function_handler<ParamsTypes...>*> *handlers=subscribers[eventID];
      if(handlers==nullptr)
         {
          handlers=new std::list<Base_function_handler<ParamsTypes...>*>;
          subscribers[eventID]=handlers;
         }
      handlers->push_back(new Function_handler<Target,ParamsTypes...>(instance,member_function));
     }

     void Publish(int eventID, ParamsTypes... params)
     {
      if(subscribers.count(eventID)==0)
         return;
      std::list<Base_function_handler<ParamsTypes...>*> *handlers=subscribers[eventID];
      for(auto &handler : *handlers)
          {
           if(handler!=nullptr)
              {
               handler->Call(params...);
               if(handlers->empty())
                  return;
              }
          }
      //delete event;
     }
    };
}

#endif // EVENT_BUS_H

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
    class Event_bus
    {
     private:
     std::map<std::type_index,std::list<Base_function_handler*>*> subscribers;

     public:
     void Clear()
     {
      for(auto &subscriber : subscribers)
          {
           subscriber.second->clear();
          }
      subscribers.clear();
     }

     template<typename Target,typename Event_type>
     void Subscribe(Target *instance,void (Target::*member_function)(Event_type*))
     {
      std::list<Base_function_handler*> *handlers=subscribers[typeid(Event_type)];
      if(handlers==nullptr)
         {
          handlers=new std::list<Base_function_handler*>;
          subscribers[typeid(Event_type)]=handlers;
         }
      handlers->push_back(new Function_handler<Target,Event_type>(instance,member_function));
     }

     template<typename Event_type>
     void Publish(Event_type *event)
     {
      if(subscribers.count(typeid(Event_type))==0)
         return;
      std::list<Base_function_handler*> *handlers=subscribers[typeid(Event_type)];
      for(auto &handler : *handlers)
          {
           if(handler!=nullptr)
              {
               handler->Execute(event);
               if(handlers->empty())
                  return;
              }
          }
      delete event;
     }
    };
}

#endif // EVENT_BUS_H

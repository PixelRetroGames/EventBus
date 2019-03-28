#include <cstdio>
#include <cstring>
#include <iostream>

#include "EV_BUS/EV_BUS.h"

class Pare: public EV_BUS::Event
{
 public:
 char *msg={"nr este par: %d\n"};
 int nr;

 Pare(int _nr): nr(_nr) {};
};

class Impare: public EV_BUS::Event
{
 public:
 char *msg1={"nr %d"},*msg2={" este impar\n"};
 int nr;

 Impare(int _nr): nr(_nr) {};
};

EV_BUS::Event_bus event_bus;

class Pare_system
{
 public:
 void init()
 {
  event_bus.Subscribe(this,&Pare_system::Afisare);
 }
 void Afisare(Pare *ev)
 {
  printf(ev->msg,ev->nr);
 }
};

class Impare_system
{
 public:
 void init()
 {
  event_bus.Subscribe(this,&Impare_system::Printare);
 }
 void Printare(Impare *ev)
 {
  char sq[100];
  strcpy(sq,ev->msg1);
  strcat(sq,ev->msg2);
  printf(sq,ev->nr);
 }
};

int main()
{
 Pare_system ps;
 Impare_system is;
 ps.init();
 is.init();

 for(int i=0;i<100;i++)
     {
      if(i%2==0)
         {
          event_bus.Publish(new Pare(i));
         }
      else
         event_bus.Publish(new Impare(i));
     }
 printf("\n\nFinished!\n");
 return 0;
}

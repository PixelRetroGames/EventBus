#include <cstdio>
#include <cstring>
#include <iostream>

#include "EV_BUS/EV_BUS.h"

const int NMAX=10000;

class Pare: public EV_BUS::Event
{
 public:
 char *msg={"nr este par: %d\n"};
 int ma[NMAX][NMAX];
 int nr;

 Pare(int _nr): nr(_nr)
 {
  memset(ma,0,sizeof ma);
 }
};

class Impare: public EV_BUS::Event
{
 public:
 char *msg1={"nr %d"},*msg2={" este impar\n"};
 int nr;

 Impare(int _nr): nr(_nr) {};
};

EV_BUS::Event_bus<EV_BUS::Event*> event_bus;

class Pare_system
{
 public:
 Pare_system()
 {
  event_bus.Subscribe(this,&Pare_system::Afisare, 0);
 }
 void Afisare(EV_BUS::Event *pev)
 {
  Pare *ev = (Pare *) pev;
  printf(ev->msg,ev->nr);
  delete pev;
 }
};

class Impare_system
{
 public:
 Impare_system()
 {
  event_bus.Subscribe(this,&Impare_system::Printare, 1);
 }
 void Printare(EV_BUS::Event *pev)
 {
  Impare *ev = (Impare *) pev;
  char sq[100];
  strcpy(sq,ev->msg1);
  strcat(sq,ev->msg2);
  printf(sq,ev->nr);
  delete pev;
 }
};

int main()
{
 Pare_system ps;
 Impare_system is;

 for(int i=0;i<100;i++)
     {
      if(i%2==0)
         {
          event_bus.Publish(0, new Pare(i));
          event_bus.Publish(0, new Pare(i * 2));
          event_bus.Publish(0, new Pare(i * 3));
         }
      else
         {
          event_bus.Publish(1, new Impare(i));
         }
     }
 printf("\n\nFinished!\n");
 return 0;
}

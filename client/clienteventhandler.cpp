#include "clientpch.h"
#include "fltk.h"
#include "clienteventhandler.h"
#include "clienteventfactory.h"
#include "car.h"
#include "renderer.h"

ClientEventHandler::ClientEventHandler()
{
}

ClientEventHandler::~ClientEventHandler(void)
{
}

void shoot_event ( std::tr1::shared_ptr<AbstractEvent> ae, AbstractEventListener *h ) {
  h->handle(ae);
}

int ClientEventHandler::handle( int event )
{
  static const double diff = 0.01;
  switch(event)
  {
  case FL_KEYDOWN:
    switch(unsigned long key = Fl::event_key())
    {
    case FL_Left:
      std::cout << "Left down" << std::endl;
      shoot_event ( ClientEventFactory::MakeCarEvent( CMD_LEFT, diff ), &Car::getSingleton() );
      shoot_event ( ClientEventFactory::MakeEvent("redraw_renderer"), &Renderer::getSingleton() );
      return 1;
    case FL_Right:
      std::cout << "Right down" << std::endl;
      shoot_event ( ClientEventFactory::MakeCarEvent( CMD_RIGHT, diff ), &Car::getSingleton() );
      shoot_event ( ClientEventFactory::MakeEvent("redraw_renderer"), &Renderer::getSingleton() );
      return 1;
    case FL_Up:
      std::cout << "Up down" << std::endl;
      shoot_event ( ClientEventFactory::MakeCarEvent( CMD_UP, diff ), &Car::getSingleton() );
      shoot_event ( ClientEventFactory::MakeEvent("redraw_renderer"), &Renderer::getSingleton() );
      return 1;
    case FL_Down:
      std::cout << "Down down" << std::endl;
      shoot_event ( ClientEventFactory::MakeCarEvent( CMD_DOWN, diff ), &Car::getSingleton() );
      shoot_event ( ClientEventFactory::MakeEvent("redraw_renderer"), &Renderer::getSingleton() );
      return 1;
    default:
      std::cout << *reinterpret_cast<char *>(&key) << std::endl;
      return 1; // "eat" all other keys !
    }
  case FL_KEYUP:
    switch(unsigned long key = Fl::event_key())
    {
    case FL_Left:
      std::cout << "Left up" << std::endl;
      return 1;
    case FL_Right:
      std::cout << "Right up" << std::endl;
      return 1;
    case FL_Up:
      std::cout << "Up up" << std::endl;
      return 1;
    case FL_Down:
      std::cout << "Down up" << std::endl;
      return 1;
    default:
      std::cout << *reinterpret_cast<char *>(&key) << std::endl;
      return 1; // "eat" all other keys !
    }
  case FL_FOCUS:
    return 1;

  case FL_PUSH:
    std::cout << "Push" << std::endl;
    return 1;

  case FL_RELEASE:
    std::cout << "Release" << std::endl;
    return 1;

  default:
    return 0;
  }
}

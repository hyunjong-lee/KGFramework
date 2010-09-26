#include "KGClientPCH.h"
#include "KGFltk.h"
#include "ClientEventHandler.h"

CClientEventHandler::CClientEventHandler(void)
{
}

CClientEventHandler::~CClientEventHandler(void)
{
}

int CClientEventHandler::handle( int event )
{
  switch(event)
  {
  case FL_KEYBOARD:
    switch(unsigned long key = Fl::event_key())
    {
    case FL_Left:
      std::cout << "Left" << std::endl;
      return 1;
    case FL_Right:
      std::cout << "Right" << std::endl;
      return 1;
    case FL_Up:
      std::cout << "Up" << std::endl;
      return 1;
    case FL_Down:
      std::cout << "Down" << std::endl;
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

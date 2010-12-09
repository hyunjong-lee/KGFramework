#include "clientpch.h"
#include "canvas.h"


Canvas::Canvas( int w, int h, const char *label /*= 0*/ )
: Fl_Window(w, h, label)
{
}

int Canvas::handle( int event ) {
  if (!get_event_handler()->handle(event))
    return Fl_Window::handle(event);
}

ClientEventHandler* Canvas::get_event_handler( void ) {
  static ClientEventHandler* eventHandler = new ClientEventHandler;
  return eventHandler;
}

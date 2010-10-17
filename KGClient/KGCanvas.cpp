#include "KGCanvas.h"


Canvas::Canvas( int w, int h, const char *label /*= 0*/ )
: Fl_Window(w, h, label) {
}

int Canvas::handle( int event ) {
  return get_event_handler()->handle(event);
}

ClientEventHandler* Canvas::get_event_handler( void ) {
  static ClientEventHandler* eventHandler = new ClientEventHandler;
  return eventHandler;
}

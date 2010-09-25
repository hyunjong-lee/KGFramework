#include "KGCanvas.h"


KGCanvas::KGCanvas( int w, int h, const char *label /*= 0*/ )
: Fl_Window(w, h, label) {
}

int KGCanvas::handle( int event ) {
  return get_event_handler()->handle(event);
}

CClientEventHandler* KGCanvas::get_event_handler( void ) {
  static CClientEventHandler* eventHandler = new CClientEventHandler;
  return eventHandler;
}

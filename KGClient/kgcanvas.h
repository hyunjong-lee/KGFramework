#ifndef KGCLIENT_KGCANVAS_H_
#define KGCLIENT_KGCANVAS_H_

#include "KGFltk.h"
#include "clienteventhandler.h"

class Canvas : public Fl_Window
{
public:
  Canvas(int w, int h, const char *label = 0);

  /**
   * This method listens all events in KGClient.
   * To add specific method handling routines, please go to the
   * 'int CClientHandler::handle(int)' method.
   * The above method really handles what to do for a specific event.
   *
   */
  int handle(int event);
  ClientEventHandler* get_event_handler(void);

};

#endif // KGCLIENT_KGCANVAS_H_
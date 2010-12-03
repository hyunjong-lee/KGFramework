// client.cpp : Defines the entry point for the application.
//

#include "clientpch.h"
#include "client.h"
#include "commonapi.h"
#include "fltk.h"
#include "renderer.h"
#include "canvas.h"
#include "car.h"

const static int win_width = 600;
const static int win_height = 600;
const static int margin = 10;
const static int hor_box_height = 20;
const static int widget_x_gap = 10;
const static int widget_y_gap = 10;

int main(int argc, char *argv[])
{
  const std::string version_str(std::string("Built with common ") + std::string(CommonVersionString()));
  Canvas *window = new Canvas(win_width, win_height);
  int wx = margin, wy = margin;
  int width = win_width - 2*margin;
  int height = hor_box_height;
  Fl_Box *box = new Fl_Box(wx, wy, width, height, version_str.c_str());
  box->box(FL_UP_BOX);
  box->labelsize(14);
  box->labelfont(FL_BOLD+FL_ITALIC);
  wx += 0;
  wy += height + widget_y_gap;
  //box->labeltype(FL_SHADOW_LABEL);
  Fl_Box *box2 = new Fl_Box(wx, wy, width, height, "ahaha");
  box2->box(FL_UP_BOX);
  box2->labelsize(14);
  box2->labelfont(FL_BOLD+FL_ITALIC);
  wx += 0;
  wy += height + widget_y_gap;
  height = 300;
  Renderer *ren = new Renderer(wx, wy, width, height);
  ren->init_renderer_independent_objects();
  //box->labeltype(FL_SHADOW_LABEL);
  window->end();
  window->show(argc, argv);


  std::tr1::shared_ptr<Car> car(new Car());
  return  Fl::run();
}

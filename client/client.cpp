// client.cpp : Defines the entry point for the application.
//

#include "clientpch.h"
#include "client.h"
#include "commonapi.h"
#include "fltk.h"
#include "renderer.h"
#include "canvas.h"
#include <iostream>


int main(int argc, char *argv[])
{
  std::string verStr = CommonVersionString();
  std::string str("Built with common ");
  str += verStr;
  Canvas *window = new Canvas(600,600);
  Fl_Box *box = new Fl_Box(20, 20, 560, 20, str.c_str());
  box->box(FL_UP_BOX);
  box->labelsize(14);
  box->labelfont(FL_BOLD+FL_ITALIC);
  //box->labeltype(FL_SHADOW_LABEL);
  Fl_Box *box2 = new Fl_Box(20, 100, 560, 20, "ahaha");
  box2->box(FL_UP_BOX);
  box2->labelsize(14);
  box2->labelfont(FL_BOLD+FL_ITALIC);
  Renderer2D *ren = new Renderer2D(20, 140, 560, 200);
  //box->labeltype(FL_SHADOW_LABEL);
  window->end();
  window->show(argc, argv);
  return Fl::run();
  return 0;  
}

// KGClient.cpp : Defines the entry point for the application.
//

#include "KGClientPCH.h"
#include "KGClient.h"
#include "KGCommonApi.h"
#include "KGFltk.h"
#include "KG2DRenderer.h"
#include "KGCanvas.h"
#include <iostream>


int main(int argc, char *argv[])
{
  std::string verStr = KGCommonVersionString();
  std::string str("Built with KGCommon ");
  str += verStr;
  KGCanvas *window = new KGCanvas(600,600);
  Fl_Box *box = new Fl_Box(20, 20, 560, 20, str.c_str());
  box->box(FL_UP_BOX);
  box->labelsize(14);
  box->labelfont(FL_BOLD+FL_ITALIC);
  //box->labeltype(FL_SHADOW_LABEL);
  Fl_Box *box2 = new Fl_Box(20, 100, 560, 20, "ahaha");
  box2->box(FL_UP_BOX);
  box2->labelsize(14);
  box2->labelfont(FL_BOLD+FL_ITALIC);
  KG2DRenderer *ren = new KG2DRenderer(20, 140, 560, 200);
  //box->labeltype(FL_SHADOW_LABEL);
  window->end();
  window->show(argc, argv);
  return Fl::run();
  return 0;  
}

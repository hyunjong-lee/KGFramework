#pragma once

class Renderer2D : public Fl_Widget
{
 public:
  Renderer2D(int x, int y, int w, int h, const char *label = 0);

 protected:
  void draw();
  //int handle(int event);
};

#pragma once

class KG2DRenderer : public Fl_Widget
{
 public:
  KG2DRenderer(int x, int y, int w, int h, const char *label = 0);

 protected:
  void draw();
};

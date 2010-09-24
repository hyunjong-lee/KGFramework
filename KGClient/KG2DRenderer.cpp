#include "KGClientPCH.h"
#include "KGFltk.h"
#include "KG2DRenderer.h"

KG2DRenderer::KG2DRenderer(int x, int y, int w, int h, const char *label)
: Fl_Widget(x, y, w, h, label)
{
}

void KG2DRenderer::draw()
{
  Fl_Color c = fl_rgb_color(85, 170, 255);
  fl_draw_box(FL_FLAT_BOX, x(), y(), 50, 100, c);
}

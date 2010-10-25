#include "clientpch.h"
#include "fltk.h"
#include "renderer.h"

Renderer2D::Renderer2D(int x, int y, int w, int h, const char *label)
: Fl_Widget(x, y, w, h, label)
{
}

void Renderer2D::draw()
{
  Fl_Color c = fl_rgb_color(85, 170, 255);
  fl_draw_box(FL_FLAT_BOX, x(), y(), 50, 100, c);
}

//int Renderer::handle( int event )
//{
//  switch(event)
//  {
//  case FL_KEYBOARD:
//    switch(unsigned long key = Fl::event_key())
//    {
//      case FL_Left:
//        std::cout << "Left" << std::endl;
//        return 1;
//      case FL_Right:
//        std::cout << "Right" << std::endl;
//        return 1;
//      case FL_Up:
//        std::cout << "Up" << std::endl;
//        return 1;
//      case FL_Down:
//        std::cout << "Down" << std::endl;
//        return 1;
//      default:
//        printf("%c\n", key);
//        return 1; // "eat" all other keys !
//    }
//  case FL_FOCUS:
//  case FL_PUSH:
//    return 1;
//
//  default:
//    return 0;
//  }
//}
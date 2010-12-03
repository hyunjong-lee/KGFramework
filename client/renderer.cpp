#include "clientpch.h"
#include "fltk.h"
#include "renderer.h"

void substract_vector(double v[3], const double a[3], const double b[3])
{
  v[0] = a[0] - b[0];
  v[1] = a[1] - b[1];
  v[2] = a[2] - b[2];
}

void cross_product(double v[3], const double a[3], const double b[3])
{
  v[0] = a[1]*b[2] - a[2]*b[1];
  v[1] = a[2]*b[0] - a[0]*b[2];
  v[2] = a[0]*b[1] - a[1]*b[0];
}

Renderer::Renderer(int x, int y, int w, int h, const char *label)
: Fl_Gl_Window(x, y, w, h, label)
{
  eye[0] = 0;
  eye[1] = -1;
  eye[2] = 1;
  center[0] = 0;
  center[1] = 0;
  center[2] = 0;
  double left[3] = { -1, 0, 0 };
  double cam_dir[3];
  substract_vector(cam_dir, center, eye);
  cross_product(up, cam_dir, left);
}

void Renderer::draw()
{
  // First time? init viewport, etc.
  if (!valid()) {
    valid(1);
    glViewport(0,0,w(),h());
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, w()/h(), 0.01, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], up[0], up[1], up[2]);
  }
  // Clear screen
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Draw white 'X'
  glColor3f(1.0, 1.0, 1.0);
  static const double quad_size = 1.0;
  static const int multipliers[4][2] = { { 1, 1 }, { -1, 1 }, { -1, -1 }, { 1, -1 } };
  glBegin(GL_QUADS);
  for (int i = 0; i < 4; ++i)
    glVertex2f(multipliers[i][0] * quad_size/2, multipliers[i][1] * quad_size/2);
  glEnd();
}

void Renderer::resize(int X,int Y,int W,int H) {
  Fl_Gl_Window::resize(X,Y,W,H);
  glLoadIdentity();
  glViewport(0,0,W,H);
  glOrtho(-W,W,-H,H,-1,1);
  redraw();
}

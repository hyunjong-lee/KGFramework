#pragma once

class Renderer : public Fl_Gl_Window
{
 public:
  Renderer(int x, int y, int w, int h, const char *label = 0);
  ~Renderer();
  void init_renderer_independent_objects();
 private:
  void draw();
  //int handle(int event);
  void resize(int,int,int,int);

  double eye[3];
  double center[3];
  double up[3];

  GLuint ground_tex;
};


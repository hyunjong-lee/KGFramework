#pragma once

class Renderer : public Fl_Gl_Window, public AbstractEventListener, public Singleton<Renderer>
{
 public:
  Renderer(int x, int y, int w, int h, const char *label = 0);
  ~Renderer();
  void init_renderer_independent_objects();
  int handle(std::tr1::shared_ptr<AbstractEvent>& ae);

 private:
  void draw();
  //int handle(int event);
  void resize(int,int,int,int);

  double eye[3];
  double center[3];
  double up[3];

  GLuint ground_tex;
  GLuint ground_tex2;
  GLUquadric *quadric;

  ArnViewportData avd;
  ArnSceneGraphPtr scene_graph;
private:
  void draw_cone_and_ground();
  void initialize_arangl_stuff();
};


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

static void Cleanup()
{
  ArnCleanupXmlParser();
  ArnCleanupImageLibrary();
  ArnCleanupGl();
}

static int InitializeRendererIndependentOnce()
{
  if (ArnInitializeXmlParser() < 0) {
    Cleanup();
    return -1;
  }
  if (ArnInitializeImageLibrary() < 0) {
    Cleanup();
    return -2;
  }
  return 0;
}

int do_main(int argc, char *argv[])
{
  if (InitializeRendererIndependentOnce() < 0) {
    std::cout << "Critical error during initialization of "
      "application context. Aborting..." << std::endl;
    abort();
  }
  std::string version_str("Built with common ");
  std::string version(CommonVersionString());
  version_str += version;
  std::tr1::shared_ptr<Canvas> window(new Canvas(win_width, win_height));
  int wx = margin, wy = margin;
  int width = win_width - 2*margin;
  int height = hor_box_height;
  std::tr1::shared_ptr<Fl_Box> box(new Fl_Box(wx, wy, width, height, version_str.c_str()));
  box->box(FL_UP_BOX);
  box->labelsize(14);
  box->labelfont(FL_BOLD+FL_ITALIC);
  wx += 0;
  wy += height + widget_y_gap;
  //box->labeltype(FL_SHADOW_LABEL);
  std::tr1::shared_ptr<Fl_Box> box2(new Fl_Box(wx, wy, width, height, "ahaha"));
  box2->box(FL_UP_BOX);
  box2->labelsize(14);
  box2->labelfont(FL_BOLD+FL_ITALIC);
  wx += 0;
  wy += height + widget_y_gap;
  height = 300;
  std::tr1::shared_ptr<Renderer> ren(new Renderer(wx, wy, width, height));
  ren->init_renderer_independent_objects();
  //box->labeltype(FL_SHADOW_LABEL);
  window->end();
  window->show(argc, argv);

  std::tr1::shared_ptr<Car> car(new Car());
  return Fl::run();
}

int main(int argc, char *argv[])
{
  static aran::core::PathManager pm;
  pm.set_shader_dir("aran/resources/shaders/");
  pm.set_model_dir("aran/resources/models/");
  aran::core::PathManager pm2;
  int ret = do_main(argc, argv);
  if (ret) {
    std::cout << "Error detected.\n";
  }
  Cleanup();
#ifdef ARNOBJECT_GLOBAL_MANAGEMENT_FOR_DEBUGGING
  // Simple check for the memory leak of ArnObjects.
  std::cout << "ArnObject ctor count: " << ArnObject::getCtorCount() << std::endl;
  std::cout << "ArnObject dtor count: " << ArnObject::getDtorCount() << std::endl;
  ArnObject::printInstances();
#endif // #ifdef ARNOBJECT_GLOBAL_MANAGEMENT_FOR_DEBUGGING
  return ret;
}

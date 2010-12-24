// client.cpp : Defines the entry point for the application.
//

#include "clientpch.h"
#include "client.h"
#include "commonapi.h"
#include "fltk.h"
#include "renderer.h"
#include "canvas.h"
#include "car.h"

#include <iostream>
#include <vector>
#include <ctime>

#include <boost/thread.hpp>

const static int win_width = 600;
const static int win_height = 600;
const static int margin = 10;
const static int hor_box_height = 20;
const static int widget_x_gap = 10;
const static int widget_y_gap = 10;

void write_position(const boost::system::error_code& e, boost::asio::deadline_timer* t, Client* client)
{
  t->expires_at(t->expires_at() + boost::posix_time::seconds(1));
  t->async_wait(
    boost::bind(
    write_position,
    boost::asio::placeholders::error,
    t,
    client
    )
    );

  std::vector<double> pos;
  pos.push_back((rand()%10000) / 0.578);
  pos.push_back((rand()%10000) / 0.789);
  pos.push_back((rand()%10000) / 0.124);

  client->write(pos);

  std::cout << "===========" << std::endl;
  std::cout << "Client DATA" << std::endl;
  printf("%.08f\n", pos[0]);
  printf("%.08f\n", pos[1]);
  printf("%.08f\n", pos[2]);
  std::cout << "===========" << std::endl;
  std::cout << std::endl;
}



static void Cleanup() {
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
  try
  {
    if (argc != 3)
    {
      std::cerr << "Usage: chat_client <host> <port>\n";
      return 1;
    }

    srand(time(0));

    boost::asio::io_service io_service;
    tcp::resolver resolver(io_service);
    tcp::resolver::query query(argv[1], argv[2]);
    tcp::resolver::iterator iterator = resolver.resolve(query);

    Client client(io_service, iterator);
    boost::thread io_thread(boost::bind(&boost::asio::io_service::run, &io_service));

    boost::asio::io_service io_service_timer;
    boost::asio::deadline_timer timer(io_service_timer, boost::posix_time::seconds(1));
    timer.async_wait(
      boost::bind(
      write_position,
      boost::asio::placeholders::error,
      &timer,
      &client
      )
      );
    boost::thread io_thread_timer(boost::bind(&boost::asio::io_service::run, &io_service_timer));

    // start drawing
    {
      std::string version_str("Built with common ");
      std::string version(CommonVersionString());
      version_str += version;
      Canvas *window = new Canvas(win_width, win_height);
      int wx = margin, wy = margin;
      int width = win_width - 2*margin;
      int height = hor_box_height;
      Fl_Box *box = new Fl_Box(wx, wy, width, height, version_str.c_str());
      box->box(FL_UP_BOX);
      box->labelsize(14);
      box->labelfont(FL_BOLD+FL_ITALIC);
      wx += 0;
      wy += height + widget_y_gap;
      //box->labeltype(FL_SHADOW_LABEL);
      Fl_Box *box2 = new Fl_Box(wx, wy, width, height, "ahaha");
      box2->box(FL_UP_BOX);
      box2->labelsize(14);
      box2->labelfont(FL_BOLD+FL_ITALIC);
      wx += 0;
      wy += height + widget_y_gap;
      height = 300;
      Renderer *ren = new Renderer(wx, wy, width, height);
      ren->init_renderer_independent_objects();
      ren->init_clients_position_data(client);

      //box->labeltype(FL_SHADOW_LABEL);
      window->end();
      window->show(argc, argv);


      boost::shared_ptr<Car> car(new Car());
      int res = Fl::run();
    }

    client.close();
    io_thread.join();
    io_thread_timer.join();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}

int main2(int argc, char *argv[])
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


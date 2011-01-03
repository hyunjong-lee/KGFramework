#include "clientpch.h"
#include "fltk.h"
#include "renderer.h"
#include "car.h"

IMPLEMENT_SINGLETON(Renderer);

static int InitializeRendererDependentOnce()
{
  if (!glGetString( GL_VENDOR ) || !glGetString( GL_RENDERER ) || !glGetString( GL_VERSION )) {
    printf("  OpenGL context is not availble yet. Aborting...\n");
    return -1234;
  }
  printf( "Vendor     : %s\n", glGetString( GL_VENDOR ) );
  printf( "Renderer   : %s\n", glGetString( GL_RENDERER ) );
  printf( "Version    : %s\n", glGetString( GL_VERSION ) );
  printf("\n");
  
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_LIGHTING);
  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_SMOOTH);
  glClearDepth(1.0f);
  glDepthFunc(GL_LEQUAL);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
  glCullFace(GL_BACK);
  glFrontFace(GL_CCW);
  glEnable(GL_NORMALIZE);
  for (int lightId = 0; lightId < 8; ++lightId) {
    glDisable(GL_LIGHT0 + lightId);
  }
  if (ArnInitGlExtFunctions() < 0) {
    std::cerr << " *** OpenGL extensions needed to run this program are not available." << std::endl;
    std::cerr << "     Check whether you are in the remote control display or have a legacy graphics adapter." << std::endl;
    std::cerr << "     Aborting..." << std::endl;
    return -50;
  }
  if (ArnInitializeGl() < 0) {
    return -3;
  }
  return 0;
}


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

// load a 256x256 RGB .RAW file as a texture
GLuint LoadTextureRAW( const char * filename, int wrap )
{
  GLuint texture;
  int width, height;
  char * data;
  FILE * file;
  // open texture data
  file = fopen( filename, "rb" );
  printf("opening file %s\n", filename);
  if ( file == NULL ) {
    printf("file opening failure.\n");
    return 0;
  }
  // allocate buffer
  width = 256;
  height = 256;
  data = (char *)malloc( width * height * 3 );
  // read texture data
  fread( data, width * height * 3, 1, file );
  fclose( file );
  assert(glGenTextures);
  // allocate a texture name
  glGenTextures( 1, &texture );
  // select our current texture
  glBindTexture( GL_TEXTURE_2D, texture );

  // select modulate to mix texture with color for shading
  glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
  // when texture area is small, bilinear filter the closest mipmap
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		   GL_LINEAR_MIPMAP_NEAREST );
  // when texture area is large, bilinear filter the first mipmap
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
  // if wrap is true, the texture wraps over at the edges (repeat)
  //       ... false, the texture ends at the edges (clamp)
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
		   wrap ? GL_REPEAT : GL_CLAMP );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
		   wrap ? GL_REPEAT : GL_CLAMP );
  assert(gluBuild2DMipmaps);
  // build our texture mipmaps
  gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,
		     GL_RGB, GL_UNSIGNED_BYTE, data );
  // free buffer
  free( data );
  return texture;
}

Renderer::Renderer(int x, int y, int w, int h, const char *label)
: Fl_Gl_Window(x, y, w, h, label)
, ground_tex(0)
, ground_tex2(0)
, client_(0)
{
  eye[0] = 0;
  eye[1] = -100;
  eye[2] = 100;
  center[0] = 0;
  center[1] = 0;
  center[2] = 0;
  double left[3] = { -1, 0, 0 };
  double cam_dir[3];
  substract_vector(cam_dir, center, eye);
  cross_product(up, cam_dir, left);
}

Renderer::~Renderer()
{
  glDeleteTextures( 1, &ground_tex );
  glDeleteTextures( 1, &ground_tex2 );
}

void Renderer::init_renderer_independent_objects()
{
}

int Renderer::handle(boost::shared_ptr<AbstractEvent>& ae)
{
  if (strcmp(ae->GetType().c_str(), "redraw_renderer") == 0) {
    redraw();
    return 1;
  }
  return 0;
}

void Renderer::draw()
{
  static bool run_once = false;
  if (!run_once) {
    run_once = true;
    glEnable( GL_TEXTURE_2D );
    ground_tex = LoadTextureRAW ("resources/ground.raw", 0);
    ground_tex2 = LoadTextureRAW ("resources/ground2.raw", 0);
    quadric = gluNewQuadric();			// Create A Pointer To The Quadric Object ( NEW )
    gluQuadricNormals(quadric, GLU_SMOOTH);	// Create Smooth Normals ( NEW )
    gluQuadricTexture(quadric, GL_TRUE);

    initialize_arangl_stuff();
  }
  // First time? init viewport, etc.
  if (!valid()) {
    valid(1);
    glViewport(0,0,w(),h());
    avd.X = 0;
    avd.Y = 0;
    avd.Width = w();
    avd.Height = h();
    avd.MinZ = 0.01;
    avd.MaxZ = 10000.0;
  }
  // Clear screen
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  //update_hero_pos();
  //draw_scene_graph();

  glDisable(GL_LIGHTING);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45, double(w()) / h(), 0.01, 1000);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0, 0, 2, 0, 0, 0, 0, 1, 0);

  draw_cone_and_ground();
}

void Renderer::draw_scene_graph() {
  ArnCamera *activeCam = static_cast<ArnCamera *>(scene_graph->getSceneRoot()->findFirstNodeOfType(NDT_RT_CAMERA));
  ArnLight *activeLight = static_cast<ArnLight *>(scene_graph->getSceneRoot()->findFirstNodeOfType(NDT_RT_LIGHT));
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  if (activeCam) {
    ArnConfigureViewportProjectionMatrixGl(&avd, activeCam);
    ArnConfigureViewMatrixGl(activeCam);
  }
  if (activeLight) {
    ArnConfigureLightGl(0, activeLight);
  }
  ArnSceneGraphRenderGl(scene_graph.get(), true);
}

void Renderer::draw_cone_and_ground() {
  glColor3f(1.0, 1.0, 1.0);
  static const double quad_size = 1.0;
  static const int multipliers[4][2] = { { 1, 1 }, { -1, 1 }, { -1, -1 }, { 1, -1 } };
  glBindTexture( GL_TEXTURE_2D, ground_tex );
  glBegin(GL_QUADS);
  for (int i = 0; i < 4; ++i) {
    glTexCoord2d( (multipliers[i][0]+1) / 2, (multipliers[i][1]+1) / 2 );
    glVertex2f(multipliers[i][0] * quad_size/2, multipliers[i][1] * quad_size/2);
  }
  glEnd();


  glPushMatrix();
  const Car &car = Car::getSingleton();
  glTranslated(car.get_pos()[0], car.get_pos()[1], car.get_pos()[2]);
  glBindTexture( GL_TEXTURE_2D, ground_tex2 );
  gluCylinder(quadric, 0.1, 0, 0.3, 32, 32);
  glPopMatrix();

  for (int i = 0; i < client_->get_client_counts(); ++i) {
    if (i != client_->getId()) {
      const double *const p = client_->get_client_point(i);
      glPushMatrix();
      glTranslated(p[0], p[1], p[2]);
      glBindTexture( GL_TEXTURE_2D, ground_tex2 );
      gluCylinder(quadric, 0.1, 0, 0.3, 32, 32);
      glPopMatrix();
    }
  }
}

void Renderer::resize(int X,int Y,int W,int H) {
  Fl_Gl_Window::resize(X,Y,W,H);
  glViewport(0,0,W,H);
  /*glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45, (double)W/H, 0.01, 100.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], up[0], up[1], up[2]);*/
  
  avd.Width = w();
  avd.Height = h();

  redraw();


}

void Renderer::initialize_arangl_stuff()
{
  if (InitializeRendererDependentOnce() < 0) {
    std::cerr << "InitializeRendererDependentOnce() failed." << std::endl;
    abort();
  }
  const char *scene_name = "MaterialTest.xml";
  ArnSceneGraphPtr sg(ArnSceneGraph::createFrom(scene_name));
  sg->interconnect(sg.get());
  std::cout << "   Scene file " << scene_name << "(prefix omitted) loaded successfully." << std::endl;
  ArnInitializeRenderableObjectsGl(sg.get());
  scene_graph = sg;
}

void Renderer::init_clients_position_data( ClientCore* client )
{
    client_ = client;
}

void Renderer::update_hero_pos()
{
  ArnMesh *m = reinterpret_cast<ArnMesh *>(scene_graph->getSceneRoot()->findFirstNodeOfType(NDT_RT_MESH));
  if (m) {
    const Car &car = Car::getSingleton();
    m->setLocalXform_Trans(ArnVec3(car.get_pos()[0], car.get_pos()[1], car.get_pos()[2]));
    m->recalcLocalXform();
  }
}

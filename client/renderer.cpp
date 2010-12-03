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
  printf("aha..\n");
  assert(gluBuild2DMipmaps);
  // build our texture mipmaps
  gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,
		     GL_RGB, GL_UNSIGNED_BYTE, data );
  printf("oho\n");
  // free buffer
  free( data );
  return texture;
}

Renderer::Renderer(int x, int y, int w, int h, const char *label)
: Fl_Gl_Window(x, y, w, h, label)
, ground_tex(0)
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

Renderer::~Renderer()
{
  glDeleteTextures( 1, &ground_tex );
}

void Renderer::init_renderer_independent_objects()
{
}

void Renderer::draw()
{
  static bool run_once = false;
  if (!run_once) {
    run_once = true;
    glEnable( GL_TEXTURE_2D );
    ground_tex = LoadTextureRAW ("../resources/ground2.raw", 0);
  }
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
  glBindTexture( GL_TEXTURE_2D, ground_tex );
  glBegin(GL_QUADS);
  for (int i = 0; i < 4; ++i) {
    glTexCoord2d( (multipliers[i][0]+1) / 2, (multipliers[i][1]+1) / 2 );
    glVertex2f(multipliers[i][0] * quad_size/2, multipliers[i][1] * quad_size/2);
  }
  glEnd();
}

void Renderer::resize(int X,int Y,int W,int H) {
  Fl_Gl_Window::resize(X,Y,W,H);
  glLoadIdentity();
  glViewport(0,0,W,H);
  glOrtho(-W,W,-H,H,-1,1);
  redraw();
}

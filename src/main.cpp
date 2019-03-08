
#include <iostream>
#include "glbackend/glselect.h"
#include "sgraytracer_cpuonly.h"
#include "common/logger.h"
#include "sgsphere.h"

#define FOVY 45.0
#define ZNEAR 0.01
#define ZFAR 100.0

using namespace std;
using namespace sda;
using namespace ps::raytracer;
using namespace ps::scene;

//create raytracer
ps::raytracer::RayTracer* g_prt = NULL;

void benchmark();

void draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //draw a textured rectangle to display the result
    float vertices [4][3] = { {-1.0, -1.0, 0.0}, {1.0, -1.0, 0.0},
                              {1.0, 1.0, 0.0}, {-1.0, 1.0, 0.0} };

    float texcoords [4][2] = { {0.0, 0.0}, {1.0, 0.0},
                               {1.0, 1.0}, {0.0, 1.0} };

    //binds rt frame
    if(g_prt)
        g_prt->framebuffer().bind();


    glPushMatrix();
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    //glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

    glBegin(GL_QUADS);
    glTexCoord2fv(&texcoords[0][0]);
    glVertex3fv(&vertices[0][0]);


    glTexCoord2fv(&texcoords[1][0]);
    glVertex3fv(&vertices[1][0]);


    glTexCoord2fv(&texcoords[2][0]);
    glVertex3fv(&vertices[2][0]);


    glTexCoord2fv(&texcoords[3][0]);
    glVertex3fv(&vertices[3][0]);
    glEnd();

    //unbinds ray tracer frame
    if(g_prt)
        g_prt->framebuffer().unbind();

    glPopAttrib();
    glPopMatrix();

    glutSwapBuffers();
}

void mouse_press(int button, int state, int x, int y) {

}

void mouse_move(int x, int y) {

}

void time_step() {

}

void close() {
    SAFE_DELETE(g_prt);

}

void def_resize(int w, int h) {
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluPerspective(FOVY, (double)w/(double)h, ZNEAR, ZFAR);
    glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void def_initgl() {
    //Setup Shading Environment
    static const GLfloat lightColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    static const GLfloat lightPos[4] = { 0.0f, 9.0f, 0.0f, 1.0f };

    //Setup Light0 Position and Color
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightColor);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightColor);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    //Turn on Light 0
    //glEnable(GL_LIGHT0);
    //Enable Lighting
    //glEnable(GL_LIGHTING);

    //Enable features we want to use from OpenGL
    glShadeModel(GL_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glEnable(GL_LINE_SMOOTH);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    //glClearColor(0.45f, 0.45f, 0.45f, 1.0f);
    glClearColor(1.0, 1.0, 1.0, 1.0);

    //Compiling shaders
    //	GLenum err = glewInit();
    //	if (err != GLEW_OK)
    //	{
    //		//Problem: glewInit failed, something is seriously wrong.
    //		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    //		exit(1);
    //	}
}

void onkey(unsigned char key, int x, int y) {
    switch(key) {
    case('r'): {
        vloginfo("oneshot");
        g_prt->run();
        vloginfo("oneshot");

        break;
    }

    case(27): {
        vloginfo("closing...");

#ifdef PS_OS_MAC
        close();
        exit(0);
#else
        glutLeaveMainLoop();
#endif
    }
        break;
    }
}


void onfunckey(int key, int x, int y) {
  switch(key) {
  case(GLUT_KEY_F5):
    benchmark();
    break;
  }
}

void benchmark() {
  vloginfo("start benchmark");

  const int nruns = 10;
  uint64_t average_time = 0;
  for(int i=0; i < nruns; i++) {
    g_prt->run();
    average_time += g_prt->get_duration_microseconds();
    std::cout << "run [ " << i + 1 << " of " << nruns << " ] duration = " << g_prt->get_duration_microseconds() << " microseconds" << std::endl; 
  }

  std::cout << "Average of [" << nruns << "] duration = [" << average_time / nruns << "] micro-seconds" << std::endl;

  vloginfo("finish benchmark");
}
int main(int argc, char* argv[]) {
    vloginfo("Starting raytracer.");

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
    glutInitWindowSize(RayTracer::kDefaultFrameWidth, RayTracer::kDefaultFrameHeight);
    glutCreateWindow("Raytracer");
    glutDisplayFunc(draw);
    glutReshapeFunc(def_resize);
    glutKeyboardFunc(onkey);
    glutSpecialFunc(onfunckey);
    glutMouseFunc(mouse_press);
    glutMotionFunc(mouse_move);
    //glutMouseWheelFunc(MouseWheel);
    //glutSpecialFunc(SpecialKey);
    //glutPassiveMotionFunc(MousePassiveMove);

#ifdef PS_OS_MAC
    glutWMCloseFunc(close);
#else
    glutCloseFunc(close);
#endif

    glutIdleFunc(time_step);

    //init gl
    def_initgl();

    //run the raytracer
    //g_prt = new RayTracer(RayTracer::kDefaultFrameWidth, RayTracer::kDefaultFrameHeight, 1);
    g_prt = new RayTracer(RayTracer::kFourKFrameWidth, RayTracer::kFourKFrameHeight, 1);

    //root node
    SGNodeList root;
    std::vector<Material> mtrl_list = {Material::red(), Material::green(), Material::blue()};

    const int nsx = 20;
    const int nsy = 20;
    for(int i = 0; i < nsx; i++) {
      for(int j = 0; j < nsy; j++) {

        int index = i * nsy + j;
        int mtrl_index = index % mtrl_list.size();
        
        //define the radius 
        float radius = RandRangeT<float>(0.1f, 0.5f);
        float depth = RandRangeT<float>(5.0f, 20.0f);
        float x = Lerp(static_cast<float>(i) / static_cast<float>(nsx), -2.0f, 2.0f);
        float y = Lerp(static_cast<float>(j) / static_cast<float>(nsy), -2.0f, 2.0f);

        //create the primitive 
        SGSphere* sphere = new SGSphere(vec3f(x, y, depth), radius);
        sphere->set_material(mtrl_list[mtrl_index]);
        root.add_node(sphere);
      }
    }    
    g_prt->set_rootnode(&root);
    g_prt->addlight(vec3f(0, 4, 4), Color::white());

    glutMainLoop();

    return 0;
}

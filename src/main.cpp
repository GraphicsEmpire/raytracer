
#include <iostream>
#include <GL/freeglut.h>
#include "raytracer_cpuonly.h"
#include "common/logger.h"
#include "common/cmdlineparser.h"
#include "sgsphere.h"

#define FOVY 45.0
#define ZNEAR 0.01
#define ZFAR 100.0

using namespace std;
using namespace sda;
using namespace sda::utils;
using namespace ps::raytracer;
using namespace ps::scene;

//create raytracer
ps::raytracer::RayTracer* g_prt = NULL;


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


	case(27): {
		vloginfo("closing...");
		glutLeaveMainLoop();
	}
	break;
	}
}

int main(int argc, char* argv[]) {
	vloginfo("Starting raytracer.");

	CmdLineParser parser;
	parser.parse(argc, argv);


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
	glutInitWindowSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
	glutCreateWindow("Raytracer");
	glutDisplayFunc(draw);
	glutReshapeFunc(def_resize);
	glutKeyboardFunc(onkey);
	glutMouseFunc(mouse_press);
	glutMotionFunc(mouse_move);
	//glutMouseWheelFunc(MouseWheel);
	//glutSpecialFunc(SpecialKey);
	//glutPassiveMotionFunc(MousePassiveMove);

	glutCloseFunc(close);
	glutIdleFunc(time_step);


	//init gl
	def_initgl();

	//run the raytracer
	g_prt = new RayTracer(DEFAULT_WIDTH, DEFAULT_HEIGHT, 1);
        
        //add sphere 
        SGSphere* sp = new SGSphere(vec3f(0.0f), 2.0);
        g_prt->add_node(sp);
        
	g_prt->run();

	glutMainLoop();

	return 0;
}

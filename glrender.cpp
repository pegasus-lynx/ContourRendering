#include "macros.hpp"
#include "glrender.hpp"

using namespace std;

void initGL() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor3f(1.0f,0.0f,0.0f);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 500.0, 0.0, 500.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void createWin(int argc,char** argv, char* name,int mode, int x, int y, int h,int w){
    glutInit(&argc,argv);
    glutInitDisplayMode(mode);
    glutInitWindowSize(w,h);
    glutInitWindowPosition(x,y);
    glutCreateWindow(name);
}
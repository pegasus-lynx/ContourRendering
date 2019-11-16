#include "glrender.hpp"
#include "contour.hpp"
#include "model.hpp"

using namespace std;

Model model;

GLfloat xRot = 0.0;
GLfloat zRot = 0.0;
GLfloat zoom = 1.0;

int typeMode = 1;

void renderBase(){
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glShadeModel(GL_SMOOTH);
	glBegin(GL_QUADS);

	glColor3f(0.2f, 1.0f, 0.5f);
	glNormal3d(0,0,1);
    glVertex3d(-1000,-1000,0);
    glVertex3d(-1000,1000,0);
    glVertex3d(1000,1000,0);
	glVertex3d(1000,-1000,0);

	glEnd();
	glDisable(GL_BLEND);
}

void displaySurface(){
	
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat light_position[] = { 1.0, 5.0, -10.0, 0.0 };
	GLfloat light_ambient[] = { 1.0, 0.0, 0.0, 1.0};

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    // glColor3f(0.0f, 1.0f, 0.0f);
    glFrontFace(GL_CW);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
	
	// Enable lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);

	glPushMatrix();

	// glTranslatef(-30.0f, -50.0f, 0.0f);
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(zRot, 0.0f, 0.0f, 1.0f);
	glScalef(zoom, zoom, zoom);

	// Model Rendering
	renderBase();
    model.drawSurface();

    glPopMatrix();
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

}

void displayContour(){
	glLineWidth(2.0);
	glColor3f(0.0f, 1.0f, 0.0f);

	glPushMatrix();

    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(zRot, 0.0f, 0.0f, 1.0f);
	glScalef(zoom, zoom, zoom);

	model.drawContour();

	glPopMatrix();
}

void display(){
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);

	glClear(GL_COLOR_BUFFER_BIT);
	typeMode==1?displaySurface():displayContour();
	// glutSwapBuffers();
	glFlush();
}

void ChangeSize(int w, int h){
	GLfloat nRange = 100.0f;
	if(h == 0)
		h = 1;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h)
		glOrtho(-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange, nRange);
	else
		glOrtho(-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange, nRange);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keys(unsigned char key, int x, int y){}

void sKeys(int key, int x, int y){
	if(key == GLUT_KEY_UP)
		xRot-= 5.0f;
	else if(key == GLUT_KEY_DOWN)
		xRot += 5.0f;
	else if(key == GLUT_KEY_RIGHT)
		zRot -= 5.0f;
	else if(key == GLUT_KEY_LEFT)
		zRot += 5.0f;
	else if(key > 356.0f)
		xRot = 0.0f;
	else if(key < -1.0f)
		xRot = 355.0f;
	else if(key > 356.0f)
		zRot = 0.0f;
	else if(key < -1.0f)
		zRot = 355.0f;
	else if(key == GLUT_KEY_PAGE_UP)
		zoom += 0.05f;
	else if(key == GLUT_KEY_PAGE_DOWN)
		zoom -= 0.05f;
	else
		exit(0);
	glutPostRedisplay();
}

void mainMenu(int id){
	typeMode = id;
	glutPostRedisplay();
}

void menu(){
	glutCreateMenu(mainMenu);
	glutAddMenuEntry("3D Render", 1);
	glutAddMenuEntry("Contour Input", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char **argv) {
    
    // char fname[40];
    // cout << "Input contour filename: ";
    // cin >> fname;

    model.loadContours("sample3.txt");

    // createWin(argc, argv, "Contour Rendering", GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH, 100, 100, 500, 500);

	glutInit(&argc, argv);	
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(-1, -1);
	glutCreateWindow("Contour Rendering");
    glViewport(-1000, -1000, 5000, 5000);

	glutReshapeFunc(ChangeSize);
    glutKeyboardFunc(keys);
    glutSpecialFunc(sKeys);
    glutDisplayFunc(display);

    initGL();
	menu();

    glutMainLoop();

    return 0;
}

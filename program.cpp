#include "glrender.hpp"
#include "contour.hpp"
#include "model.hpp"

using namespace std;

Model model;

GLfloat xRot = 0.0;
GLfloat yRot = 0.0;

void display(){
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat light_position[] = { 1.0, 1.0, -10.0, 0.0 };
	GLfloat light_ambient[] = { 1.0, 0.0, 0.0, 1.0};
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glShadeModel(GL_FLAT);
    // glFrontFace(GL_CW);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
	// Enable lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);

	glPushMatrix();

	glTranslatef(-30.0f, -50.0f, 0.0f);
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);

    model.draw3D();

    glPopMatrix();

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glutSwapBuffers();
}

void ChangeSize(int w, int h)
{
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
		yRot -= 5.0f;
	else if(key == GLUT_KEY_LEFT)
		yRot += 5.0f;
	else if(key > 356.0f)
		xRot = 0.0f;
	else if(key < -1.0f)
		xRot = 355.0f;
	else if(key > 356.0f)
		yRot = 0.0f;
	else if(key < -1.0f)
		yRot = 355.0f;
	else
		exit(0);
	glutPostRedisplay();
}

int main(int argc, char **argv) {
    
    // char fname[40];
    // cout << "Input contour filename: ";
    // cin >> fname;

    model.loadContours("sample.txt");

    // createWin(argc, argv, "Contour Rendering", GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH, 100, 100, 500, 500);

	glutInit(&argc, argv);	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(-1, -1);
	glutCreateWindow("Contour Rendering");
    glViewport(-1000, -1000, 5000, 5000);

	glutReshapeFunc(ChangeSize);
    glutKeyboardFunc(keys);
    glutSpecialFunc(sKeys);
    glutDisplayFunc(display);

    initGL();

    glutMainLoop();

    return 0;
}

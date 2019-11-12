#ifndef GLRENDER_H
#define GLRENDER_H

enum RenderStyle {
	WIREFRAME,
	SMOOTH,
	FLAT
};

void initGL();
void createWin(int argc, char** argv, char* name, int mode, int pos_x,int pos_y,int ht,int wt);

#endif
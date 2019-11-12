#include "glrender.hpp"
#include "contour.hpp"
#include "model.hpp"

int main(int argc, char **argv) {
    initGL();
    createWin(
        argc, argv, "Contour Rendering", GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH, 100, 100, 500, 500);
    Model model;
    char fname[40];
    cout << "Input contour filename: ";
    cin >> fname;
    model.loadContour(fname);
    return 0;
}

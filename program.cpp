#include "glrender.hpp"
#include "contour.hpp"
#include "model.hpp"

int main(int argc, char **argv) {
    initGL();
    createWin(
        argc, argv, "Contour Rendering", GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH, 100, 100, 500, 500);
    char c;
    Model model;
    
    cout << "Choice: { a : addContour, l : listContours, d : draw3d, e : exit} : \n";
    
    bool flag = true;
    
    while(flag) {
        cout << "Enter choice : ";
        cin >> c;
        switch(c){
            case 'a':
                model.addContour();
                break;
            case 'l':
                model.listContours();
                break;
            case 'd':
                model.draw3D();
                break;
            case 'e':
                flag=false;
                break;
        }
    }
    return 0;
}

#ifndef MODEL_H
#define MODEL_H
#include "contour.hpp"
#include "glrender.hpp"

class Model {
    public:
        ContourBox *contourBox;
        RenderStyle rStyle;
        bool meshOn, capsOn;

        Color currCol;
        int currLevel;
        int numContours;

        int sepPlane;

        Model();
        void addContour();
        void loadContour(char *filename);
        // void deleteContour();
        void listContours();
        void draw3D();
        void setCurrColor();
        void refresh();
        void eraseAll();
};

#endif
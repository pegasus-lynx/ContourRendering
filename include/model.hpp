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

        Model();
        void addContour();
        void finishContour();
        void deleteVertex();
        void draw3D();
        void setCurrColor();
        void refresh();
        void eraseAll();
};

#endif
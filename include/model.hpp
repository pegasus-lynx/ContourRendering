#ifndef MODEL_H
#define MODEL_H
#include "contour.hpp"
#include "glrender.hpp"

class Model {
    public:
        bContour *cBox;

        Model();
        void addContour();
        void loadContours(char *filename);
        
        
        void drawSurface();
        void drawContour();
        
        void refresh();
        void eraseAll();
};

#endif
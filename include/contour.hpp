// ==================================================================
// contains all information relating to contours in program
// ==================================================================

#ifndef CONTOUR_H
#define CONTOUR_H

#include "macros.hpp"
#include "glshape.hpp"
#include "glrender.hpp"

using namespace std;

class bContour;

class cContour {
    public:
        double ht;
        vector<Point> controlPts;
        bContour* cBox;

        cContour();
        cContour(double height, bContour *boxPtr);
        void addControlPts(Point newPt);
};

class bContour {
    public:
        map<double,cContour> contourSet;
        vector<double> heights;

        void addContour(cContour newContour);
        void addContour(vector<Point>& pts, double ht);
        // void eraseAll();
        void draw3D();
};

#endif


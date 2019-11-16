// ==================================================================
// contains all information relating to contours in program
// ==================================================================

#ifndef CONTOUR_H
#define CONTOUR_H

#include "macros.hpp"
#include "glshape.hpp"
#include "glrender.hpp"

using namespace std;

class ContourBox;

class Contour {
    public:
        double ht;
        vector<Point> controlPts;
        ContourBox* cBox;

        Contour();
        Contour(double height, ContourBox *boxPtr);
        void addControlPts(Point newPt);

        void plot();
};

class ContourBox {
    public:
        map<double,Contour> contourSet;
        vector<double> heights;

        void addContour(Contour newContour);
        void addContour(vector<Point>& pts, double ht);

        void drawSurface();
        void drawContour();

};

#endif


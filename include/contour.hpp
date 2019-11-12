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

//class representing a single contour
class Contour {
    public:
        Contour(ContourBox *boxPtr) {
            m_CBox=boxPtr;
            modified=false;
        }
        //set of vertices describing contour
        vector<Point> controlPts;
        //set of vertices describing convexHull of contour
        // vector<Point> convexHull;
        //color of contour
        Color color;
        //defines best-fit ellipse
        // BoundingE m_boundE;
        // bool hullSet,ellipseSet;

        //list of contours connected to this contour in next plane
        vector<Point> nextCont;
        
        //list of contours connected to this contour in previous plane
        vector<Point> prevCont;
    
        //optimal tiling found by tiling algorithm between this contour and each member of the
        //prevCont set.
        vector<vector<Point>> optimalPath;
        
        //pointer to entire contourBox.
        ContourBox *m_CBox;
        //marks whether or not the mesh needs to be rebuilt
        bool modified;
        
        // void setEllipse();
        // void setHull();
        
        void addControlPt(Point newPt);
        // void draw2D();

        //renders meshes to 3D view
        void draw3D(float sep,int level, RenderStyle rStyle,bool meshOn,bool capOn,int cNum);
        
        void optimizeTiling(int);
        /* Finds representation of contour with minimized vertices.
         * If multiple vertices are co-linear, only vertices at endpoints
         * will be saved.
         */
        void optimizeVertices();
        void insertPts(vector<Point> &tmpPts);
};


// defines all contours at a single level
class ContourPlane {
    public:
        //set of all contours on this plane
        vector<Contour> planeContours;
        void addContour(Contour newContour);
        void finishContour(int,bool);
        void addPoint(int contourNum, Point newPt);
        void draw3D(int planeNum,float sepStep, RenderStyle rStyle,bool meshOn,bool capOn);
        int getSize() {return planeContours.size(); }
        void setColor(int planeNum);
        Color getColor();
        void optimizeTiling(int,int);
};


//define all contours currently in existence
class ContourBox {
    public:
        //set of all image levels currently in existence
        vector<ContourPlane> contourSet;
        
        void addPlane(ContourPlane newPlane);
        int getNumContours(int planeNum);
        void newContour(int planeNum, Contour newContour);
        void getLastPt(int currLevel,int numContours,Point &prevPt);
        void deleteVertex(int currLevel,int currPickC,int currPickV);
        void finishContourLoad(int , int);
        void newStrip(Point,Point);
        void remesh();
        void addPoint(int planeNum, int contourNum, Point newPt);
        void draw3D(float sepStep,RenderStyle rStyle,bool meshOn,bool capOn);
        void eraseAll(int);
        Color getPlaneColor(int planeNum);
        Contour *getContour(int planeNum,int contourNum);
        void insertPts(vector<Point> &tmpPts,int currLevel,int currC);
        Point currScrollPos;
        void modifyPoint(int currLevel,Point target,int currPickC,int currPickV);
        void makeTrans();
        void makeInvis();
        void resetView();
};

#endif


// ==================================================================
// contourBox.h
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
            hullSet=transp=invis=ellipseSet=false;
            m_CBox=boxPtr;
            picked=false;
            modified=false;
        }
        //set of vertices describing contour
        vector<Point> controlPts;
        //set of vertices describing convexHull of contour
        vector<Point> convexHull;
        //color of contour
        Color color;
        //defines best-fit ellipse
        // BoundingE m_boundE;
        bool hullSet,ellipseSet;
        //are tilings invisible?
        bool invis;
        //are tilings transparent?
        bool transp;

        //list of contours connected to this contour in next plane
        vector<Point> nextCont;
        
        //list of contours connected to this contour in previous plane
        vector<Point> prevCont;
    
        //optimal tiling found by tiling algorithm between this contour and each member of the
        //prevCont set.
        vector<vector<Point> > optimalPath;
        
        //list of vertices currently picked 
        vector<int> pickedNums;
        //is contour picked? 
        bool picked;
        //pointer to entire contourBox.
        ContourBox *m_CBox;
        //marks whether or not the mesh needs to be rebuilt
        bool modified;
        
        bool deleteVertices();
        bool pickPoint(Point target,int &currPickV);
        void setEllipse();
        void setHull();
        void addControlPt(Point newPt);
        void draw2D();
        void draw3D(float sep,int level, RenderStyle rStyle,bool meshOn,bool capOn,int cNum);
        void optimizeTiling(int);
        void optimizeVertices();
        void insertPts(vector<Point> &tmpPts);
        void pickBox(Point boxStart, Point boxCurr);
};


// defines all contours at a single level
class ContourPlane {
    public:
        //set of all contours on this plane
        vector<Contour> planeContours;
        void addContour(Contour newContour);
        void finishContour(int,bool);
        void modifyContour(int);
        void addPoint(int contourNum, Point newPt);
        void draw2D();
        void draw3D(int planeNum,float sepStep, RenderStyle rStyle,bool meshOn,bool capOn);
        int getSize() {return planeContours.size(); }
        Color getColor();
        void optimizeTiling(int,int);
        bool pickPoint(Point target,int &currPickC, int &currPickV,bool);
};


//define all contours currently in existence
class ContourBox {
    public:
        //set of all image levels currently in existence
        vector<ContourPlane> contourSet;
        
        void pickContour(Point);
        void updateCorresp(ContourPlane &plane1, ContourPlane &plane2,int plane1Num);
        void pickChain(Point);
        void addBranch(Point newB);
        void eraseBranch(Point newB);
        void deselectAll();
        void deselectAll2d();
        void addPlane(ContourPlane newPlane);
        int getNumContours(int planeNum);
        void newContour(int planeNum, Contour newContour);
        void getLastPt(int currLevel,int numContours,Point &prevPt);
        void deleteVertex(int currLevel,int currPickC,int currPickV);
        void finishContour(int , int, bool);
        void finishContourLoad(int , int);
        void cleanUpBranches(int,int);
        void newStrip(Point,Point);
        int deleteBoxVertices(int);
        void remesh();
        void saveModel(char *filename,float);
        void saveContour(float,char *);
        void updateCooresp(ContourPlane &plane1, ContourPlane &plane2);
        void addPoint(int planeNum, int contourNum, Point newPt);
        vector<Point> getControlPts(int,int);
        void draw2D(int currLevel);
        void draw3D(float sepStep,RenderStyle rStyle,bool meshOn,bool capOn);
        void eraseAll(int);
        Point getPlaneColor(int planeNum);
        Contour *getContour(int planeNum,int contourNum);
        void pickPoint(int currLevel,Point target,int &currPickC,int &currPickV,bool);
        void pickBox(int currLevel,Point boxStart, Point boxCurr);
        void modifyContour(int planeNum, int contourNum);
        void insertPts(vector<Point> &tmpPts,int currLevel,int currC);
        Point currScrollPos;
        void modifyPoint(int currLevel,Point target,int currPickC,int currPickV);
        void modifyAllPoints(int currLevel,Point target,int currPickC);
        void makeTrans();
        void makeInvis();
        void resetView();
};

#endif


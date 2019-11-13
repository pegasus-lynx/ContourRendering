#include "contour.hpp"
#include "glrender.hpp"
#include "tiling.hpp"
using namespace std;


//////////////////////////////////////////////////////////////////////////////////////////////
/*
 *  Contour definitions
 */

// void Contour::addControlPt(Point newPt) {
//     controlPts.pb(newPt);
// }

// void Contour::optimizeTiling(int planeNum) {
//     int x = prevCont.size() - 1;
//     optimalTiling(controlPts, m_CBox->getContour(prevCont[x].x, prevCont[x].y)->controlPts, optimalPath[x]);
// }

// double dist2d(Point target, Point dest) {
//     return sqrt( (target.y-dest.y)*(target.y-dest.y) + (target.x-dest.x)*(target.x-dest.x) );
// }

// void Contour::insertPts(vector<Point> &tmpPts) {
//     int p1 = 0;
//     int p2 = controlPts.size() - 1;
//     double startDist,endDist;
//     startDist = dist2d(tmpPts[0],controlPts[ p1 ]);
//     endDist = dist2d(tmpPts[0],controlPts[ p2 ]);
//     if(startDist < endDist) {
//         if(p1 < p2 ) {
//             if(p1==0 && p2==(controlPts.size()-1) || 
//                 p2==0 && p1==(controlPts.size()-1) ) {
//                 for(int x=tmpPts.size()-1;x>=0;x--) 
//                     controlPts.push_back(tmpPts[x]);
//             }
//             else {
//                 for(int x=0;x<tmpPts.size();x++) 
//                     controlPts.insert(controlPts.begin()+p1+x+1,tmpPts[x]);
//             }
//         }
//         else {
//             if(p1==0 && p2==(controlPts.size()-1) || 
//                 p2==0 && p1==(controlPts.size()-1) ) {
//                 for(int x=0;x<tmpPts.size();x++) 
//                     controlPts.push_back(tmpPts[x]);
//             }
//             else {
//                 for(int x=tmpPts.size()-1;x>=0;x--) 
//                     controlPts.insert(controlPts.begin()+p2+( (tmpPts.size()-1) - x )+1,tmpPts[x]);
//             }
//         }
//     }
//     else {
//         if(p1 < p2 ) {
//             if(p1==0 && p2==(controlPts.size()-1) || 
//                 p2==0 && p1==(controlPts.size()-1) ) {
//                 for(int x=0;x<tmpPts.size();x++) 
//                     controlPts.push_back(tmpPts[x]);
//             }
//             else {
//                 for(int x=tmpPts.size()-1;x>=0;x--) 
//                     controlPts.insert(controlPts.begin()+p1+ ( (tmpPts.size()-1) - x )+1,tmpPts[x]);
//             }
//         }
//         else {
//             if(p1==0 && p2==(controlPts.size()-1) || 
//                 p2==0 && p1==(controlPts.size()-1) ) {
//                 for(int x=tmpPts.size()-1;x>=0;x--) 
//                     controlPts.push_back(tmpPts[x]);
//             }
//             else {
//                 for(int x=0;x<tmpPts.size();x++) 
//                     controlPts.insert(controlPts.begin()+p2+x+1,tmpPts[x]);
//             }
//         }
//     }
// }

// void Contour::draw3D(float sepStep,int level, RenderStyle rStyle, bool meshOn, bool capOn, int cNum) {
//     GLUquadricObj *qua;
//     Contour *next, *prev;

//     float sep = level * sepStep;
//     if (!(capOn && meshOn && rStyle == SMOOTH))
//         glDisable(GL_LIGHTING);
//     else if (capOn && (nextCont.size() == 0 || prevCont.size() == 0)) {
//         glEnable(GL_LIGHTING);
//         glBegin(GL_POLYGON);
//     }

//     // draw contour
//     int i;
//     for (i = 0; i < controlPts.size() - 1; ++i) {
//         if(!(capOn&&meshOn&&rStyle==SMOOTH)) {
//             glColor3ub(255,255,255);
//             glPointSize(4);
//             glBegin(GL_POINTS);
//             glVertex3d(controlPts[i].x/90.0-2, .1+sep/2.0, -controlPts[i].y/90.0+7);
//             glEnd();
//         }

//         if(!(capOn&&meshOn && rStyle==SMOOTH))
//             glBegin(GL_LINES);
//         glColor3ub(color.r, color.g, color.b);
//         glVertex3d(controlPts[i].x/90.0-2, .1+sep/2.0, -controlPts[i].y/90.0+7);
        
//         if(!(capOn&&meshOn&&rStyle==SMOOTH))  {
//             glVertex3d(controlPts[i+1].x/90.0-2,.1+sep/2.0, -controlPts[i+1].y/90.0+7);
//             glEnd();
//         }
//     }

//     if(!(capOn&&meshOn&&rStyle==SMOOTH) ) {
//         glBegin(GL_LINES);
//         glColor3ub(color.r, color.g, color.b);
//         glVertex3d(controlPts[i].x/90.0-2, .1+sep/2.0, -controlPts[i].y/90.0+7);
//         glVertex3d(controlPts[i].x/90.0-2, .1+sep/2.0, -controlPts[i].y/90.0+7);
//         glEnd();
//     } else {
//         glVertex3d(controlPts[i].x/90.0-2, .1+sep/2.0, -controlPts[i].y/90.0+7);
//         glEnd();
//         glDisable(GL_LIGHTING);
//     }

//     if(!capOn) {
//         glPointSize(4);
//         glBegin(GL_POINTS);
//         glColor3ub(255,255,255);
//         glVertex3d(controlPts[i].x/90.0-2, .1+sep/2.0, -controlPts[i].y/90.0+7 );
//         glEnd();
//     }

//     for (int mm = 0; mm < prevCont.size(); ++mm) {
//         prev = m_CBox->getContour(prevCont[mm].x, prevCont[mm].y);
//         switch(rStyle) {
//             case SMOOTH:
//                 glEnable(GL_LIGHTING);
//                 glEnable(GL_BLEND);
//                 glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
//                 glShadeModel(GL_SMOOTH);
//                 glBegin(GL_TRIANGLES);
//                 glColor4ub(color.r, color.g, color.b, color.a);

//                 for(int q=0;q<optimalPath[mm].size()-2;q++) {
//                     if(optimalPath[mm][q].y==optimalPath[mm][q+1].x) {
//                         glNormal3f(-prev->controlPts[optimalPath[mm][q].y].x/90.0-2,.1+(sep-sepStep)/2.0,-prev->controlPts[optimalPath[mm][q].y].y/90.0+7);

//                         glVertex3d(controlPts[optimalPath[mm][q].x].x/90.0-2,.1+sep/2.0,-controlPts[optimalPath[mm][q].x].y/90.0+7);
//                         glVertex3d(prev->controlPts[optimalPath[mm][q].y].x/90.0-2,.1+(sep-sepStep)/2.0,-prev->controlPts[optimalPath[mm][q].y].y/90.0+7);
//                         glVertex3d(controlPts[optimalPath[mm][q+1].x].x/90.0-2,.1+sep/2.0,-controlPts[optimalPath[mm][q+1].x].y/90.0+7);
//                     }
//                     else  {
//                         glNormal3f(-prev->controlPts[optimalPath[mm][q].y].x/90.0-2,.1+(sep-sepStep)/2.0,-prev->controlPts[optimalPath[mm][q].y].y/90.0+7);
                    
//                         glVertex3d(controlPts[optimalPath[mm][q].x].x/90.0-2,.1+sep/2.0,-controlPts[optimalPath[mm][q].x].y/90.0+7);
//                         glVertex3d(prev->controlPts[optimalPath[mm][q].y].x/90.0-2,.1+(sep-sepStep)/2.0,-prev->controlPts[optimalPath[mm][q].y].y/90.0+7);
//                         glVertex3d(prev->controlPts[optimalPath[mm][q+1].y].x/90.0-2,.1+(sep-sepStep)/2.0,-prev->controlPts[optimalPath[mm][q+1].y].y/90.0+7);
//                     }
//                 }
//                 glEnd();
//                 glDisable(GL_BLEND);
//                 break;
//             case FLAT:
//                 glEnable(GL_LIGHTING);
//                 //glBegin(GL_TRIANGLE_STRIP);
//                 glShadeModel(GL_FLAT);
//                 glColor3ub(color.r, color.g, color.b);
//                 break;
//             case WIREFRAME:
//                 // need to find best-fit ellipse.
//                 break;
//         }
//     }
// }


// void Contour::optimizeVertices() {
//     int x=0;
//     //records start and end of collapsed vertex region
//     int start=x;
//     float xVal,yVal,angle;
//     float angle2;
//     bool startC=false;
    
//     //sum of angle differences
//     float totalDiff=0;
    
//     if(controlPts.size() < 3) 
//         return;

//     xVal = controlPts[x].x - controlPts[x+1].x;
//     yVal = controlPts[x].y - controlPts[x+1].y;
//     angle = atan2(yVal,xVal);
//     x++;

//     //Combine pts if their angle is within a given threshold
//     while((x+1)<controlPts.size() ) {
//         xVal = controlPts[x].x - controlPts[x+1].x;
//         yVal = controlPts[x].y - controlPts[x+1].y;
//         angle2 = atan2(yVal,xVal);
//         totalDiff+=angle2-angle;
//         angle=angle2;
//         if(fabs(totalDiff) > .12) {
//             if(startC && ((x-start)>2 ) ) {
//                 controlPts.erase(controlPts.begin()+start+1,controlPts.begin()+x-1);
//                 start+=1;
//                 x=start+1;
//             }
//             else {
//                 start++;x++;
//             }
//             startC=false;
//             totalDiff=0;
//         }
//         else {
//             x++;
//             startC=true;
//         }
//     }
// }

// /*
//  *  ContourPlane definitions
//  */

// void ContourPlane::addContour(Contour newContour) {
//     planeContours.pb(newContour);
// }

// void ContourPlane::finishContour(int contourNum, bool optVerts) {
//     if (optVerts)   planeContours[contourNum].optimizeVertices();
// }

// void ContourPlane::addPoint(int contourNum, Point newPt) {
//     planeContours[contourNum].addControlPt(newPt);
// }

// void ContourPlane::optimizeTiling(int planeNum, int contourNum) {
//     planeContours[contourNum].optimizeTiling(planeNum);
// }

// void ContourPlane::draw3D(int planeNum, float sepStep,RenderStyle rStyle,bool meshOn,bool capOn) {
//     for (int i = 0; i < planeContours.size(); i++)
//         planeContours[i].draw3D(sepStep, planeNum, rStyle, meshOn, capOn, i);
// }

// void ContourPlane::setColor(int planeNum){
//     double v = (double)planeNum*0.05;
//     Color c(v,v,v,1);
    
//     rep(i,0,planeContours.size()){
//         planeContours[i].color=c;
//     }
// }

// Color ContourPlane::getColor() {
//     return planeContours[0].color;
// }

// /*
//  *  ContourBox definitions
//  */

// void ContourBox::addPlane(ContourPlane newPlane) {
//     newPlane.setColor(contourSet.size());
//     contourSet.pb(newPlane);
// }

// void ContourBox::addPoint(int planeNum, int contourNum, Point newPt) {
//     contourSet[planeNum].addPoint(contourNum, newPt);
// }

// void ContourBox::newContour(int planeNum, Contour newContour) {
//     contourSet[planeNum].addContour(newContour);
// }

// void ContourBox::modifyPoint(int currLevel, Point target,int currPickC,int currPickV) {
//     contourSet[currLevel].planeContours[currPickC].controlPts[currPickV] = target;
//     contourSet[currLevel].planeContours[currPickC].modified = true;
// }

// void ContourBox::finishContourLoad(int planeNum, int contourNum) {
//     contourSet[planeNum].finishContour(contourNum, true);
//     if (planeNum > 0 && contourSet[planeNum - 1].planeContours.size() > 0) {
//         contourSet[planeNum].optimizeTiling(planeNum, contourNum);
//     }
//     if (planeNum < contourSet.size() - 1) {
//         if (contourSet[planeNum].planeContours[contourNum].nextCont.size() > 0) {
//             for (int i = 0; i < contourSet[planeNum].planeContours[contourNum].nextCont.size(); ++i) {
//                 contourSet[planeNum+1].optimizeTiling(planeNum+1, contourSet[planeNum].planeContours[contourNum].nextCont[i].y);
//             }
//         }
//     }
// }

// void ContourBox::draw3D(float sepStep,RenderStyle rStyle,bool meshOn,bool capOn) {
//     for(int i=0;i<contourSet.size();i++) {
//         contourSet[i].draw3D(i,sepStep,rStyle,meshOn,capOn);
//     }
// }

// int ContourBox::getNumContours(int planeNum) {
//     return contourSet[planeNum].getSize();
// }

// Color ContourBox::getPlaneColor(int planeNum) {
//     return contourSet[planeNum].getColor();
// }

// void ContourBox::insertPts(vector<Point> &pts, int currLvl, int currContour) {
//     contourSet[currLvl].planeContours[currContour].insertPts(pts);
// }

// void ContourBox::makeTrans() {
//     for(int x=0;x<contourSet.size();x++)
//         for(int y=0;y<contourSet[x].planeContours.size();y++)
//             contourSet[x].planeContours[y].color.a = 130;
// }

// void ContourBox::makeInvis() {
//     for(int x=0;x<contourSet.size();x++)
//         for(int y=0;y<contourSet[x].planeContours.size();y++)
//             contourSet[x].planeContours[y].color.a = 0;
// }

// void ContourBox::resetView() {
//         for(int x=0;x<contourSet.size();x++)
//             for(int y=0;y<contourSet[x].planeContours.size();y++)
//                 contourSet[x].planeContours[y].color.a = 255;
// }

// Contour *ContourBox::getContour(int planeNum, int contourNum) {
//     return &(contourSet[planeNum].planeContours[contourNum]);
// }

// void ContourBox::deleteVertex(int currLevel,int currPickC,int currPickV) {
//     contourSet[currLevel].planeContours[currPickC].controlPts.erase(contourSet[currLevel].planeContours[currPickC].controlPts.begin()+currPickV);
//     contourSet[currLevel].planeContours[currPickC].modified=true;
// }

// void ContourBox::eraseAll(int currLevel) {
//     for(int x=contourSet[currLevel].planeContours.size()-1;x>=0;x--)  {
//         contourSet[currLevel].planeContours.erase(contourSet[currLevel].planeContours.begin()+x);
//     }
// }

// void ContourBox::newStrip(Point upper, Point lower) {
//     contourSet[upper.x].planeContours[upper.y].prevCont.pb(lower);
//     contourSet[lower.x].planeContours[lower.y].nextCont.pb(upper);

//     vector<Point> *newTiling = new vector<Point>;
//     contourSet[upper.x].planeContours[upper.y].optimalPath.pb(*newTiling);
//     contourSet[upper.x].optimizeTiling(upper.x, upper.y);
// }

// void ContourBox::remesh() {
//     int m;
//     Contour *prev;
//     vector<Point> modPrevs;
//     for(int x=0;x<contourSet.size();x++) {
//         for(int y=0;y<contourSet[x].planeContours.size();y++) {
//             for(m=0;m<contourSet[x].planeContours[y].prevCont.size();m++) {
//                 prev = getContour(contourSet[x].planeContours[y].prevCont[m].x, contourSet[x].planeContours[y].prevCont[m].y);
//                 if(prev->modified)
//                     modPrevs.push_back( Point( contourSet[x].planeContours[y].prevCont[m].x,contourSet[x].planeContours[y].prevCont[m].y) );
//             }

//             if(contourSet[x].planeContours[y].modified) {
//                 for(m=0;m<contourSet[x].planeContours[y].prevCont.size();m++) {
//                     prev = getContour(contourSet[x].planeContours[y].prevCont[m].x,contourSet[x].planeContours[y].prevCont[m].y);
//                     optimalTiling(contourSet[x].planeContours[y].controlPts,prev->controlPts,contourSet[x].planeContours[y].optimalPath[m]);
//                 }
//             }
//             else if(modPrevs.size()!=0) {
//                 for(m=0;m<modPrevs.size();m++) {
//                     prev = getContour(modPrevs[m].x,modPrevs[m].y);
//                     optimalTiling(contourSet[x].planeContours[y].controlPts,prev->controlPts,contourSet[x].planeContours[y].optimalPath[m]);
//                 }
//                 modPrevs.erase( modPrevs.begin(),modPrevs.end() );
//             }
//         }
//     }
// }


////////////////////////////////////////////////////////////////////////

//////////// Util Functions //////////////////

// Distance between two points
double _dist(Point &p, Point &q){
    return sqrt(pow(p.x-q.x,2) + pow(p.y-q.y,2) + pow(p.z-q.z,2));
}

// Area of a triangle
double _areaTriangle(Point &a,Point &b,Point &c){
    double sa = _dist(c,b);
    double sb = _dist(a,c);
    double sc = _dist(a,b);
    double s = (sa+sb+sc)/2;
    return sqrt(s*(s-sa)*(s-sb)*(s-sc));
}

// Get normal of the triangle

Point _getNormal(Point& a,Point& b,Point& c){
    Point v1(b.x-a.x, b.y-a.y, b.z-a.z);
    Point v2(c.x-a.x, c.y-a.y, c.z-a.z);

    Point nor;

    nor.x = v1.y*v2.z - v1.z*v2.y;
    nor.y = v1.z*v2.x - v1.x*v2.z;
    nor.z = v1.x*v2.y - v1.y*v2.x;

    return nor;
}

// Render the shapes ( OpenGL part )

void renderTriangle(Point& a,Point& b,Point& c){

    Point nor = _getNormal(a,b,c);

    glEnable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glShadeModel(GL_SMOOTH);
    glBegin(GL_TRIANGLES);

    glColor3f(1.0f, 0.2f, 0.5f);
    glNormal3d(nor.x,nor.y,nor.z);
    glVertex3d(a.x,a.y,a.z);
    glVertex3d(b.x,b.y,b.z);
    glVertex3d(c.x,c.y,c.z);

    glEnd();
    glDisable(GL_BLEND);

}

// Get the path between the strips
void getOptPath(cContour& low, cContour& up, vector<Point> &path){
    vector<Point>& lr = low.controlPts;
    vector<Point>& ur = up.controlPts;
    
    int ls = lr.size();
    int us = ur.size();

    double dp[ls+1][us+1];
    int bk[ls+1][us+1];

    // Initialize the arrays :
    rep(i,0,ls+1) rep(j,0,us+1) dp[i][j] = DBL_MAX;
    rep(i,0,ls+1) rep(j,0,us+1) bk[i][j] = 0;

    // Base cases :
    dp[0][0]=0;
    rep(i,1,ls+1){
        dp[i][0] = dp[i-1][0] + _areaTriangle(ur[0],lr[i-1],lr[i%ls]);
        bk[i][0] = 2;
    }   
    rep(i,1,us+1){
        dp[0][i] = dp[0][i-1] + _areaTriangle(lr[0],ur[i-1],ur[i%us]);
        bk[0][i] = 1;
    }

    // DP Equation :
    rep(i,1,ls+1){
        rep(j,1,us+1){
            dp[i][j] = dp[i-1][j] + _areaTriangle(ur[j%us],lr[i%ls],lr[i-1]);
            bk[i][j] = 2;

            double temp = dp[i][j-1] + _areaTriangle(ur[j%us],ur[j-1],lr[i%ls]);
            if(temp<dp[i][j]){
                dp[i][j] = temp;
                bk[i][j] = 1;
            }
        }
    }

    // Getting the result from backtracking :
    int p=ls, q=us;
    Point bp = lr[p%ls], bq = ur[q%us];
    
    // if(bk[p][q]==2){
    //     path.pb(ur[0]);
    // }
    // else{
    //     path.pb(lr[0]);
    // }

    vector< pair< Point, pair <Point,Point> > > triangles;

    while(p!=0 || q!=0){
        
        if(bk[p][q]==2){
            p--;
            path.pb(lr[p%ls]);
            triangles.pb({lr[p%ls] ,{bp, ur[q%us]}});
            bp = lr[p%ls];
        }
        else{
            q--;
            triangles.pb({bq ,{ur[q%us], lr[p%ls]}});
            bq = ur[q%us];
            path.pb(ur[q%us]);
        }
    }

    cout<<triangles.size()<<endl;



    glEnable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glShadeModel(GL_SMOOTH);
    glBegin(GL_TRIANGLES);

    for(auto it:triangles){
        cout<<it.first.x<<" "<<it.first.y<<" "<<it.first.z<<endl;
        cout<<it.second.second.x<<" "<<it.second.second.y<<" "<<it.second.second.z<<endl;
        cout<<it.second.first.x<<" "<<it.second.first.y<<" "<<it.second.first.z<<endl;
        renderTriangle(it.first, it.second.first, it.second.second);
    }

    // Check the path :
    // cout<<"Debug : "<<path.size()<<endl;
    // rep(i,0,path.size()) cout<<path[i].x<<" "<<path[i].y<<" "<<path[i].z<<"\n";
}











//////////// Main Functions ///////////////////

cContour::cContour(){}

cContour::cContour(double height, bContour* boxPtr){
    ht = height;
    cBox = boxPtr;
}

void cContour::addControlPts(Point newPt){
    controlPts.pb(newPt);
}


void bContour::addContour(cContour newContour){
    heights.pb(newContour.ht);
    sort(all(heights));
    contourSet[newContour.ht] = newContour;
}

void bContour::addContour(vector<Point>& pts, double ht){
    heights.pb(ht);
    sort(all(heights));
    cContour newContour(ht,this);
    rep(i,0,pts.size()) newContour.addControlPts(pts[i]);
    contourSet[newContour.ht] = newContour;
}

void bContour::draw3D(){

    // Here algorithm would be to take two adjacent contours
    // Then build the path between then using the DP algorithm
    // Once the path is built, render the surface.
    // Loop the process for all heights.

    rep(i,0,heights.size()-1){
        cContour &lower = contourSet[heights[i]];        
        cContour &upper = contourSet[heights[i+1]];

        vector<Point> optPath;

        getOptPath(lower,upper,optPath);
    }
}
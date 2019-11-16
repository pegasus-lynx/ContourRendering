#include "contour.hpp"
#include "glrender.hpp"
#include "tiling.hpp"
using namespace std;


//////////// Util Functions /////////////////////////////////////////////////////////////

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

    nor.normalize();

    return nor;
}

// Render the shapes ( OpenGL part )
void renderTriangle(Point& a,Point& b,Point& c){
    Point nor = _getNormal(a,b,c);

    glBegin(GL_TRIANGLES);

    glColor3f(1.0f, 0.2f, 0.5f);
    glNormal3d(nor.x,nor.y,nor.z);
    glVertex3d(a.x,a.y,a.z);
    glVertex3d(b.x,b.y,b.z);
    glVertex3d(c.x,c.y,c.z);

    glEnd();
}

// Get the path between the strips
void getOptPath(Contour& low, Contour& up, vector<Point> &path){
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

    for(auto it:triangles){
        renderTriangle(it.first, it.second.first, it.second.second);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////

//////////// Contour Methods /////////////////////////////////////////////////////////////

Contour::Contour(){}

Contour::Contour(double height, ContourBox* boxPtr){
    ht = height;
    cBox = boxPtr;
}

void Contour::addControlPts(Point newPt){
    controlPts.pb(newPt);
}

void Contour::plot(){
    glBegin(GL_LINE_LOOP);
    glColor3f(1.0f, 0.2f, 0.5f);
    rep(i,0,controlPts.size()){
        glVertex3d(controlPts[i].x,controlPts[i].y,controlPts[i].z);
    }
    glEnd();
}

void ContourBox::addContour(Contour newContour){
    heights.pb(newContour.ht);
    sort(all(heights));
    contourSet[newContour.ht] = newContour;
}

void ContourBox::addContour(vector<Point>& pts, double ht){
    heights.pb(ht);
    sort(all(heights));
    Contour newContour(ht,this);
    rep(i,0,pts.size()) newContour.addControlPts(pts[i]);
    contourSet[newContour.ht] = newContour;
}

void ContourBox::drawSurface(){
    // Here algorithm would be to take two adjacent contours
    // Then build the path between then using the DP algorithm
    // Once the path is built, render the surface.
    // Loop the process for all heights.

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glShadeModel(GL_SMOOTH);

    rep(i,0,heights.size()-1){
        Contour &lower = contourSet[heights[i]];        
        Contour &upper = contourSet[heights[i+1]];

        vector<Point> optPath;

        getOptPath(lower,upper,optPath);
    }

    glDisable(GL_BLEND);
}

void ContourBox::drawContour(){

    rep(i,0,heights.size()){
        contourSet[heights[i]].plot();
    }

}

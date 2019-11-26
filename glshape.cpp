#include "macros.hpp"
#include "glshape.hpp"
#include <GL/glut.h>

using namespace std;

Color::Color(){
    r = g = b = 0;
    a = 1;
}

Color::Color(float red,float green,float blue,float alpha){
    r = red; g = green; b = blue; a = alpha;
}

void Closed::setCol(Color color){
    this->color = color;
}

void Closed::setCol(float red,float green,float blue,float alpha){
    this->color.r = red; 
    this->color.g = green; 
    this->color.b = blue; 
    this->color.a = alpha; 
}

float* Color::vec(){
    float colorVars[4];
    colorVars[0] = r;
    colorVars[1] = g;
    colorVars[2] = b;
    colorVars[3] = a;
    return colorVars;
}

Point::Point(){
    x = 0, y = 0, z = 0;
    dimension = 3;
    // color = Color();
}

Point::Point(double x,double y){
    this->x = x, this->y = y;
    dimension = 2;
    // color = Color();
}

Point::Point(double x,double y, double z){
    this->x = x, this->y = y, this->z = z;
    dimension = 3;
    // color = Color();
}

double* Point::getPos() {
    double position[dimension];
    position[0] = x, position[1] = y;
    if (dimension > 2)  position[2] = z;
    return position;
}

void Point::plot(){
    // glColor4d(color.r,color.g,color.b,color.a);
    glBegin(GL_POINTS);
    if (dimension == 2) glVertex2d(x, y);
    else if (dimension == 3) glVertex3d(x, y, z);
    glEnd();
}

double Point::magnitude() {
    return sqrt(x*x + y*y + z*z);
}

void Point::normalize() {
    double mag = magnitude();
    x /= mag;
    y /= mag;
    z /= mag;
}

Line::Line(){
    stPoint = Point();
    endPoint = Point(); 
    color = Color();  
}

Line::Line(Point&a , Point&b ){
    stPoint = a;
    endPoint = b;
    color = Color();  
}

Line::Line(double xa,double ya,double xb,double yb){
    stPoint = Point(xa,ya);
    endPoint = Point(xb,yb);
    color = Color();  
}

void Line::plot(){
    glColor4d(color.r,color.g,color.b,color.a);
    glBegin(GL_LINE);

    if(stPoint.dimension == 2)  glVertex2d(stPoint.x, stPoint.y);
    else if (stPoint.dimension == 3) glVertex3d(stPoint.x, stPoint.y, stPoint.z);

    if(endPoint.dimension == 2)  glVertex2d(endPoint.x, endPoint.y);
    else if (endPoint.dimension == 3) glVertex3d(endPoint.x, endPoint.y, endPoint.z);

    glEnd();
}

Circle::Circle(){
    center = Point();
    radius = 0;
    color = Color();
    fillColor = Color(0.7,0.7,0.7);
}

Circle::Circle(double rad, Point& center){
    this->center = center;
    radius = rad;
    color = Color();
    fillColor = Color(0.7,0.7,0.7);
}

//  Complete plot circle function
void Circle::plot(){
    glColor4d(color.r,color.g,color.b,color.a);
    // glBegin(GL_CIR)
}

Polygon::Polygon(){
    n_vt = 0;
    color = Color();
    fillColor = Color(0.7,0.7,0.7);
}

Polygon::Polygon(int n){
    n_vt = n;
    color = Color();
    fillColor = Color(0.7,0.7,0.7);
}

Polygon::Polygon(vector<Point>& pts){
    n_vt = pts.size();
    vertices = pts;
    color = Color();
    fillColor = Color(0.7,0.7,0.7);
}

Polygon::Polygon(vector<pair<double, double> >& vec){
    n_vt = vec.size();
    rep(i,0,n_vt) vertices.pb(Point(vec[i].X, vec[i].Y));
    color = Color();
    fillColor = Color(0.7,0.7,0.7);
}

void Polygon::plot(){
    glColor4d(color.r,color.g,color.b,color.a);
    glBegin(GL_LINE_LOOP);
    rep(i,0,vertices.size()){
        glVertex2d(vertices[i].x,vertices[i].y);
    }
    glEnd();
}

Triangle::Triangle(){
    color = Color();
    fillColor = Color(0.7,0.7,0.7);
}

Triangle::Triangle(Point a, Point b, Point c){
    vex[0] = a;
    vex[1] = b;
    vex[2] = c;
    color = Color();
    fillColor = Color(0.7,0.7,0.7);
}

Triangle::Triangle(vector<Point>& pts){
    rep(i,0,3) vex[i]=pts[i];
    color = Color();
    fillColor = Color(0.7,0.7,0.7);
}

void Triangle::plot(){
    glColor4d(color.r,color.g,color.b,color.a);
    glBegin(GL_LINE_LOOP);
    rep(i,0,3){
        glVertex3d(vex[i].x,vex[i].y,vex[i].z);
    }
    glEnd();    
}

void Triangle::render(){
    Point nor = normal();

    glBegin(GL_TRIANGLES);

    glColor3f(1.0f, 0.2f, 0.5f);
    glNormal3d(nor.x,nor.y,nor.z);
    glVertex3d(vex[0].x,vex[0].y,vex[0].z);
    glVertex3d(vex[1].x,vex[1].y,vex[1].z);
    glVertex3d(vex[2].x,vex[2].y,vex[2].z);

    glEnd();
}

double Triangle::area(){
    double sa = sqrt(pow(vex[0].x-vex[1].x,2)+pow(vex[0].y-vex[1].y,2)+pow(vex[0].z-vex[1].z,2));
    double sb = sqrt(pow(vex[1].x-vex[2].x,2)+pow(vex[1].y-vex[2].y,2)+pow(vex[1].z-vex[2].z,2));
    double sc = sqrt(pow(vex[2].x-vex[0].x,2)+pow(vex[2].y-vex[0].y,2)+pow(vex[2].z-vex[0].z,2));
    double s = (sa+sb+sc)/2;
    return sqrt(s*(s-sa)*(s-sb)*(s-sc));
}

Point Triangle::normal(){
    Point v1(vex[1].x-vex[0].x, vex[1].y-vex[0].y, vex[1].z-vex[0].z);
    Point v2(vex[2].x-vex[0].x, vex[2].y-vex[0].y, vex[2].z-vex[0].z);

    Point nor;

    nor.x = v1.y*v2.z - v1.z*v2.y;
    nor.y = v1.z*v2.x - v1.x*v2.z;
    nor.z = v1.x*v2.y - v1.y*v2.x;

    nor.normalize();

    return nor;
}
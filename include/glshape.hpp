#ifndef GLSHAPE_H
#define GLSHAPE_H

#include "macros.hpp"
using namespace std;

// Hold color data
class Color {
    public:
        float r, g, b, a;

        Color();
        Color(float red,float green,float blue,float alpha=1.0);
        float* vec();
};

// Hold informations about the primitives
class Primitive {
    public:
        void plot();
};

class Closed : public Primitive {
    public:
        Color color, fillColor;

        void setFillCol(Color color);
        void setFillCol(float red,float green,float blue,float alpha=1.0);
        void setCol(Color color);
        void setCol(float red,float gren,float blue,float alpha=1.0);
        void plot();
};

// Represents a 2D/3D point
class Point : public Primitive {
    public:
        double x, y, z;
        int dimension;

        Point();
        Point(double x, double y);
        Point(double x, double y, double z);
        double* getPos();
        void plot();
        double magnitude();
        void normalize();
};

class Line : public Primitive {
    public:
        Point stPoint, endPoint;
        Color color;

        Line();
        Line(Point& a, Point& b);
        Line(double xa,double ya,double xb,double yb);
        void setCol(Color color);
        void setCol(float red,float gren,float blue,float alpha=1.0);
        void plot();
};

class Circle : public Closed {
    public:
        Point center;
        double radius;

        Circle();
        Circle(double rad, Point& center);
        void plot();
};

class Polygon : public Closed {
    public:
        int n_vt;
        vector<Point> vertices;

        Polygon();
        Polygon(int n);
        Polygon(vector<Point>& pts);
        Polygon(vector<pair<double, double> >& vec);
        void plot();
};

#endif
#ifndef TILING_H
#define TILING_H

#include <vector>
#include "glshape.hpp"
using namespace std;

double _dist(Point &p, Point &q);
double _areaTriangle(Point &a,Point &b,Point &c);
void optimalTiling(vector<Point> &c1, vector<Point> &c2, vector<Point> &optimalPath);

#endif
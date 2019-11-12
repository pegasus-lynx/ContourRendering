#include "contour.hpp"
using namespace std;

void Contour::addControlPt(Point newPt) {
    controlPts.pb(newPt);
}
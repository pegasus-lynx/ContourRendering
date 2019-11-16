#include "model.hpp"
#include "contour.hpp"
#include "glrender.hpp"


using namespace std;

Model::Model() {
    cBox = new ContourBox;
}

void Model::addContour(){
}

void Model::loadContours(char *filename) {
    int x, y, numVertices;
    double contourHt;
    
    ifstream in(filename);

    int numContours;
    in >> numContours;
    
    rep(i, 0, numContours) {
        in >> contourHt;
        in >> numVertices;

        Contour newContour(contourHt, cBox);
        for (int j = 0; j < numVertices; j++) {
            in >> x >> y;
            newContour.addControlPts(Point(x, y, contourHt));
        }

        cBox->heights.pb(contourHt);
        sort(all(cBox->heights));

        cBox->contourSet[contourHt] = newContour;
    }
}

void Model::drawSurface(){
    cBox->drawSurface();
}

void Model::drawContour(){
    cBox->drawContour();
}
#include "model.hpp"
#include "contour.hpp"
#include "glrender.hpp"


using namespace std;

Model::Model() {
    contourBox = new ContourBox;
    rStyle =  SMOOTH;
    meshOn = capsOn = false;
}

void Model::addContour(){
    cout<<"Enter the controls points coordinates (x, y) :\n( For exit : -1 -1)\n";
    int x=0,y=0;
    Contour c(this->contourBox);
    while(true){
        cin>>x>>y;
        if(x==-1 && y==-1) break;
        c.addControlPt(Point(x,y));
    }
    
    ContourPlane cPlane;
    cPlane.addContour(c);

    this->contourBox->addPlane(cPlane);

    currLevel++;
    numContours++;
}

// void Model::deleteContour(){
//     cout<<"Enter the contour level to be deleted : "  ; 
// }

void Model::loadContour(char *filename) {
    int x, y, numVertices;
    delete contourBox;
    contourBox = new ContourBox;
    ifstream in(filename);

    in >> numContours;
    in >> sepPlane;
    rep(i, 0, numContours) {
        in >> numVertices;
        Contour newContour(contourBox);
        for (int j = 0; j < numVertices; j++) {
            in >> x >> y;
            newContour.addControlPt(Point(x, y));
        }

        ContourPlane newPlane;
        contourBox->addPlane(newPlane);
    }
    contourBox->finishContourLoad(numContours, numContours);
}

void Model::listContours(){
    int lev = contourBox->contourSet.size();
    vector<ContourPlane> &v = contourBox->contourSet;
    rep(i,0,lev){
        cout<<"Level : "<<i<<"\n";
        cout<<"Contours : \n";
        rep(j,0,v[i].planeContours.size()){
            cout<<"Contour No : "<<j<<" | ";
            vector<Point> &temp = v[i].planeContours[j].controlPts;
            cout<<"Points : ";
            rep(k,0,temp.size()) cout<<temp[k].x<<", "<<temp[k].y<<" ; ";
        }
        cout<<endl;
    }
}

void Model::draw3D(){
    this->contourBox->draw3D(sepPlane, rStyle, meshOn, capsOn);
}

void Model::refresh(){

}

void Model::eraseAll(){

}
#include "model.hpp"
#include "contour.hpp"
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

void Model::listContours(){

}

void Model::draw3D(){
    this->contourBox->draw3D(1,rStyle,meshOn,capsOn);
}

void Model::refresh(){

}

void Model::eraseAll(){

}
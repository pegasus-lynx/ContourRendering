#include "model.hpp"
#include "contour.hpp"
#include "glrender.hpp"


using namespace std;

Model::Model() {
    cBox = new bContour;
}

void Model::addContour(){
    // cout<<"Enter the controls points coordinates (x, y) :\n( For exit : -1 -1)\n";
    // int x=0,y=0;
    // Contour c(this->contourBox);
    // while(true){
    //     cin>>x>>y;
    //     if(x==-1 && y==-1) break;
    //     c.addControlPt(Point(x,y));
    // }
    
    // ContourPlane cPlane;
    // cPlane.addContour(c);

    // this->contourBox->addPlane(cPlane);

    // currLevel++;
    // numContours++;
}

// void Model::deleteContour(){
//     cout<<"Enter the contour level to be deleted : "  ; 
// }

void Model::loadContours(char *filename) {
    int x, y, numVertices;
    double contourHt;
    // delete contourBox;
    // contourBox = new ContourBox;
    
    ifstream in(filename);

    int numContours;
    in >> numContours;
    
    // cout<< numContours << " ok "<<endl;
    // in >> sepPlane;
    rep(i, 0, numContours) {
        in >> contourHt;
        in >> numVertices;

        cContour newContour(contourHt, cBox);
        // Contour newContour(contourBox);
        for (int j = 0; j < numVertices; j++) {
            in >> x >> y;
            newContour.addControlPts(Point(x, y, contourHt));
        }

        cBox->heights.pb(contourHt);
        sort(all(cBox->heights));

        cBox->contourSet[contourHt] = newContour;
    }

    // cout<<cBox->heights.size()<<endl;
    // rep(i,0,cBox->heights.size()) cerr<<cBox->heights[i]<<" ";


}

void Model::listContours(){
    // int lev = contourBox->contourSet.size();
    // vector<ContourPlane> &v = contourBox->contourSet;
    // rep(i,0,lev){
    //     cout<<"Level : "<<i<<"\n";
    //     cout<<"Contours : \n";
    //     rep(j,0,v[i].planeContours.size()){
    //         cout<<"Contour No : "<<j<<" | ";
    //         vector<Point> &temp = v[i].planeContours[j].controlPts;
    //         cout<<"Points : ";
    //         rep(k,0,temp.size()) cout<<temp[k].x<<", "<<temp[k].y<<" ; ";
    //     }
    //     cout<<endl;
    // }
}

void Model::draw3D(){
    this->cBox->draw3D();
    // this->contourBox->draw3D(sepPlane, rStyle, meshOn, capsOn);
}

void Model::refresh(){

}

void Model::eraseAll(){

}
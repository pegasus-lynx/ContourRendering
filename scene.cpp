#include "scene.hpp"
#include "contour.hpp"
#include "glrender.hpp"
#include "macros.hpp"

using namespace std;


Object::Object(){
    objBox = new ContourBox;
    mode = ABSOLUTE;
    lightingParams = GL_LIGHT0 | GL_LIGHT_MODEL_AMBIENT ;
    obj_id=totalObjects++;
}

Object::Object(ObjectMode mode, int lightingParams){
    objBox = new ContourBox;
    this->mode = mode;
    this->lightingParams = lightingParams;
    obj_id=totalObjects++;
}

void Object::addObjectPos(Point p){
    objPos.pb(p);
}

void Object::addObjectPos(vector<Point>& vec){
    for(auto it: vec) objPos.pb(it);
}

void Object::removeObjectPos(Point p){
    int ind=-1;
    rep(i,0,objPos.size()){
        if((objPos[i].x == p.x) && (objPos[i].y==p.y) && (objPos[i].z==p.z)){
            ind = i;
            break;
        }
    }
    if(ind!=-1){
        objPos.erase(objPos.begin()+ind);
    }
    return;
}

void Object::removeObjectPos(vector<Point>& vec){
    rep(i,0,vec.size()){
        this->removeObjectPos(vec[i]);
    }
}

void Object::renderObject(){

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glShadeModel(GL_SMOOTH);

    objBox->drawSurface();

    glDisable(GL_BLEND);
}
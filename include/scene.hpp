#ifndef SCENE_H
#define SCENE_H

#include "macros.hpp"
#include "glshape.hpp"
#include "glrender.hpp"
#include "contour.hpp"

using namespace std;

class Scene;

class Object {
    public:
        ContourBox* objBox;
        int mode; // Absolute or Relative ( Depending on the mode given by the user)
        int lightingParams;

        static int obj_id;

        vector<Point> objPos;

        Object();
        Object(int mode, int lightingParams);

        void addObjectPos(Point);
        void addObjectPos(vector<Point>&);

        void removeObjectPos(Point);
        void removeObjectPos(vector<Point>&);

        void renderObject();
};

class Scene {
    public:
        map<int, Object> objects;
        int globalLightingParams;

        void addObjectToScene(Object);
        void addObjectAtPos(Object,vector<Point>&);
        void duplicateObject(int object_id, Point);

        void removeObject(int object_id);
        void removeObjectFromPos(int object_id, Point);
        void removeObjectFromPos(int object_id, vector<Point>&);

        void renderScene();
};

#endif

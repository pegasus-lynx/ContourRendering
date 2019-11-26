// ==================================================================
// contains all information relating to scenes and objects in program
// ==================================================================

#ifndef SCENE_H
#define SCENE_H

#include "macros.hpp"
#include "glshape.hpp"
#include "glrender.hpp"
#include "contour.hpp"

using namespace std;

enum ObjectMode { RELATIVE, ABSOLUTE };

class Scene;

class Object {
    public:
        ContourBox* objBox;
        ObjectMode mode; // Absolute or Relative ( Depending on the mode given by the user)
        int lightingParams;
        int obj_id;

        static int totalObjects;

        vector<Point> objPos;

        Object();
        Object(ObjectMode mode, int lightingParams);

        void addObjectPos(Point);
        void addObjectPos(vector<Point>&);

        void removeObjectPos(Point);
        void removeObjectPos(vector<Point>&);

        void renderObject();

        // Add object scalabitlity later
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
        void renderSceneContours();
};

#endif

//
// Created by KK on 16/9/15.
//

#ifndef RTRACER_PARSE_H
#define RTRACER_PARSE_H
#include "Camera.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "animation.h"
#include "Hitable.h"
#include "Scene.h"
#include "Texturetriangles.h"
#include "Meshhitable.h"
#include <cstring>
#include "Vec3.h"
#include "texture.h"
#include <stack>
class parse{
public:
//    Scene* world= new Scene();
//    AnimationList *Animation_list= nullptr;
//    Camera* ccam = nullptr;
//bool viParseArgs(int argc, char *argv[], char **filename);
//
    bool viParseFile(FILE *f );
    void parseViewpoint(FILE *fp);
    void parseLight(FILE *fp);
    void parseBackground(FILE *fp);
    void parseFill(FILE *fp);
    void parseInclude(FILE *fp);
    void parseDetailLevel(FILE *fp);
    void parseKeyFrames(FILE *fp);
    void parseXform(FILE *f);
    void parseAnimParams(FILE *fp);
    void parseA(FILE *f);
    void parseMesh(FILE *fp);
    void parsertbrkt(FILE *fp);


    ~parse(){
//        delete world;
//        delete ccam;
//        delete Animation_list;

    }
    int xs = 0;
};


//Scene *gScene;
//typedef enum {false=0,true=1} bool;


#endif //RTRACER_PARSE_H

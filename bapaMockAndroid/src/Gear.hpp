//
// Created by 新家 亮太 on 2016/08/14.
//

#ifndef BAPAMOCKANDROID_GEAR_H
#define BAPAMOCKANDROID_GEAR_H

#include "ofMain.h"
#include "Item.hpp"

class Gear : public Item {
    public:
        Gear(ofPoint _pos, float _diameter, float _bold, int _polygonalNumber);
        virtual void update(float x, float y, float velocityX, float velocityY);
        virtual void draw();
        virtual ofPoint getLocation();
        void update();
        void update(float velocityX, float velocityY);
        bool hasFinishRotate();
        void reset();
        int getAngle();

    private:
        float getVelocity(float _destination, float _location, float _velocity);
        int getElapsedTime();
        ofPoint pos;
        ofPoint velocity;
        ofPoint dummyLocation;
        float diameter;
        float bold;
        int angle;
        int polygonalNumber;
        float STIFFNESS = 0.05;
        float DAMPING = 0.75;
        int startTime;
        bool canRotate;
        ofColor color;
};

#endif //BAPAMOCKANDROID_GEAR_H

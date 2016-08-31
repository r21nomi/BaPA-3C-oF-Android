//
// Created by 新家 亮太 on 2016/08/30.
//

#ifndef BAPAMOCKANDROID_FLOWER_H
#define BAPAMOCKANDROID_FLOWER_H

#include "ofMain.h"
#include "Item.hpp"

class Flower : public Item {
    public:
        Flower(ofImage *image, ofPoint pos, float width, float height);
        virtual void update(float x, float y, float velocityX, float velocityY);
        virtual void draw();
        virtual ofPoint getLocation();
        virtual void update(float velocityX, float velocityY);

    private:
        float getVelocity(float _destination, float _location, float _velocity);
        int getElapsedTime();
        float STIFFNESS = 0.05;
        float DAMPING = 0.75;

        ofImage *image;
        ofPoint pos;
        float width;
        float height;

        int angle;
        int startTime;
        bool canRotate;
        ofPoint velocity;
        ofPoint dummyLocation;
};

#endif //BAPAMOCKANDROID_FLOWER_H

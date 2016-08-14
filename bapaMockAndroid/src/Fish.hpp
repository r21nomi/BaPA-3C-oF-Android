//
// Created by 新家 亮太 on 2016/07/17.
//

#ifndef BAPAMOCKANDROID_FISH_H
#define BAPAMOCKANDROID_FISH_H

#include "ofMain.h"
#include "Item.hpp"

class Fish : public Item {
    public:
        Fish(ofImage *image, ofPoint pos, float radius);
        virtual void update(float x, float y, float velocityX, float velocityY);
        virtual void draw();
        virtual ofPoint getLocation();

    private:
        ofImage *image;
        ofPoint pos;
        float radius;
        float angle;
        float speedX;
        float speedY;
        float offsetX;
        float offsetY;
        float defSpeed;
        float bounceVelocity;
};

#endif //BAPAMOCKANDROID_FISH_H

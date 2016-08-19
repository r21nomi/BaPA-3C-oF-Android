//
// Created by 新家 亮太 on 2016/08/19.
//

#ifndef BAPAMOCKANDROID_FISH2_H
#define BAPAMOCKANDROID_FISH2_H

#include "ofMain.h"
#include "Item.hpp"

class Fish2 : public Item {
    public:
        Fish2(ofImage *head, ofImage *body, ofImage *tail, ofPoint pos);
        virtual void update(float x, float y, float velocityX, float velocityY);
        virtual void draw();
        virtual ofPoint getLocation();

    private:
        ofImage *head;
        ofImage *body;
        ofImage *tail;
        ofPoint pos;
        float radius;
        float angle;
        float speed;
        float offsetX;
        float offsetY;
        float defSpeed;
        float bounceVelocity;
        float headWidth, headHeight;
        float bodyWidth, bodyHeight;
        float tailWidth, tailHeight;
        float headAngle, tailAngle;
        float dirX, dirY;
        float originDirX, originDirY;

        float targetX, targetY;
        float currentTheta;
};

#endif //BAPAMOCKANDROID_FISH2_H

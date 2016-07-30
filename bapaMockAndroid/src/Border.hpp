//
// Created by 新家 亮太 on 2016/07/28.
//

#ifndef BAPAMOCKANDROID_BORDER_H
#define BAPAMOCKANDROID_BORDER_H

#include "ofMain.h"
#include "Item.hpp"

class Border : public Item {
    public:
        enum Type {
            VERTICAL,
            HORIZONTAL
        };
        Border(ofPoint pos, float width, float height, Type type);
        virtual void update(float x, float y, float velocityX, float velocityY);
        virtual void draw();
        virtual ofPoint getLocation();

    private:
        ofPoint pos;
        ofColor color;
        float width;
        float height;
        Type type;
        float angle;
        float speedX;
        float speedY;
        float offsetX;
        float offsetY;
        float defSpeed;
        float bounceVelocity;
};

#endif //BAPAMOCKANDROID_BORDER_H

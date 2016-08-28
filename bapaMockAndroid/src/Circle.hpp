//
// Created by 新家 亮太 on 2016/08/28.
//

#ifndef BAPAMOCKANDROID_CIRCLE_H
#define BAPAMOCKANDROID_CIRCLE_H

#include "ofMain.h"
#include "Item.hpp"

class Circle : public Item {
    public:
        Circle(ofPoint pos, float width, float height, float speed, float limitSize, ofColor color);
        virtual void update(float x, float y, float velocityX, float velocityY);
        virtual void draw();
        virtual ofPoint getLocation();
        bool isOverRange();

    private:
        ofPoint pos;
        ofColor color;
        float width;
        float height;
        float limitSize;
        float speed;
};
#endif //BAPAMOCKANDROID_CIRCLE_H

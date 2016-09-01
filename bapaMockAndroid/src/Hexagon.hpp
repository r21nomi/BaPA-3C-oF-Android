//
// Created by 新家 亮太 on 2016/09/02.
//

#ifndef BAPAMOCKANDROID_HEXAGON_H
#define BAPAMOCKANDROID_HEXAGON_H

#include "ofMain.h"
#include "Item.hpp"

class Hexagon : public Item {
    public:
        Hexagon(ofPoint _pos, float radius, ofColor color);
        virtual void update(float x, float y, float velocityX, float velocityY);
        virtual void draw();
        virtual ofPoint getLocation();

    private:
        ofPoint pos;
        ofPoint velocity;
        ofPoint dummyLocation;
        ofColor color;
        float radius;
};

#endif //BAPAMOCKANDROID_HEXAGON_H

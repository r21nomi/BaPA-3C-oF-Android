//
// Created by 新家 亮太 on 2016/09/02.
//

#ifndef BAPAMOCKANDROID_HEXAGON_H
#define BAPAMOCKANDROID_HEXAGON_H

#include "ofMain.h"
#include "Item.hpp"

class Hexagon : public Item {
    public:
        Hexagon(ofPoint pos, float radius, vector<ofColor> colors, int index, float velocity);
        virtual void update(float x, float y, float velocityX, float velocityY);
        virtual void draw();
        virtual ofPoint getLocation();

    private:
        int getNextIndex();
        ofPoint pos;
        ofPoint dummyLocation;
        vector<ofColor> colors;
        int index;
        float radius, defaultRadius;
        float velocity;
};

#endif //BAPAMOCKANDROID_HEXAGON_H

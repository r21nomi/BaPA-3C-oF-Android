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

    private:
        ofImage *image;
        ofPoint pos;
        float width;
        float height;
};

#endif //BAPAMOCKANDROID_FLOWER_H

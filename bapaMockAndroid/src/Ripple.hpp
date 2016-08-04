//
// Created by 新家 亮太 on 2016/08/04.
//

#ifndef BAPAMOCKANDROID_RIPPLE_H
#define BAPAMOCKANDROID_RIPPLE_H

#include "ofMain.h"
#include "Item.hpp"

class Ripple : public Item {
    public:
        Ripple(ofPoint pos, float speed, float maxRadius, int delay, ofColor color);
        virtual void update(float x, float y, float velocityX, float velocityY);
        virtual void draw();
        virtual ofPoint getLocation();
        bool shouldDelete();

    private:
        ofPoint pos;
        float radius;
        float speed;
        float maxRadius;
        ofColor color;
        int alpha;
        int defaultAlpha;
        int startTime;
        int delay;
};

#endif //BAPAMOCKANDROID_RIPPLE_H

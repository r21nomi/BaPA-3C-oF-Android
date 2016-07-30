//
// Created by 新家 亮太 on 2016/07/28.
//

#include "Border.hpp"

Border::Border(ofPoint _pos, float _width, float _height, Type _type) {
    pos = _pos;
    width = _width;
    height = _height;
    type = _type;
    offsetX = ofRandom(10, 30);
    offsetY = ofRandom(10, 30);
    speedX = speedY = defSpeed = 0;
    bounceVelocity = ofRandom(0.05, 0.1);
    color = ofColor(ofRandom(255), ofRandom(255), ofRandom(255));
    angle = (int)ofRandom(2) % 2 == 0 ? 0 : 90;
}

void Border::update(float x, float y, float velocityX, float velocityY) {
    switch (type) {
        case VERTICAL:
            pos.y += 5 * velocityY;

            if (pos.y + height < 0) {
                pos.y = ofGetHeight();
            } else if (pos.y > ofGetHeight()) {
                pos.y = -height;
            }
            break;

        case HORIZONTAL:
            pos.x += 5 * velocityX;

            if (pos.x + width < 0) {
                pos.x = ofGetWidth();
            } else if (pos.x > ofGetWidth()) {
                pos.x = -width;
            }
            break;
    }
}

void Border::draw() {
    ofSetColor(color);
    ofDrawRectangle(pos.x, pos.y, width, height);
}

ofPoint Border::getLocation() {
    return pos;
}

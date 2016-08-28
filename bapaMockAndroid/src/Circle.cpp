//
// Created by 新家 亮太 on 2016/08/28.
//

#include "Circle.hpp"

Circle::Circle(ofPoint _pos, float _width, float _height, float _speed, float _limitSize, ofColor _color) {
    pos = _pos;
    width = _width;
    height = _height;
    limitSize = _limitSize;
    speed = _speed;
    color = _color;
}

void Circle::update(float x, float y, float velocityX, float velocityY) {
    if (height > limitSize) {
        width = 0;
        height = 0;
    }
    float offset = pow((abs(velocityX) + abs(velocityY)) / 2 + 1, 3);
    width += speed * offset;
    height += speed * offset;
}

void Circle::draw() {
    ofSetColor(color);
    ofPushMatrix();
    ofTranslate(pos.x, pos.y);
    ofDrawEllipse(0, 0, width, height);
    ofPopMatrix();
}

ofPoint Circle::getLocation() {
    return pos;
}

bool Circle::isOverRange() {
    return height > limitSize;
}

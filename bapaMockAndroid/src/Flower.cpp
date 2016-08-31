//
// Created by 新家 亮太 on 2016/08/30.
//

#include "Flower.hpp"

Flower::Flower(ofImage *_image, ofPoint _pos, float _width, float _height) {
    image = _image;
    pos = _pos;
    width = _width;
    height = _height;
    image->setAnchorPercent(0.5, 0.5);
    angle = 0;
    startTime = 0;
    canRotate = true;
}

void Flower::update(float x, float y, float velocityX, float velocityY) {
    if (canRotate) {
        startTime = ofGetElapsedTimeMillis();
        velocity.x = getVelocity(360, angle, velocity.x);
        angle += velocity.x;

        if (angle > 350) {
            angle = 0;
            canRotate = false;
        }
    }
    if (getElapsedTime() > 3000) {
        canRotate = true;
    }
}

void Flower::update(float velocityX, float velocityY) {
    int x = ofMap(velocityX, -1, 1, 0, ofGetWidth());
    int y = ofMap(velocityY, -1, 1, 0, ofGetHeight());

    velocity.x = getVelocity(x, dummyLocation.x, velocity.x);
    dummyLocation.x += velocity.x;

    velocity.y = getVelocity(y, dummyLocation.y, velocity.y);
    dummyLocation.y += velocity.y;

    angle = atan2(dummyLocation.y - ofGetHeight() / 2, dummyLocation.x - ofGetWidth() / 2) * 180.0 / PI;
}

void Flower::draw() {
    ofPushMatrix();
    ofTranslate(pos.x, pos.y);
    ofRotate(angle);

    image->draw(0, 0, width, height);

    ofPopMatrix();
}

ofPoint Flower::getLocation() {
    return pos;
}

float Flower::getVelocity(float _destination, float _location, float _velocity) {
    float force = STIFFNESS * (_destination - _location);
    return DAMPING * (_velocity + force);
}

int Flower::getElapsedTime() {
    return ofGetElapsedTimeMillis() - startTime;
}

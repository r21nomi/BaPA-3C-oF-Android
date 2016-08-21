//
// Created by 新家 亮太 on 2016/07/17.
//

#include "Fish.hpp"

Fish::Fish(ofImage *_image, ofPoint _pos, float _radius) {
    image = _image;
    pos = _pos;
    radius = _radius;
    offsetX = ofRandom(10, 30);
    offsetY = ofRandom(10, 30);
    speedX = speedY = defSpeed = 0;
    bounceVelocity = ofRandom(0.05, 0.1);
}

void Fish::update(float x, float y, float velocityX, float velocityY) {
    float targetX = ofGetWidth() / 2 + ofGetWidth() / 2 * velocityX;
    float targetY = ofGetHeight() / 2 + ofGetHeight() / 2 * velocityY;

    // X
    float radX = ofDegToRad(ofMap(velocityX, -1, 1, 180, 0));
    float radiusX = (offsetX * sin(radX));
    pos.x += (targetX - pos.x) * bounceVelocity * 0.7 + radiusX * cos(ofGetFrameNum() * bounceVelocity * 0.5);

    // Y
    float radY = ofDegToRad(ofMap(velocityY, -1, 1, 180, 0));
    float radiusY = (offsetY * sin(radY));
    pos.y += (targetY - pos.y) * bounceVelocity * 0.7 + radiusY * sin(ofGetFrameNum() * bounceVelocity * 0.5);

    // Edge
    if (pos.x < radius / 2) {
        pos.x = radius / 2;
        speedX = defSpeed;

    } else if (pos.x > ofGetWidth() - radius / 2) {
        pos.x = ofGetWidth() - radius / 2;
        speedX = defSpeed;
    }
    if (pos.y < radius / 2) {
        pos.y = radius / 2;
        speedY = defSpeed;

    } else if (pos.y > ofGetHeight() - radius / 2) {
        pos.y = ofGetHeight() - radius / 2;
        speedY = defSpeed;
    }

    angle = atan2(pos.y - ofGetHeight() / 2, pos.x - ofGetWidth() / 2) * 180.0 / PI + 90;
}

void Fish::draw() {
    ofPushMatrix();

    ofTranslate(pos.x, pos.y);
    ofRotate(angle);

    image->draw(0, 0);

    ofPopMatrix();
}

ofPoint Fish::getLocation() {
    return pos;
}

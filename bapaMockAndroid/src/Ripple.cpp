//
// Created by 新家 亮太 on 2016/08/04.
//

#include "Ripple.hpp"

Ripple::Ripple(ofPoint _pos, float _speed, float _maxRadius, int _delay, ofColor _color) {
    pos = _pos;
    speed = _speed;
    maxRadius = _maxRadius;
    color = _color;
    radius = 0;
    alpha = defaultAlpha = 200;
    delay = _delay;
    startTime = ofGetElapsedTimeMillis();
}

void Ripple::update(float _x, float _y, float _velocityX, float _velocityY) {
    if (ofGetElapsedTimeMillis() - startTime < delay) {
        return;
    }
    radius += speed;
    alpha -= defaultAlpha / (maxRadius / speed);

    if (shouldDelete()) {
        pos = ofPoint(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
        radius = 0;
        alpha = defaultAlpha;
    }
}

void Ripple::draw() {
    ofSetColor(color, alpha);
    ofPushMatrix();

    ofTranslate(pos.x, pos.y);
    ofDrawEllipse(0, 0, radius, radius);

    ofPopMatrix();
}

ofPoint Ripple::getLocation() {
    return pos;
}

bool Ripple::shouldDelete() {
    return radius > maxRadius;
}

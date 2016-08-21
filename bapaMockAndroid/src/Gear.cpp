//
// Created by 新家 亮太 on 2016/08/14.
//

#include "Gear.hpp"

Gear::Gear(ofPoint _pos, float _diameter, float _bold, int _polygonalNumber) {
    pos = _pos;
    diameter = _diameter;
    bold = _bold;
    polygonalNumber = _polygonalNumber;
    angle = 0;
    startTime = 0;
    canRotate = true;
    color = ofColor(ofRandom(255), ofRandom(255), ofRandom(255));
}

void Gear::update(float x, float y, float velocityX, float velocityY) {
    // no-op
}

void Gear::update() {
    canRotate = true;

    velocity.x = getVelocity(360, angle, velocity.x);
    angle += velocity.x;

    if (angle > 350) {
        if (startTime == 0) {
            startTime = ofGetElapsedTimeMillis();
        }
        if (getElapsedTime() > 800) {
            angle = 0;
            startTime = 0;
            canRotate = false;
        }
    }
}

void Gear::update(float velocityX, float velocityY) {
    int x = ofMap(velocityX, -1, 1, 0, ofGetWidth());
    int y = ofMap(velocityY, -1, 1, 0, ofGetHeight());

    velocity.x = getVelocity(x, dummyLocation.x, velocity.x);
    dummyLocation.x += velocity.x;

    velocity.y = getVelocity(y, dummyLocation.y, velocity.y);
    dummyLocation.y += velocity.y;

    angle = atan2(dummyLocation.y - ofGetHeight() / 2, dummyLocation.x - ofGetWidth() / 2) * 180.0 / PI;
}

void Gear::draw() {
    ofSetColor(color);
    ofPushMatrix();

    ofTranslate(pos.x, pos.y);
    ofRotate(angle);

    for (int i = 0; i < polygonalNumber; i++) {
        ofDrawRectangle(-diameter / 2, -bold / 2, diameter, bold);
        ofRotate(180 / polygonalNumber);
    }

    ofPopMatrix();
}

ofPoint Gear::getLocation() {
    return pos;
}

bool Gear::hasFinishRotate() {
    return !canRotate;
}

void Gear::reset() {
    angle = 0;
    startTime = 0;
    canRotate = true;
    velocity.x = 0;
}

int Gear::getAngle() {
    return angle;
}

float Gear::getVelocity(float _destination, float _location, float _velocity) {
  float force = STIFFNESS * (_destination - _location);
  return DAMPING * (_velocity + force);
}

int Gear::getElapsedTime() {
    return ofGetElapsedTimeMillis() - startTime;
}

//
//  Particle.cpp
//  bapaMock3
//
//  Created by 新家 亮太 on 2016/06/24.
//
//

#include "Particle.hpp"

Particle::Particle(ofImage *_image, ofPoint _pos, float _radius) {
    image = _image;
    pos = _pos;
    radius = defaultRadius = _radius;
    bounceVelocity = ofRandom(0.05, 0.1);
    offsetX = ofRandom(10, 30);
    offsetY = ofRandom(10, 30);
    speedX = speedY = defSpeed = 0;
    acceleration = 0.1;
    dirX = getDir();
    dirY = getDir();
}

void Particle::update(float x, float y, float velocityX, float velocityY) {
    angle = atan2(y - ofGetHeight() / 2, x - ofGetWidth() / 2) * 180.0 / PI;

    radius = defaultRadius * ofMap(sin(ofGetFrameNum() * bounceVelocity), -1, 1, 0.5, 1.2);

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
}

void Particle::draw() {
    ofSetColor(255, 255, 0, 60);
    ofPushMatrix();

    ofTranslate(pos.x, pos.y);
    ofRotate(angle);

    ofNoFill();
    ofDrawEllipse(0, 0, radius * 1.3, radius * 1.3);
    ofFill();
    ofDrawEllipse(0, 0, radius, radius);

    float r = radius * 0.8;
    ofLine(-r, 0, r, 0);
    ofLine(0, -r, 0, r);

    ofSetColor(236,52,131);
    ofDrawEllipse(0, 0, radius * 0.1, radius * 0.1);

    ofPopMatrix();
}

ofPoint Particle::getLocation() {
    return pos;
}

float Particle::getDir() {
    return ((int)ofRandom(1, 3)) % 2 == 0 ? 1 : -1;
}
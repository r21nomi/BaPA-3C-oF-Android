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
    speedX = speedY = defSpeed = 0;
    acceleration = 1.3;
    dirX = getDir();
    dirY = getDir();
}

void Particle::update(float x, float y, float velocityX, float velocityY) {
    angle = atan2(y - ofGetHeight() / 2, x - ofGetWidth() / 2) * 180.0 / PI;

    radius = defaultRadius * ofMap(sin(ofGetFrameNum() * bounceVelocity), -1, 1, 0.5, 1.2);

    //speedX += velocityX;
    //pos.x += speedX * acceleration;
    //speedY += -velocityY;
    //pos.y += speedY * acceleration;

    //if (pos.x < radius / 2) {
    //    pos.x = radius / 2;
    //    speedX = defSpeed;

    //} else if (pos.x > ofGetWidth() - radius / 2) {
    //    pos.x = ofGetWidth() - radius / 2;
    //    speedX = defSpeed;
    //}
    //if (pos.y < radius / 2) {
    //    pos.y = radius / 2;
    //    speedY = defSpeed;

    //} else if (pos.y > ofGetHeight() - radius / 2) {
    //    pos.y = ofGetHeight() - radius / 2;
    //    speedY = defSpeed;
    //}

    pos.x += dirX * 1;
    pos.y += dirY * 1;

    if (pos.x < radius / 2 || pos.x > ofGetWidth() - radius / 2) {
        dirX *= -1;
    }
    if (pos.y < radius / 2 || pos.y > ofGetHeight() - radius / 2) {
        dirY *= -1;
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
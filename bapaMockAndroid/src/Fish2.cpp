//
// Created by 新家 亮太 on 2016/08/19.
//

#include "Fish2.hpp"

Fish2::Fish2(ofImage *_head, ofImage *_body, ofImage *_tail, ofPoint _pos) {
    head = _head;
    body = _body;
    tail = _tail;
    pos = _pos;
    offsetX = ofRandom(10, 30);
    offsetY = ofRandom(10, 30);
    speed = defSpeed = ofRandom(3, 5);
    bounceVelocity = ofRandom(0.05, 0.1);
    headWidth = _head->getWidth();
    headHeight = _head->getHeight();
    bodyWidth = _body->getWidth();
    bodyHeight = _body->getHeight();
    tailWidth = _tail->getWidth();
    tailHeight = _tail->getHeight();
    head->setAnchorPercent(0, 0.5);
    body->setAnchorPercent(0.5, 0.5);
    tail->setAnchorPercent(1, 0.5);
    dirX = originDirX = (int)ofRandom(0, 2) % 2 == 0 ? 1 : -1;
    dirY = originDirY = (int)ofRandom(0, 2) % 2 == 0 ? 1 : -1;
}

void Fish2::update(float x, float y, float velocityX, float velocityY) {
    targetX = ofGetWidth() / 2 + ofGetWidth() / 2 * velocityX;
    targetY = ofGetHeight() / 2 + ofGetHeight() / 2 * velocityY;

    float speedX;
    float speedY;

    float velocityOffset = 0.2;

    if (velocityX < -velocityOffset) {
        dirX = -1;
        speedX = defSpeed * ABS(velocityX);
    } else if (velocityX > velocityOffset) {
        dirX = 1;
        speedX = defSpeed * ABS(velocityX);
    } else {
        dirX = originDirX;
        speedX = defSpeed;
    }
    if (velocityY < -velocityOffset) {
        dirY = -1;
        speedY = defSpeed * ABS(velocityY);
    } else if (velocityY > velocityOffset) {
        dirY = 1;
        speedY = defSpeed * ABS(velocityY);
    } else {
        dirY = originDirY;
        speedY = defSpeed;
    }

    // Edge
    int w = -headWidth;
    if (pos.x < w) {
        dirX = originDirX = 1;
    } else if (pos.x > ofGetWidth() - w) {
        dirX = originDirX = -1;
    }
    if (pos.y < w) {
        dirY = originDirY = 1;
    } else if (pos.y > ofGetHeight() - w) {
        dirY = originDirY = -1;
    }

    // Position
    pos.x += speedX * dirX;
    pos.y += speedY * dirY;

    currentTheta = ofGetElapsedTimeMillis() * speed * 0.001;

    pos.x += cos(currentTheta) * speedX * dirX;
    pos.y += cos(currentTheta) * speedY * dirY * -1;

    // Angle
    angle = atan2(
        (pos.y + (speedY * dirY) + (cos(currentTheta) * speedY * dirY * -1)) - pos.y,
        (pos.x + (speedX * dirX) + (cos(currentTheta) * speedX * dirX)) - pos.x
    ) * 180.0 / PI;

    headAngle = cos(currentTheta - speed) * speed * 5;
    tailAngle = sin(currentTheta - speed) * speed * 4;
}

void Fish2::draw() {
    ofPushMatrix();

    ofTranslate(pos.x, pos.y);
    ofRotate(angle);

    // Head
    ofPushMatrix();
    ofTranslate((bodyWidth * 0.4) / 2, 0);
    ofRotate(headAngle);
    head->draw(0, 0, headWidth * 0.8, headHeight * 0.8);
    ofPopMatrix();

    // Tail
    ofPushMatrix();
    ofTranslate(-(bodyWidth * 0.3) / 2, 0);
    ofRotate(tailAngle);
    tail->draw(0, 0, tailWidth * 0.8, tailHeight * 0.8);
    ofPopMatrix();

    // Body
    ofPushMatrix();
    body->draw(0, 0, bodyWidth * 0.8, bodyHeight * 0.8);
    ofPopMatrix();

    ofPopMatrix();
}

ofPoint Fish2::getLocation() {
    return pos;
}

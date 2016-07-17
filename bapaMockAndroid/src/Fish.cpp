//
// Created by 新家 亮太 on 2016/07/17.
//

#include "Fish.hpp"

Fish::Fish(ofImage *_image, ofPoint _pos, float _radius) {
    image = _image;
    pos = _pos;
    radius = _radius;
}

void Fish::update(float x, float y, float velocityX, float velocityY) {
}

void Fish::draw() {
    ofSetColor(255, 255, 0, 60);
    ofPushMatrix();

    ofTranslate(pos.x, pos.y);

    image->draw(pos.x, pos.y);

    //ofNoFill();
    //ofDrawEllipse(0, 0, radius * 1.3, radius * 1.3);
    //ofFill();
    //ofDrawEllipse(0, 0, radius, radius);

    //float r = radius * 0.8;
    //ofLine(-r, 0, r, 0);
    //ofLine(0, -r, 0, r);

    //ofSetColor(236,52,131);
    //ofDrawEllipse(0, 0, radius * 0.1, radius * 0.1);

    ofPopMatrix();
}

ofPoint Fish::getLocation() {
    return pos;
}
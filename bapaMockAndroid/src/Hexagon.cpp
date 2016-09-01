//
// Created by 新家 亮太 on 2016/09/02.
//

#include "Hexagon.hpp"

Hexagon::Hexagon(ofPoint _pos, float _radius, ofColor _color) {
    pos = _pos;
    radius = _radius;
    color = _color;
}

void Hexagon::update(float x, float y, float velocityX, float velocityY) {

}

void Hexagon::draw() {
    ofSetColor(color);
    ofPushMatrix();
    ofTranslate(pos.x, pos.y);
    ofRotate(30);
    ofSetCircleResolution(6);
    ofCircle(0, 0, radius);
    ofPopMatrix();
}

ofPoint Hexagon::getLocation() {
    return pos;
}

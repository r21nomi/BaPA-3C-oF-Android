//
// Created by 新家 亮太 on 2016/09/02.
//

#include "Hexagon.hpp"

Hexagon::Hexagon(ofPoint _pos, float _radius, vector<ofColor> _colors, int _index, float _velocity) {
    pos = _pos;
    radius = defaultRadius = _radius;
    colors = _colors;
    index = _index;
    velocity = _velocity;
}

void Hexagon::update(float x, float y, float velocityX, float velocityY) {
    radius -= velocity;

    if (radius <= 0) {
        radius = defaultRadius;
        index++;
        if (index > colors.size() - 1) {
            index = 0;
        }
    }
}

void Hexagon::draw() {
    ofPushMatrix();
    ofTranslate(pos.x, pos.y);
    ofRotate(30);

    ofSetColor(colors[index]);
    ofSetCircleResolution(6);
    ofCircle(0, 0, defaultRadius);

    ofSetColor(colors[getNextIndex()]);
    ofSetCircleResolution(6);
    ofCircle(0, 0, radius);

    ofPopMatrix();
}

ofPoint Hexagon::getLocation() {
    return pos;
}

int Hexagon::getNextIndex() {
    int _index = index + 1;
    if (_index > colors.size() - 1) {
        _index = 0;
    }
    return _index;
}

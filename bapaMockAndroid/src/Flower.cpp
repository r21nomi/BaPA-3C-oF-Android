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
}

void Flower::update(float x, float y, float velocityX, float velocityY) {
}

void Flower::draw() {
    ofPushMatrix();
    ofTranslate(pos.x, pos.y);

    image->draw(0, 0, width, height);

    ofPopMatrix();
}

ofPoint Flower::getLocation() {
    return pos;
}

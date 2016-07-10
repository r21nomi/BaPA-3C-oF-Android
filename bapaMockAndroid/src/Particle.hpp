//
//  Particle.hpp
//  bapaMock3
//
//  Created by 新家 亮太 on 2016/06/24.
//
//

#ifndef Particle_hpp
#define Particle_hpp

#include "ofMain.h"

class Particle {
public:
    Particle(ofImage *image, ofPoint pos, float radius);
    void update(float x, float y, float velocityX, float velocityY);
    void draw();
    ofPoint getLocation();
private:
    float getDir();
    ofPoint pos;
    float defaultRadius;
    float radius;
    float angle;
    float bounceVelocity;
    float dirX;
    float dirY;
    float speedX;
    float speedY;
    float defSpeed;
    float acceleration;
    ofImage *image;
};

#endif /* Particle_hpp */

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);

    font.load("verdana.ttf", 24);

    ofxAccelerometer.setup();

    ofRegisterGPSEvent(this);
    ofxAndroidGPS::startGPS();

    img1.load("images/img5_1.png");
    img1.setAnchorPercent(0.5, 0.5);

    stiffness = 0.1;
    damping = 0.85;
    createItems();
}

//--------------------------------------------------------------
void ofApp::update(){
    accel = ofxAccelerometer.getForce();
    normAccel = accel.getNormalized();

    velocity.x = getVelocity(destination.x, dummyLocation.x, velocity.x);
    dummyLocation.x += velocity.x;

    velocity.y = getVelocity(destination.y, dummyLocation.y, velocity.y);
    dummyLocation.y += velocity.y;

    for (Particle *particle : particles) {
        // Use Z axis to make the origin the state of standing.
        particle->update(dummyLocation.x, dummyLocation.y, normAccel.x, normAccel.z);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    for (Particle *particle : particles) {
        particle->draw();
    }

    ofSetColor(255, 255, 255);
    font.drawString("x : " + ofToString(normAccel.x), 10, 30);
    font.drawString("y : " + ofToString(normAccel.y), 10, 60);
    font.drawString("z : " + ofToString(normAccel.z), 10, 90);
    font.drawString("latitude : " + ofToString(latitude), 10, 120);
    font.drawString("longitude : " + ofToString(longitude), 10, 150);
    font.drawString("speed : " + ofToString(speed), 10, 180);
}

//--------------------------------------------------------------
void ofApp::keyPressed  (int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::touchDown(int x, int y, int id){

}

//--------------------------------------------------------------
void ofApp::touchMoved(int x, int y, int id){
    destination.x = x;
    destination.y = y;
}

//--------------------------------------------------------------
void ofApp::touchUp(int x, int y, int id){

}

//--------------------------------------------------------------
void ofApp::touchDoubleTap(int x, int y, int id){

}

//--------------------------------------------------------------
void ofApp::touchCancelled(int x, int y, int id){

}

//--------------------------------------------------------------
void ofApp::swipe(ofxAndroidSwipeDir swipeDir, int id){

}

//--------------------------------------------------------------
void ofApp::pause(){

}

//--------------------------------------------------------------
void ofApp::stop(){

}

//--------------------------------------------------------------
void ofApp::resume(){

}

//--------------------------------------------------------------
void ofApp::reloadTextures(){

}

//--------------------------------------------------------------
bool ofApp::backPressed(){
    return false;
}

//--------------------------------------------------------------
void ofApp::okPressed(){

}

//--------------------------------------------------------------
void ofApp::cancelPressed(){

}

void ofApp::locationChanged(ofxLocation& location) {
    ofLog(OF_LOG_NOTICE, "location changed, latitude : " + ofToString(location.latitude));
    ofLog(OF_LOG_NOTICE, "location changed, longitude : " + ofToString(location.longitude));
    ofLog(OF_LOG_NOTICE, "location changed, speed : " + ofToString(location.speed));

    latitude = location.latitude;
    longitude = location.longitude;
    speed = location.speed;
}

void ofApp::createItems() {
    particles.clear();

    float width = 100;
    float margin = 0;
    for (int i = 0, wLen = ofGetWidth() / (width + margin); i < wLen; i++) {
        for (int j = 0, hLen = ofGetHeight() / (width + margin); j < hLen; j++) {
            Particle *particle = new Particle(&img1, ofPoint(i * (width + margin), j * (width + margin)), width);
            float dist = ofDist(particle->getLocation().x, particle->getLocation().y, ofGetWidth() / 2, ofGetHeight() / 2);

            if (dist < ofGetHeight() / 2) {
                particles.push_back(particle);
            }
        }
    }
}

float ofApp::getVelocity(float destination, float location, float velocity) {
    float force = stiffness * (destination - location);
    return damping * (velocity + force);
}
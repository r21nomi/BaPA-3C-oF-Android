#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);

    ofLog(OF_LOG_NOTICE, "setup -----------------------------------------");

    font.load("verdana.ttf", 24);

    ofxAccelerometer.setup();

    ofRegisterGPSEvent(this);
    ofxAndroidGPS::startGPS();

    setGraphicId();

    imageRefs.push_back("images/fish_100_0.png");
    imageRefs.push_back("images/fish_100_1.png");
    imageRefs.push_back("images/fish_100_2.png");
    imageRefs.push_back("images/fish_100_3.png");
    imageRefs.push_back("images/fish_100_4.png");
    img.load(imageRefs[graphicId]);
    img.setAnchorPercent(0.5, 0.5);

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

    for (Item *particle : particles) {
        // Use Z axis to make the origin the state of standing.
        particle->update(dummyLocation.x, dummyLocation.y, normAccel.x * 1.5, normAccel.z * 1.5);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    for (Item *particle : particles) {
        particle->draw();
    }

    ofSetColor(255, 255, 255);
    font.drawString("x : " + ofToString(normAccel.x), 10, 30);
    font.drawString("y : " + ofToString(normAccel.y), 10, 60);
    font.drawString("z : " + ofToString(normAccel.z), 10, 90);
    font.drawString("latitude : " + ofToString(latitude), 10, 120);
    font.drawString("longitude : " + ofToString(longitude), 10, 150);
    font.drawString("speed : " + ofToString(speed), 10, 180);
    font.drawString("getAzimuth : " + ofToString(getAzimuth()), 10, 210);
}

//--------------------------------------------------------------
void ofApp::keyPressed  (int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    ofLog(OF_LOG_NOTICE, "windowResized");
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
    ofLog(OF_LOG_NOTICE, "pause");
}

//--------------------------------------------------------------
void ofApp::stop(){
    ofLog(OF_LOG_NOTICE, "stop");
}

//--------------------------------------------------------------
void ofApp::resume(){
    ofLog(OF_LOG_NOTICE, "resume");
}

//--------------------------------------------------------------
void ofApp::reloadTextures(){
    ofLog(OF_LOG_NOTICE, "reloadTextures");
    setGraphicId();
    img.clear();
    img.load(imageRefs[graphicId]);
    createItems();
}

//--------------------------------------------------------------
bool ofApp::backPressed(){
    ofLog(OF_LOG_NOTICE, "backPressed");
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
            Item *particle;

            if (graphicId == 1) {
                particle = new Particle(&img, ofPoint(i * (width + margin), j * (width + margin)), width);
            } else {
                particle = new Fish(&img, ofPoint(i * (width + margin), j * (width + margin)), width);
            }

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

void ofApp::setGraphicId() {
    graphicId = getId();
    ofLog(OF_LOG_NOTICE, "ID : " + ofToString(graphicId));
}

/**
 * Get ID using getId method which OFActivity has.
 */
int ofApp::getId() {
    // Get env.
    JNIEnv *env = ofGetJNIEnv();
    if (!env) {
        ofLogError() << "Couldn't get environment using GetEnv()." << endl;
        return -1;
    }

    // Find reference for OFActivity.
    jclass localClass = env->FindClass("cc/openframeworks/bapaMockAndroid/OFActivity");
    jclass javaClass = (jclass) env->NewGlobalRef(localClass);
    if(!javaClass){
        ofLogError() << "Couldn't get java class for OFActivity." << endl;
        return -1;
    }
    jobject javaObject = ofGetOFActivityObject();
    javaObject = (jobject) env->NewGlobalRef(javaObject);
    if (!javaObject) {
        ofLogError() << "javaObject not found." << endl;
        return -1;
    }

    // Find getId method from OFActivity.
    jmethodID javaGetIdMethod = env->GetMethodID(javaClass,"getId","()I");
    if(!javaGetIdMethod){
        ofLogError() << "Couldn't get java getId from OFActivity." << endl;
        return -1;
    }

    return env->CallIntMethod(javaObject, javaGetIdMethod);
}

float ofApp::getAzimuth() {
    // Get env.
    JNIEnv *env = ofGetJNIEnv();
    if (!env) {
        ofLogError() << "Couldn't get environment using GetEnv()." << endl;
        return -1;
    }

    // Find reference for OFActivity.
    jclass localClass = env->FindClass("cc/openframeworks/bapaMockAndroid/OFActivity");
    jclass javaClass = (jclass) env->NewGlobalRef(localClass);
    if(!javaClass){
        ofLogError() << "Couldn't get java class for OFActivity." << endl;
        return -1;
    }
    jobject javaObject = ofGetOFActivityObject();
    javaObject = (jobject) env->NewGlobalRef(javaObject);
    if (!javaObject) {
        ofLogError() << "javaObject not found." << endl;
        return -1;
    }

    // Find getId method from OFActivity.
    jmethodID javaGetIdMethod = env->GetMethodID(javaClass,"getAzimuth","()F");
    if(!javaGetIdMethod){
        ofLogError() << "Couldn't get java getId from OFActivity." << endl;
        return -1;
    }

    return env->CallFloatMethod(javaObject, javaGetIdMethod);
}
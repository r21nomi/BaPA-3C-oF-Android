#include "ofApp.h"
#include <algorithm>

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
    imageRefs.push_back("images/cone_80_1.png");
    imageRefs.push_back("images/eye_57_1.png");
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
        float accelX = normAccel.x * 2.5;
        float accelY = normAccel.z * 2.5 * -1;
        if (accelX > 1) {
            accelX = 1;
        } else if (accelX < -1) {
            accelX = -1;
        }
        if (accelY > 1) {
            accelY = 1;
        } else if (accelY < -1) {
            accelY = -1;
        }
        particle->update(dummyLocation.x, dummyLocation.y, accelX, accelY);
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
    reset();
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
    if (graphicId == 2) {
        createBorderItems();
    } else {
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
}

void ofApp::createBorderItems() {
    particles.clear();

    int currentXLen = 0;
    int currentYLen = 0;
    // Horizontal
    for (int i = 0, wLen = ofGetWidth(); currentXLen < wLen; i++) {
        int bold = ofRandom(10, 80);
        Item *particle = new Border(ofPoint(currentXLen, 0), bold, ofGetHeight(), ofRandom(5, 8), Border::HORIZONTAL);
        particles.push_back(particle);
        currentXLen += bold;
    }
    // Vertical
    for (int j = 0, hLen = ofGetHeight(); currentYLen < hLen; j++) {
        int bold = ofRandom(10, 80);
        Item *particle = new Border(ofPoint(0, currentYLen), ofGetWidth(), bold, ofRandom(5, 8), Border::VERTICAL);
        particles.push_back(particle);
        currentYLen += bold;
    }
    random_shuffle(particles.begin(), particles.end());
}

float ofApp::getVelocity(float destination, float location, float velocity) {
    float force = stiffness * (destination - location);
    return damping * (velocity + force);
}

void ofApp::setGraphicId() {
    graphicId = getId();
    reset();
    ofLog(OF_LOG_NOTICE, "ID : " + ofToString(graphicId));
}

/**
 * Get env.
 */
JNIEnv* ofApp::getEnv() {
    if (env != NULL) {
        return env;
    }
    JNIEnv *e = ofGetJNIEnv();
    if (!e) {
        ofLogError() << "Couldn't get environment using GetEnv()." << endl;
        return NULL;
    }

    env = e;

    return env;
}

/**
 * Get OFActivity class.
 */
jclass ofApp::getOFActivityClass(JNIEnv *env) {
    if (ofActivityClass != NULL) {
        return ofActivityClass;
    }
    // Find reference for OFActivity.
    jclass localClass = env->FindClass("cc/openframeworks/bapaMockAndroid/OFActivity");
    jclass javaClass = (jclass) env->NewGlobalRef(localClass);
    if(!javaClass){
        ofLogError() << "Couldn't get java class for OFActivity." << endl;
        return NULL;
    }

    ofActivityClass = javaClass;

    return ofActivityClass;
}

/**
 * Get OFActivity object.
 */
jobject ofApp::getOFActivityObject(JNIEnv *env) {
    if (ofActivityObject != NULL) {
        return ofActivityObject;
    }
    jobject javaObject = ofGetOFActivityObject();
    javaObject = (jobject) env->NewGlobalRef(javaObject);
    if (!javaObject) {
        ofLogError() << "javaObject not found." << endl;
        return NULL;
    }

    ofActivityObject = javaObject;

    return ofActivityObject;
}

/**
 * This should be called after NewGlobalRef was executed otherwise Fatal signal 11 (SIGSEGV) will happen.
 */
void ofApp::reset() {
    JNIEnv *_env = getEnv();

    // Delete reference
    _env->DeleteGlobalRef(ofActivityObject);
    _env->DeleteGlobalRef(ofActivityClass);

    ofActivityObject = NULL;
    ofActivityClass = NULL;
    env = NULL;
}

/**
 * Get ID using getId method which OFActivity has.
 */
int ofApp::getId() {
    JNIEnv *_env = getEnv();
    jclass _ofActivityClass = getOFActivityClass(_env);
    jobject _ofActivityObject = getOFActivityObject(_env);

    // Find getId method from OFActivity.
    jmethodID javaGetIdMethod = _env->GetMethodID(_ofActivityClass, "getId","()I");
    if(!javaGetIdMethod){
        ofLogError() << "Couldn't get java getId from OFActivity." << endl;
        return -1;
    }

    int val = _env->CallIntMethod(_ofActivityObject, javaGetIdMethod);

    return val;
}

float ofApp::getAzimuth() {
    JNIEnv *_env = getEnv();
    jclass _ofActivityClass = getOFActivityClass(_env);
    jobject _ofActivityObject = getOFActivityObject(_env);

    // Find getId method from OFActivity.
    jmethodID javaGetIdMethod = _env->GetMethodID(_ofActivityClass, "getAzimuth","()F");
    if(!javaGetIdMethod){
        ofLogError() << "Couldn't get java getId from OFActivity." << endl;
        return -1;
    }

    float val = _env->CallFloatMethod(_ofActivityObject, javaGetIdMethod);

    return val;
}

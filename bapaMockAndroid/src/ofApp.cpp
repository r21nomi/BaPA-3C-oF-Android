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

    head.load("images/fish/fish_0.png");
    body.load("images/fish/fish_1.png");
    tail.load("images/fish/fish_2.png");

    stiffness = 0.1;
    damping = 0.85;
    interval = changeDelay = lastAzimuth = azimuthDiff = 0;
    timeUntilChangeGraphic = 30 * 1000;
    normAccelX = normAccelY = 0;
    gearController = new GearController();

    resetTime();
    createItems();
}

//--------------------------------------------------------------
void ofApp::update(){
    // For Exhibition.
    // if (hasTimePassed()) {
    //     changeGraphic(true);
    // }

    accel = ofxAccelerometer.getForce();
    normAccel = accel.getNormalized();

    velocity.x = getVelocity(destination.x, dummyLocation.x, velocity.x);
    dummyLocation.x += velocity.x;

    velocity.y = getVelocity(destination.y, dummyLocation.y, velocity.y);
    dummyLocation.y += velocity.y;

    // Use Z axis to make the origin the state of standing.
    normAccelX = normAccel.y * 2.5;
    normAccelY = normAccel.z * 2.5 * -1;

    if (normAccelX > 1) {
        normAccelX = 1;
    } else if (normAccelX < -1) {
        normAccelX = -1;
    }
    if (normAccelY > 1) {
        normAccelY = 1;
    } else if (normAccelY < -1) {
        normAccelY = -1;
    }

    if (particles[0] != NULL && dynamic_cast<Gear*>(particles[0])) {
        // Gear.
        gearController->update(normAccelX, normAccelY);

    } else {
        // Other graphic.
        int count = 0;
        for (Item *particle : particles) {
            particle->update(dummyLocation.x, dummyLocation.y, normAccelX, normAccelY);
            count++;
        }
    }

    changeGraphicIfNeeded();
}

//--------------------------------------------------------------
void ofApp::draw(){
    for (Item *particle : particles) {
        particle->draw();
    }

    if (isDebugMode()) {
        ofSetColor(255, 255, 255);
        font.drawString("x : " + ofToString(normAccel.x), 10, 30);
        font.drawString("y : " + ofToString(normAccel.y), 10, 60);
        font.drawString("z : " + ofToString(normAccel.z), 10, 90);
        font.drawString("latitude : " + ofToString(latitude), 10, 120);
        font.drawString("longitude : " + ofToString(longitude), 10, 150);
        font.drawString("speed : " + ofToString(speed), 10, 180);
        font.drawString("getAzimuth : " + ofToString(getAzimuth()), 10, 210);
        font.drawString("Interval : " + ofToString(interval), 10, 240);
        font.drawString("AzimuthDiff : " + ofToString(azimuthDiff), 10, 270);
        font.drawString("Elapsed Time : " + ofToString(getElapsedTime()), 10, 300);
        font.drawString("Graphic Id : " + ofToString(graphicId), 10, 330);
    }

    reset();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
    switch (graphicId) {
        case 1:
            createBorderItems();
            break;

        case 2:
            createRippleItems();
            break;

        case 3:
            createGearItems();
            break;

        default:
            particles.clear();

            float width = 100;
            float margin = 0;

            for (int i = 0, wLen = ofGetWidth() / (width + margin); i < wLen; i++) {
                for (int j = 0, hLen = ofGetHeight() / (width + margin); j < hLen; j++) {
                    Item *particle;

                    if (graphicId == 3) {
                        particle = new Particle(&img, ofPoint(i * (width + margin), j * (width + margin)), width);

                    } else if (graphicId == 4) {
                        particle = new Fish2(&head, &body, &tail, ofPoint(i * (width + margin), j * (width + margin)));

                    } else {
                        particle = new Fish(&img, ofPoint(i * (width + margin), j * (width + margin)), width);
                    }

                    float dist = ofDist(particle->getLocation().x, particle->getLocation().y, ofGetWidth() / 2, ofGetHeight() / 2);

                    if (dist < ofGetHeight() / 2) {
                        particles.push_back(particle);
                    }
                }
            }
            break;
    }
}

/**
 * Border
 */
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

/**
 * Ripple
 */
void ofApp::createRippleItems() {
    particles.clear();

    for (int i = 0, len = 50; i < len; i++) {
        Item *ripple = new Ripple(
            ofPoint(ofRandom(ofGetWidth()), ofRandom(ofGetHeight())),
            8,
            400,
            (int)ofRandom(0, 1500),
            ofColor(0, ofRandom(255), 255)
        );
        particles.push_back(ripple);
    }
}

/**
 * Gear
 */
void ofApp::createGearItems() {
    particles.clear();

    int diameter = 150;
    int bold = 30;
    int margin = 30;

    for (int x = 0, width = ofGetWidth(); x < width; x += (diameter + margin)) {
        for (int y = 0, height = ofGetHeight(); y < height; y += (diameter + margin)) {
            Gear *gear = new Gear(
                ofPoint(x, y),
                diameter,
                bold,
                4
            );
            Item *item = gear;
            particles.push_back(item);
        }
    }
    gearController->setItems(particles);
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

void ofApp::changeGraphicIfNeeded() {
    interval++;
    changeDelay++;

    if (interval > INTERVAL_OFFSET) {
        // Check at regular intervals.
        float azimuth = getAzimuth();
        float absDiff = ABS(azimuth - lastAzimuth);

        if (absDiff > AZIMUTH_DIFF_OFFSET
            && absDiff < 360 - AZIMUTH_DIFF_OFFSET
            && changeDelay > CHANGE_DELAY_OFFSET
            && ABS(normAccelX) < ACCEL_OFFSET
            && ABS(normAccelY) < ACCEL_OFFSET) {
            // Change graphic.
            azimuthDiff = lastAzimuth - azimuth;
            changeDelay = 0;

            changeGraphic(azimuthDiff > 0);
        }
        lastAzimuth = azimuth;
        interval = 0;
    }
}

void ofApp::changeGraphic(bool changetoNext) {
    if (changetoNext) {
        graphicId++;
        if (imageRefs.size() <= graphicId) {
            graphicId = 0;
        }
    } else {
        graphicId--;
        if (graphicId < 0) {
            graphicId = imageRefs.size() - 1;
        }
    }
    reset();
    img.clear();
    img.load(imageRefs[graphicId]);
    createItems();
    resetTime();
}

void ofApp::resetTime() {
    startTime = ofGetElapsedTimeMillis();
}

bool ofApp::hasTimePassed() {
    return getElapsedTime() > timeUntilChangeGraphic;
}

int ofApp::getElapsedTime() {
    return ofGetElapsedTimeMillis() - startTime;
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

bool ofApp::isDebugMode() {
    JNIEnv *_env = getEnv();
    jclass _ofActivityClass = getOFActivityClass(_env);
    jobject _ofActivityObject = getOFActivityObject(_env);

    // Find getId method from OFActivity.
    jmethodID javaGetIdMethod = _env->GetMethodID(_ofActivityClass, "isDebugMode","()Z");
    if(!javaGetIdMethod){
        ofLogError() << "Couldn't get java getId from OFActivity." << endl;
        return -1;
    }

    float val = _env->CallBooleanMethod(_ofActivityObject, javaGetIdMethod);

    return val;
}

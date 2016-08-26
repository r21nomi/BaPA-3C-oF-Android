#pragma once

#include "ofMain.h"
#include "ofxAndroid.h"
#include "Particle.hpp"
#include "Fish.hpp"
#include "Border.hpp"
#include "Ripple.hpp"
#include "Gear.hpp"
#include "GearController.hpp"
#include "ofxAccelerometer.h"
#include "Fish2.hpp"

#include "ofxAndroidGPS.h"
#include "ofxAndroidUtils.h"

class ofApp : public ofxAndroidApp{

    public:

        void setup();
        void update();
        void draw();

        void keyPressed(int key);
        void keyReleased(int key);
        void windowResized(int w, int h);

        void touchDown(int x, int y, int id);
        void touchMoved(int x, int y, int id);
        void touchUp(int x, int y, int id);
        void touchDoubleTap(int x, int y, int id);
        void touchCancelled(int x, int y, int id);
        void swipe(ofxAndroidSwipeDir swipeDir, int id);

        void pause();
        void stop();
        void resume();
        void reloadTextures();

        bool backPressed();
        void okPressed();
        void cancelPressed();
        void locationChanged(ofxLocation& location);

    private:
            void createItems();
            void createBorderItems();
            void createRippleItems();
            void createGearItems();
            float getVelocity(float destination, float location, float velocity);
            void setGraphicId();
            int getId();
            float getAzimuth();
            bool isDebugMode();
            JNIEnv* getEnv();
            jclass getOFActivityClass(JNIEnv *env);
            jobject getOFActivityObject(JNIEnv *env);
            void reset();
            void changeGraphicIfNeeded();
            void changeGraphic(bool changetoNext);
            bool hasTimePassed();
            void resetTime();
            int getElapsedTime();

            int INTERVAL_OFFSET = 20;
            int AZIMUTH_DIFF_OFFSET = 40;
            float ACCEL_OFFSET = 0.4;
            int CHANGE_DELAY_OFFSET = 100;

            JNIEnv* env;
            jclass ofActivityClass;
            jobject ofActivityObject;

            vector<Item*> particles;
            vector<string> imageRefs;
            ofImage img;
            float stiffness;
            float damping;
            ofPoint destination;
            ofPoint dummyLocation;
            ofPoint velocity;
            ofVec3f accel, normAccel;
            float normAccelX, normAccelY;
            float latitude, longitude, speed;
            ofTrueTypeFont font;
            int graphicId;
            int interval;
            int changeDelay;
            float lastAzimuth;
            float azimuthDiff;
            int startTime;
            int timeUntilChangeGraphic;
            GearController* gearController;
            ofImage head;
            ofImage body;
            ofImage tail;
};

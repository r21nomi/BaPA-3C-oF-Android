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
#include "Circle.hpp"

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
            enum Graphic {
                BORDER,
                RAIN,
                GEAR,
                FISH,
                FISH2,
                CIRCLE
            };
            void createItems();
            void createFish2Items();
            void createBorderItems();
            void createRippleItems();
            void createGearItems();
            void createCircleItems();

            float getVelocity(float destination, float location, float velocity);
            void setGraphicId();
            void setGraphicId(int id);
            int getId();
            float getAzimuth();
            bool isDebugMode();
            JNIEnv* getEnv();
            jclass getOFActivityClass(JNIEnv *env);
            jobject getOFActivityObject(JNIEnv *env);
            void reset();
            void changeGraphicIfNeeded();
            void changeGraphic(bool changetoNext);
            void updateGraphic();
            bool hasTimePassed(int time);
            void resetTime();
            int getElapsedTime();

            /**
             * Get updated image path.
             * ex. If current image path is "data/img_1_1.png", updated image path will be "data/img_1_2.png".
             *     If updated path was not found, the path will be "data/img_1_1.png".
             */
            static inline string GetUpdatedImagePath(string oldImagePath) {
                vector<string> imagePaths = ofSplitString(oldImagePath, ".");
                vector<string> imageNumbers = ofSplitString(imagePaths[0], "_");
                int imageNumber = ofToInt(imageNumbers[imageNumbers.size() - 1]);
                string newImagePath = "";
                for (int i = 0, len = imageNumbers.size(); i < len; i++) {
                    if (i < len - 1) {
                        newImagePath += (imageNumbers[i] + "_");
                    }
                }
                string newNumber = ofToString(imageNumber + 1);
                string extention = ("." + imagePaths[1]);

                ofFile file(ofToDataPath(newImagePath + newNumber + extention));

                if (!file.exists()) {
                    newNumber = "1";
                }

                newImagePath += (newNumber + extention);

                return newImagePath;
            }

            Graphic currentGraphic;
            int INTERVAL_OFFSET = 20;
            int AZIMUTH_DIFF_OFFSET = 40;
            float ACCEL_OFFSET = 0.4;
            int CHANGE_DELAY_OFFSET = 100;

            JNIEnv* env;
            jclass ofActivityClass;
            jobject ofActivityObject;

            vector<Item*> particles;
            vector<string> imageRefs;
            vector<ofImage> fishImages;
            vector<string> fishImagePaths;
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
};

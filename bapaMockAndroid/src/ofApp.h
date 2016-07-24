#pragma once

#include "ofMain.h"
#include "ofxAndroid.h"
#include "Particle.hpp"
#include "Fish.hpp"
#include "ofxAccelerometer.h"

#include "ofxAndroidGPS.h"
#include "ofxAndroidUtils.h"

//#ifndef TARGET_ANDROID
//struct ofxLocation{
//    double altitude;
//    double latitude;
//    double longitude;
//    float speed;
//    float bearing;
//};
//inline ostream & operator <<(ostream & ostr, const ofxLocation & location){
//    ostr << location.altitude << " " << location.latitude << " " << location.longitude << " " << location.bearing << " " << location.speed;
//    return ostr;
//}
//
//inline istream & operator >>(istream & istr, ofxLocation & location){
//    istr >> location.altitude >> location.latitude >> location.longitude >> location.bearing >> location.speed;
//    return istr;
//}
//#else
//#include "ofxGPS.h"
//#endif

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
            float getVelocity(float destination, float location, float velocity);
            void setGraphicId();
            int getId();
            float getAzimuth();
            vector <Item*> particles;
            vector<string> imageRefs;
            ofImage img;
            float stiffness;
            float damping;
            ofPoint destination;
            ofPoint dummyLocation;
            ofPoint velocity;
            ofVec3f accel, normAccel;
            float latitude, longitude, speed;
            ofTrueTypeFont font;
            int graphicId;
};

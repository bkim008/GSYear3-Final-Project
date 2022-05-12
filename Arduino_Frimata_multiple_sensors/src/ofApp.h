#pragma once

#include "ofMain.h"
#include "ofEvents.h"

class ofApp : public ofBaseApp{

    public:
        void setup();
        void update();
        void draw();

        void keyPressed(int key);
        void keyReleased(int key);
        void mouseMoved(int x, int y );
        void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
        void mouseEntered(int x, int y);
        void mouseExited(int x, int y);
        void windowResized(int w, int h);
        void dragEvent(ofDragInfo dragInfo);
        void gotMessage(ofMessage msg);
        
    ofTrueTypeFont font;
    ofArduino arduino;
    bool bSetupArduino;
    
    void setupArduino(const int& version);
    void digitalPinChanged(const int& pinNum);
    void analogPinChanged(const int& pinNum);
    void updateArduino();
    

    int potValue;
    int potValue2;
    int digitalInput;
    
    deque<int> mydeck;
    int countSwing = 0;
    bool BoolSwing = false;
    
    int Sensor1Max;
    int Sensor1Min;
    
};

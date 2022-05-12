#pragma once

#include "ofMain.h"

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
    
    
    ofArduino arduino;
    bool bSetupArduino;
    
    void setupArduino(const int& version);
    void digitalPinChanged(const int& pinNum);
    void analogPinChanged(const int& pinNum);
    void updateArduino();
    
    bool mouseEnter;
    bool buttonPressed;
    bool resetGenerator;
    bool timeflow;
    bool perlinMesh;
    
    ofVboMesh Mesh1;
    ofVboMesh Mesh2;
    ofVboMesh MeshF;
    
    
    int fileNum = 0;
    int width, height;
    float inc =0;
    float inc2 =0;
 
    
    ofColor initialColor = ofFloatColor(0,0,200);
    
    float icvalue1, icvalue2, icvalue3;
    float mesh1Lv1,mesh1Lv2,mesh1Lv3, mesh2Lv1,mesh2Lv2,mesh2Lv3, meshFLv1, meshFLv2, meshFLv3;
    
   
    ofEasyCam cam;
    ofNode target;
    ofNode orthoTarget;

    
    int hallSensorinput1;
    int hallSensorinput2;
    int hallSensorinput3;
    int digitalInput;
    
    float swingtime = 0;
    float endtime;
    int snapCounter;
    
    int randNum1 =0;
    int randNum2 =0;
    int randNum3 =0;
    
    int tempVal1;
    int tempVal2;
    int tempVal3;
    
    vector<int> oFvec1;
    vector<int> oFvec2;
    vector<int> oFvec3;
    
    int SensorMin1;
    int SensorMin2;
    int SensorMin3;
    
    float mapVal1;
    float mapVal2;
    float mapVal3;
    
    float privateCode1A;
    float privateCode1B;
    
    float privateCode2A;
    float privateCode2B;
    
    float privateCode3A;
    float privateCode3B;

    float NoiseVal1A;
    float NoiseVal1B;
    
    float NoiseVal2A;
    float NoiseVal2B;
    
    float NoiseVal3A;
    float NoiseVal3B;

    string msg;
  
    ofTrueTypeFont font;
    ofTrueTypeFont smallfont;
    ofTrueTypeFont pixelFont;
};

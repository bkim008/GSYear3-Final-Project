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
        
    

    ofVboMesh Mesh1;
    ofVboMesh Mesh2;
    ofVboMesh Mesh3;
    ofEasyCam cam;
    ofNode orthoTarget;
    
    ofCamera camera1;
    ofRectangle viewport;
  
    ofColor initialColor = ofFloatColor(255);
    
    int swingtime = 0;
    
    
    
    int width, height;
    bool PerlinMesh;
    float perlinRange, perlinHeight;
    float icvalue1, icvalue2, icvalue3;
    float inc = 0;
    float inc2 = 0;
    
};

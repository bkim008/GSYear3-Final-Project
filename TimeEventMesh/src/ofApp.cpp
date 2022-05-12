#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    
    Mesh1.setMode(OF_PRIMITIVE_TRIANGLES);
    Mesh2.setMode(OF_PRIMITIVE_TRIANGLES);
    Mesh3.setMode(OF_PRIMITIVE_TRIANGLES);
    ofEnableDepthTest();
    
    width = 200;
    height = 200;
 
    PerlinMesh = false;

    perlinRange =0.5;
    perlinHeight = 50;
    
    ofBackground(0);
    cam.setPosition(0, 0, 520);
    orthoTarget.setPosition(0,0,0);
    
    icvalue1 = 0;
    icvalue2 = 0;
    icvalue3 = 255;
    initialColor.setHsb(icvalue1, icvalue2, icvalue3);
    
    
    for (int y = 0; y < height; y++){
        for (int x = 0; x <width; x++){
            Mesh1.addVertex( ofPoint(x - width/2 , y - height/2 ,0));
    
            Mesh1.addColor(initialColor);
            
            Mesh2.addVertex( ofPoint(x - width/2 , y - height/2 ,-50));
            
            Mesh2.addColor(initialColor);
            
            Mesh3.addVertex( ofPoint(x - width/2 , y - height/2 ,-100));
            
            Mesh3.addColor(initialColor);
            
        }
    }
 
    
    //orthographic camera easycam

    //cam.removeAllInteractions();
    //cam.addInteraction(ofEasyCam::TRANSFORM_TRANSLATE_XY, OF_MOUSE_BUTTON_LEFT);
    //cam.addInteraction(ofEasyCam::TRANSFORM_TRANSLATE_Z, OF_MOUSE_BUTTON_RIGHT);
    //cam.enableOrtho();
    //cam.setNearClip(-1000000);
    //cam.setFarClip(1000000);
    //cam.setVFlip(true);


}

//--------------------------------------------------------------
void ofApp::update(){
    ofColor newColor;
    ofColor newColor2;
    ofColor newColor3;
    
    ofColor lerpColor;
    ofColor lerpColor2;
    ofColor lerpColor3;
    
    ofVec3f newPosition, newPosition2, newPosition3;
    ofVec3f oldPosition;
    ofVec3f oldPosition2;
    ofVec3f oldPosition3;
    
    ofVec3f lerpPosition;
    ofVec3f lerpPosition2;
    ofVec3f lerpPosition3;
    
    swingtime = ofGetElapsedTimeMillis();
   
    float time = ofGetSystemTimeMillis() /100.0;
    int i=0;
    
  
  
    if (PerlinMesh){
       inc = inc +0.00001;
        
       inc2 = inc2 +0.001;
        for (int y = 0; y<height; y++){
            for (int x=0; x<width; x++){
               
            
                oldPosition = Mesh1.getVertex(i);
                newPosition = Mesh1.getVertex(i);
    
                newPosition.z = ofNoise( ofMap( x + time, 0, width, 0, perlinRange),  ofMap(y, 0, height, 0, perlinRange) ) * perlinHeight;
          
               
                newPosition.x = ofNoise(ofMap( x, 0, width, 0, perlinRange),  ofMap(y+time, 0, height, 0, perlinRange) )* perlinHeight;
                
            
                lerpPosition.x = ofLerp(oldPosition.x, newPosition.x, inc);
                lerpPosition.y = ofLerp(oldPosition.y, newPosition.y, inc);
                lerpPosition.z = ofLerp(oldPosition.z, newPosition.z, inc);
          
                newColor.setHsb(30 ,  255 - ofMap( newPosition.z, 0,  perlinHeight, 0 , 255), 255);
                
                lerpColor.setHsb(ofLerp(icvalue1,30,inc2),ofLerp(icvalue2,255 - ofMap(newPosition.z, 0,  perlinHeight, 0 , 255),inc2),ofLerp(icvalue3, 255,inc2));
             
                Mesh1.setVertex(i, lerpPosition);
                Mesh1.setColor(i, lerpColor);
            
                
                oldPosition2 = Mesh2.getVertex(i);
                newPosition2 = Mesh2.getVertex(i);
                newPosition2.z = ofNoise( ofMap( x, 0, width, 0, perlinRange),  ofMap(y + time, 0, height, 0, perlinRange) ) * perlinHeight -50;
                
                   newPosition2.y = ofNoise(ofMap( x , 0, width, 0, perlinRange),  ofMap(y + time, 0, height, 0, perlinRange)) * perlinHeight;
                
                lerpPosition2.x = ofLerp(oldPosition2.x, newPosition2.x, inc);
                lerpPosition2.y = ofLerp(oldPosition2.y, newPosition2.y, inc);
                lerpPosition2.z = ofLerp(oldPosition2.z, newPosition2.z, inc);
                
                newColor2.setHsb(250 ,  255 - ofMap( newPosition2.z, 0,  perlinHeight, 0 , 255), 255);
                
                lerpColor2.setHsb(ofLerp(icvalue1,250,inc2),ofLerp(icvalue2,255 - ofMap(newPosition2.z, 0,  perlinHeight, 0 , 255),inc2),ofLerp(icvalue3, 255,inc2));
             
                Mesh2.setVertex(i, lerpPosition2);
                Mesh2.setColor(i, lerpColor2);
        
                
                oldPosition3 = Mesh3.getVertex(i);
                newPosition3 = Mesh3.getVertex(i);
                newPosition3.z = ofNoise( ofMap( x+time, 0, width, 0, perlinRange),  ofMap(y+time, 0, height, 0, perlinRange) ) * perlinHeight -100;
                
                lerpPosition3.x = ofLerp(oldPosition3.x, newPosition3.x, inc);
                lerpPosition3.y = ofLerp(oldPosition3.y, newPosition3.y, inc);
                lerpPosition3.z = ofLerp(oldPosition3.z, newPosition3.z, inc);
                
                newColor3.setHsb(150 ,  255 - ofMap( newPosition3.z, 0,  perlinHeight, 0 , 255), 255);
                
                lerpColor3.setHsb(ofLerp(icvalue1,150,inc2),ofLerp(icvalue2,255 - ofMap(newPosition3.z, 0,  perlinHeight, 0 , 255),inc2),ofLerp(icvalue3, 255,inc2));
                
                Mesh3.setVertex(i, lerpPosition3);
                Mesh3.setColor(i, lerpColor3);
          
                i++;
   
            }
        }
    }
    
    
    if(swingtime >= 15000){
        PerlinMesh = true;
    }
    
    //orthographic view to convert 3D images into 2D image for digital fabric sample. It is a fabrication process in digital.
    if(swingtime >= 30000){
        cam.enableOrtho();
        cam.setPosition(0, 0, 520);
        cam.setTarget(orthoTarget);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
 
    cam.begin();
    ofEnableDepthTest();
    
        ofPushMatrix();
        ofScale(2,2,2);
       //to increase the size of orthographic image, scale or values of width and height needs to be increased. Increasing width and height makes computer slower.
        glPointSize(3);
 
        Mesh1.drawVertices();
        Mesh2.drawVertices();
        Mesh3.drawVertices();
        
        // Mesh1.drawWireframe();
        // Mesh2.drawWireframe();
        // Mesh3.drawWireframe();
    
    ofPopMatrix();
    ofDisableDepthTest();
    cam.end();

    
    ofSetColor(255);
    ofDrawBitmapString(ofToString(swingtime), ofGetWidth()/12, ofGetHeight()/10);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    switch(key) {
        
        case 'f':
            ofToggleFullscreen();
        
            break;

        case 'p':
            PerlinMesh = !PerlinMesh;
            break;
            
        case 'o':
            cam.getOrtho() ? cam.disableOrtho() : cam.enableOrtho(); //ortho on and off
        
            break;
            
        case OF_KEY_UP:
            perlinRange +=0.1;
            break;
            
        case OF_KEY_DOWN:
            if (perlinRange > 0.1){
                perlinRange -=0.1;
            }
            break;
            
        case OF_KEY_RIGHT:
            perlinHeight +=0.1;
            break;
            
        case OF_KEY_LEFT:
            if (perlinHeight > 0.1){
                perlinHeight -=0.1;
            }
            break;
            
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}

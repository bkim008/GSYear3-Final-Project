#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    
    mainMesh.setMode(OF_PRIMITIVE_TRIANGLES);
    mainMesh2.setMode(OF_PRIMITIVE_TRIANGLES);
    mainMesh3.setMode(OF_PRIMITIVE_TRIANGLES);
    ofEnableDepthTest();
    
    width = 200;
    height = 200;
 
    PerlinMesh = false;

    perlinRange =0.5;
    perlinHeight = 50;
    
    ofBackground(0);
    cam.setPosition(0, 0, 220);
    
    icvalue1 = 0;
    icvalue2 = 0;
    icvalue3 = 255;
    initialColor.setHsb(icvalue1, icvalue2, icvalue3); //set original color as HSB to lerp colors
    
    
    for (int y = 0; y < height; y++){
        for (int x = 0; x <width; x++){
            mainMesh.addVertex( ofPoint(x - width/2 , y - height/2 ,0));
    
            mainMesh.addColor(initialColor);
            
            mainMesh2.addVertex( ofPoint(x - width/2 , y - height/2 ,-50));
            
            mainMesh2.addColor(initialColor);
            
            mainMesh3.addVertex( ofPoint(x - width/2 , y - height/2 ,-100));
            
            mainMesh3.addColor(initialColor);
            
        }
    }
 

}

//--------------------------------------------------------------
void ofApp::update(){
    ofColor newColor;
    ofColor newColor2;
    ofColor newColor3;
    ofColor lerpColor;
    
    ofVec3f newPosition, newPosition2, newPosition3;
    ofVec3f oldPosition;
    ofVec3f lerpPosition;
   
    float time = ofGetSystemTimeMillis() /100.0;
    int i=0;
    
  
  
    if (PerlinMesh){
       inc = inc +0.00001; //increment value for lerping position. Increasing this value makes lerp                    faster to new shape
        
       inc2 = inc2 +0.0008; //increment value for lerping colors.
        for (int y = 0; y<height; y++){
            for (int x=0; x<width; x++){
               
            
                oldPosition = mainMesh.getVertex(i); // saves the old position to lerp
                newPosition = mainMesh.getVertex(i);
    
                newPosition.z = ofNoise( ofMap( x + time, 0, width, 0, perlinRange),  ofMap(y, 0, height, 0, perlinRange) ) * perlinHeight;
          
               
                newPosition.x = ofNoise(ofMap( x, 0, width, 0, perlinRange),  ofMap(y+time, 0, height, 0, perlinRange) )* perlinHeight;
                
         
                lerpPosition.x = ofLerp(oldPosition.x, newPosition.x, inc);
                lerpPosition.y = ofLerp(oldPosition.y, newPosition.y, inc);
                lerpPosition.z = ofLerp(oldPosition.z, newPosition.z, inc);
          
                newColor.setHsb(230 ,  255 - ofMap( newPosition.z, 0,  perlinHeight, 0 , 255), 255);
                
                lerpColor.setHsb(ofLerp(icvalue1,230,inc2),ofLerp(icvalue2,255 - ofMap(newPosition.z, 0,  perlinHeight, 0 , 255),inc2),ofLerp(icvalue3, 255,inc2));
                //lerp from each hsb values of icvalue 1,2,3 to current newColor hsb values
                
                
        
                mainMesh.setVertex(i, lerpPosition); //change to lerpPoistion and lerpColor
                mainMesh.setColor(i, lerpColor);
                
              
                
                
                
                
           //     newPosition2 = mainMesh2.getVertex(i);
           //     newPosition2.z = ofNoise( ofMap( x, 0, width, 0, perlinRange),  ofMap(y + time, 0, height, 0, perlinRange) ) * perlinHeight -50;
                

           //        newPosition2.y = ofNoise(ofMap( x , 0, width, 0, perlinRange),  ofMap(y + time, 0, height, 0, perlinRange)) * perlinHeight;
           //     newColor2.setHsb(250 ,  255 - ofMap( newPosition2.z, 0,  perlinHeight, 0 , 255), 255);
                
                
           //     mainMesh2.setVertex(i, newPosition2);
            //    mainMesh2.setColor(i, newColor2);
        
                
                newPosition3 = mainMesh3.getVertex(i);
                newPosition3.z = ofNoise( ofMap( x+time, 0, width, 0, perlinRange),  ofMap(y+time, 0, height, 0, perlinRange) ) * perlinHeight -100;
                
                newColor3.setHsb(150 ,  255 - ofMap( newPosition3.z, 0,  perlinHeight, 0 , 255), 255);
                
         
                mainMesh3.setVertex(i, newPosition3);
                mainMesh3.setColor(i, newColor3);
          
                i++;
   
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
 
    cam.begin();
    ofEnableDepthTest();
    
        ofPushMatrix();
        glPointSize(4);
 
        mainMesh.drawVertices();
        mainMesh2.drawVertices();
        mainMesh3.drawVertices();
        
        // mainMesh.drawWireframe();
        // mainMesh2.drawWireframe();
        // mainMesh3.drawWireframe();
    
    ofPopMatrix();
    ofDisableDepthTest();
    cam.end();

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

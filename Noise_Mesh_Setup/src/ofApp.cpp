#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    
    mainMesh.setMode(OF_PRIMITIVE_TRIANGLES);
    mainMesh2.setMode(OF_PRIMITIVE_TRIANGLES);
    mainMesh3.setMode(OF_PRIMITIVE_TRIANGLES);
    ofEnableDepthTest();
    
    width = 200; // change the pixel amount, going over 350 slows down the computer
    height = 200;
 
    PerlinMesh = false; //default mode as a normal mesh

    perlinRange =0.5; // between 0~1 noise values
    perlinHeight = 50; // how the positions of elements of mesh wants to be
    
    ofBackground(0);
    cam.setPosition(0, 0, 220);
    
    
    for (int y = 0; y < height; y++){
        for (int x = 0; x <width; x++){
            mainMesh.addVertex( ofPoint(x - width/2 , y - height/2 ,0));
            //  create a mesh. Mesh index = x + y*width
            mainMesh.addColor(ofFloatColor(255));
            
            mainMesh2.addVertex( ofPoint(x - width/2 , y - height/2 ,-50));
            //line the meshes by giving z values
            
            mainMesh2.addColor(ofFloatColor(255));
            
            mainMesh3.addVertex( ofPoint(x - width/2 , y - height/2 ,-100));
            
            mainMesh3.addColor(ofFloatColor(255));
            
        }
    }
    

}

//--------------------------------------------------------------
void ofApp::update(){
    ofColor newColor;
    ofColor newColor2;
    ofColor newColor3;
 
    ofVec3f newPosition, newPosition2, newPosition3;
   
    float time = ofGetSystemTimeMillis() /100.0;
    int i=0;
  
    if (PerlinMesh){ // by pressing p, if the Perlin Mesh is true, meshes gets noise effects
    
        for (int y = 0; y<height; y++){
            for (int x=0; x<width; x++){
               
                
                //experiments with giving noise effects to x,y,z values with hsb colors. Noise effect can be visualized when there is a moving value like time. Applying moving value to x and y also results in different patterns.
                
                
                newPosition = mainMesh.getVertex(i);
                //position each dots in mesh to new position
                newPosition.z = ofNoise( ofMap( x + time, 0, width, 0, perlinRange),  ofMap(y, 0, height, 0, perlinRange) ) * perlinHeight;
                //apply noise effect to z value or x, y.
               
                newPosition.x = ofNoise(ofMap( x, 0, width, 0, perlinRange),  ofMap(y+time, 0, height, 0, perlinRange) )* perlinHeight;
               // newPosition.y = ofNoise(ofMap( x , 0, width, 0, perlinRange),  ofMap(y + time, 0, height, 0, perlinRange)) * perlinHeight;
                newColor.setHsb(230 ,  255 - ofMap( newPosition.z, 0,  perlinHeight, 0 , 255), 255);
            //  newColor.setHsb(230 ,  255 - ofMap( newPosition.x, 0,  50, 0 , 255), 255);
                
                mainMesh.setVertex(i, newPosition);
                mainMesh.setColor(i, newColor);
                
              
                
                newPosition2 = mainMesh2.getVertex(i);
                newPosition2.z = ofNoise( ofMap( x, 0, width, 0, perlinRange),  ofMap(y + time, 0, height, 0, perlinRange) ) * perlinHeight -50;
                
                //   newPosition2.x = ofNoise(ofMap( x , 0, width, 0, perlinRange),  ofMap(y + time, 0, height, 0, perlinRange)) * perlinHeight;
                   newPosition2.y = ofNoise(ofMap( x , 0, width, 0, perlinRange),  ofMap(y + time, 0, height, 0, perlinRange)) * perlinHeight;
                newColor2.setHsb(250 ,  255 - ofMap( newPosition2.z, 0,  perlinHeight, 0 , 255), 255);
                
                
                mainMesh2.setVertex(i, newPosition2);
                mainMesh2.setColor(i, newColor2);
        
                
                newPosition3 = mainMesh3.getVertex(i);
                newPosition3.z = ofNoise( ofMap( x+time, 0, width, 0, perlinRange),  ofMap(y+time, 0, height, 0, perlinRange) ) * perlinHeight -100;
                
              //   newPosition3.x = ofNoise(ofMap( x , 0, width, 0, perlinRange),  ofMap(y + time, 0, height, 0, perlinRange)) * 120;
              //    newPosition3.y = ofNoise(ofMap( x , 0, width, 0, perlinRange),  ofMap(y + time, 0, height, 0, perlinRange)) * 120;
           
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
    // experiment on the point size along with the width and height values
        mainMesh.drawVertices();
        mainMesh2.drawVertices();
        mainMesh3.drawVertices();
        
        // mainMesh.drawWireframe();    wireframe instead of dots.
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
            PerlinMesh = !PerlinMesh; //activate perlin noise mesh
            break;
            
        case OF_KEY_UP: // increase noise value
            perlinRange +=0.1;
            break;
            
        case OF_KEY_DOWN: // decrease noise value
            if (perlinRange > 0.1){
                perlinRange -=0.1;
            }
            break;
            
        case OF_KEY_RIGHT: // increase noise distortion
            perlinHeight +=0.1;
            break;
            
        case OF_KEY_LEFT: // decrease noise distortion
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

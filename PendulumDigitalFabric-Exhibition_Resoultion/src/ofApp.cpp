#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(255);
    
    Mesh1.setMode(OF_PRIMITIVE_TRIANGLES);
    Mesh2.setMode(OF_PRIMITIVE_TRIANGLES);
    MeshF.setMode(OF_PRIMITIVE_TRIANGLES);
    
    ofEnableDepthTest();
    ofResetElapsedTimeCounter();
    
    width = 300;
    height = 200;
    
    orthoTarget.setPosition(0,0,0);
    target.setPosition(-100,50,-180);
    cam.setPosition(-100, 700, 250);
    cam.setTarget(target);
    
    icvalue1 = 166;
    icvalue2 = 250;
    icvalue3 = 250;
    initialColor.setHsb(icvalue1, icvalue2, icvalue3);
    
    for (int y = 0; y < height; y++){
        for (int x = 0; x <width; x++){

            Mesh1.addVertex( ofPoint(x - 2*width/5 , y - height/2 ,-20));
            Mesh2.addVertex( ofPoint(x - 2*width/5 , y - height/2 ,-60));
            MeshF.addVertex( ofPoint(x - 2*width/5 , y - height/2 ,-100));
            
            
            Mesh1.addColor(initialColor);
            Mesh2.addColor(initialColor);
            MeshF.addColor(initialColor);
            
        }
    }
    
    
    hallSensorinput1 = 0;
    hallSensorinput2 = 0;
    hallSensorinput3 = 0;
    
     privateCode1A=0;
     privateCode1B=0;
    
     privateCode2A=0;
     privateCode2B=0;
    
     privateCode3A=0;
     privateCode3B=0;
    
   
    
   
    font.load("Zector.ttf",60);
    smallfont.load("Zector.ttf",50);
    pixelFont.load("Pixel-UniCode.ttf",23);
    arduino.connect("/dev/cu.usbmodem14701" , 57600);
    ofAddListener(arduino.EInitialized, this, &ofApp::setupArduino);
    bSetupArduino = false;
    
    resetGenerator = false;
    buttonPressed = false;
    mouseEnter = false;
   
    swingtime = 200000; // 맨처음 시작시 자동 버튼 눌림 방지
    endtime = 91000;

    
}

//--------------------------------------------------------------
void ofApp::update(){

    if(timeflow==true){
        swingtime = ofGetElapsedTimeMillis();
        
    }
    
    if(resetGenerator==true){
        swingtime = endtime;
        timeflow = true;
        ofResetElapsedTimeCounter();
        snapCounter = 0;
        
        oFvec1.clear();
        oFvec2.clear();
        oFvec3.clear();
        
        randNum1 = ofRandom(99);
        randNum2 = ofRandom(99);
        randNum3 = ofRandom(99);
        
        tempVal1 = ofRandom(1,99);
        tempVal2 = ofRandom(1,99);
        tempVal3 = ofRandom(1,99);
        
        SensorMin1 = 0;
        SensorMin2 = 0;
        SensorMin3 = 0;
    }
    
    updateArduino();
    
    if(buttonPressed==true){
        
        
        oFvec1.emplace_back(hallSensorinput1);
        oFvec2.emplace_back(hallSensorinput2);
        oFvec3.emplace_back(hallSensorinput3);
        
        
        ofSort(oFvec1);
        ofSort(oFvec2);
        ofSort(oFvec3);
        
        SensorMin1 = oFvec1[0];
        SensorMin2 = oFvec2[0];
        SensorMin3 = oFvec3[0];
        
    }
    
    
    if(swingtime >= 3000){
        buttonPressed = true;
    }
    
    if(swingtime>= 16000){
        
        buttonPressed = false;
    }
    

    mapVal1 = 545 - SensorMin1;
    mapVal2 = 522 - SensorMin2;
    mapVal3 = 529 - SensorMin3;
 
    
 
    privateCode1A = mapVal1*(99/60);
    privateCode2A = mapVal2*(99/60);
    privateCode3A = mapVal3*(99/60);
    
    if(mapVal1 >60 || 3>mapVal1){
         privateCode1A = tempVal1;
    }
    
    if(mapVal2 >60 || 3>mapVal2){
         privateCode2A = tempVal2;
    }
    
    if(mapVal3 >60 || 3>mapVal3){
        privateCode3A = tempVal3;
    }
    
    privateCode1B = randNum1;
    privateCode2B = randNum2;
    privateCode3B = randNum3;
  
    
    ofColor newColor1,lerpColor1;
    ofColor newColor2,lerpColor2;
    ofColor newColorF,lerpColorF;
    
    ofVec3f newPosition1, oldPosition1, lerpPosition1;
    ofVec3f newPosition2, oldPosition2, lerpPosition2;
    ofVec3f newPositionF, oldPositionF, lerpPositionF;

    
    float time = ofGetElapsedTimeMillis()/100.0 + privateCode1B*300;
    int i=0;
    
    if(perlinMesh==true){
        
        inc= inc + 0.00006;
        inc2= inc2 + 0.005;
        
        if(inc2 >= 1.0){
        inc2 = 1.0;
        }
        if(inc >= 1.0){
        inc = 1.0;
        }
        
        NoiseVal1A = ofMap(privateCode1A, 0, 99, 100, 320);
        NoiseVal1B = ofMap(privateCode1B, 0, 99, 115, 125);
        
        NoiseVal2A = ofMap(privateCode2A, 0, 99, 50, 180);
        NoiseVal2B = ofMap(privateCode2B, 0, 99, 70, 90);
        
        NoiseVal3A = ofMap(privateCode3A, 0, 99, 0, 20);
        
        
       
        for (int y = 0; y<height; y++){
            for (int x=0; x<width; x++){
        
                oldPosition1 = Mesh1.getVertex(i);
                newPosition1 = Mesh1.getVertex(i);
             
                newPosition1.x = ofNoise(ofMap(x+time, 0, width, 0, 1.0),   ofMap(y, 0, height, 0, 1.0))* NoiseVal1A - NoiseVal1B;
                newPosition1.z = ofNoise( ofMap(x+time, 0, width, 0, 1.0),ofMap(y, 0, height, 0, 1.0)) * (40+privateCode1B);
                
                lerpPosition1 = Mesh1.getVertex(i);
                lerpPosition1.x = ofLerp(oldPosition1.x, newPosition1.x, inc);
                lerpPosition1.y = ofLerp(oldPosition1.y, newPosition1.y, inc);
                lerpPosition1.z = ofLerp(oldPosition1.z, newPosition1.z, inc);
                
                mesh1Lv1 =ofMap(privateCode1B, 0, 99, 0, 255);
                mesh1Lv2 =156+privateCode1A;
                mesh1Lv3 =156+privateCode1B;
             
                
                newColor1.setHsb(mesh1Lv1, mesh1Lv2, mesh1Lv3);
                
                lerpColor1.setHsb(ofLerp( icvalue1, mesh1Lv1,inc2),ofLerp( icvalue2, mesh1Lv2,inc2),ofLerp( icvalue3, mesh1Lv3,inc2));
                
                Mesh1.setVertex(i, lerpPosition1);
                Mesh1.setColor(i, lerpColor1);
                
                
                
                
                oldPosition2 = Mesh2.getVertex(i);
                newPosition2 = Mesh2.getVertex(i);
             
                newPosition2.y =ofNoise( ofMap(x+time, 0, width, 0, 1.0),  ofMap(y+time, 0, height, 0, 1.0)) * NoiseVal2A - NoiseVal2B;
                newPosition2.z = ofNoise(ofMap( x , 0, width, 0, 1.0),  ofMap(y + time, 0, height, 0, 1.0)) * (40+privateCode2B);
        
                lerpPosition2 = Mesh2.getVertex(i);
                lerpPosition2.x = ofLerp(oldPosition2.x, newPosition2.x, inc);
                lerpPosition2.y = ofLerp(oldPosition2.y, newPosition2.y, inc);
                lerpPosition2.z = ofLerp(oldPosition2.z, newPosition2.z, inc);
                
                mesh2Lv1 =ofMap(privateCode2B, 0, 99, 0, 255);;
                mesh2Lv2 =156+privateCode2A;
                mesh2Lv3 =156+privateCode2B;
            
                
                newColor2.setHsb( mesh2Lv1,  mesh2Lv2,  mesh2Lv3);
                
                lerpColor2.setHsb(ofLerp( icvalue1, mesh2Lv1,inc2),ofLerp( icvalue2, mesh2Lv2,inc2),ofLerp( icvalue3, mesh2Lv3,inc2));
                
                Mesh2.setVertex(i, lerpPosition2);
                Mesh2.setColor(i, lerpColor2);
                
                
                
                
                oldPositionF = MeshF.getVertex(i);
                newPositionF = MeshF.getVertex(i);
             
                newPositionF.z = ofNoise( ofMap(x+time, 0, width, 0, 1.0),ofMap(y+time, 0, height, 0, 1.0)) * (35+NoiseVal3A);
        
                lerpPositionF = MeshF.getVertex(i);
                lerpPositionF.x = ofLerp(oldPositionF.x, newPositionF.x, inc);
                lerpPositionF.y = ofLerp(oldPositionF.y, newPositionF.y, inc);
                lerpPositionF.z = ofLerp(oldPositionF.z, newPositionF.z, inc);
    
                
                meshFLv1 =ofMap(privateCode3B, 0, 99, 0, 255);;
                meshFLv2 =ofMap(newPositionF.z, 0, (35+NoiseVal3A), 0 , 255);
                meshFLv3 =250;
                
                newColorF.setHsb(meshFLv1,meshFLv2,meshFLv3);
                
                MeshF.setVertex(i, lerpPositionF);
                MeshF.setColor(i, newColorF);
                
                
                i++;
            }
        }
    }
    
    
    if(perlinMesh == true){
        snapCounter = snapCounter +1;
    }
    if(snapCounter == 995){ //adjustment for different cpu speed
        ofSetDataPathRoot("/Users/exhibition26002/Desktop/Gift/");//path to desktop file
        ofSaveScreen(ofToString(fileNum)+"gift.png");
         
        fileNum=fileNum+1;
        
        snapCounter = 0;
      }
    
    
    if(swingtime >= 16000){
        perlinMesh = true;
    }

    if(swingtime >= 19000){
        cam.setPosition(0, 0, 610);
        cam.setTarget(orthoTarget);
        cam.enableOrtho();
    }
    
    if(swingtime >= 56000){
        perlinMesh = false;
     
    }
 
    if(swingtime >= endtime){  

        cam.setPosition(-100, 700, 250);
        cam.setTarget(target);
        cam.disableOrtho();
      
        snapCounter = 0;
        swingtime = 200000;
        
        Mesh1.clear();
        Mesh2.clear();
        MeshF.clear();
        
        inc =0;
        inc2 =0;
        
        for (int y = 0; y < height; y++){
            for (int x = 0; x <width; x++){
              
                Mesh1.addVertex( ofPoint(x - 2*width/5 , y - height/2 ,-20));
                Mesh2.addVertex( ofPoint(x - 2*width/5 , y - height/2 ,-60));
                MeshF.addVertex( ofPoint(x - 2*width/5 , y - height/2 ,-100));
                
                Mesh1.addColor(initialColor);
                Mesh2.addColor(initialColor);
                MeshF.addColor(initialColor);
            }
        }
        
        privateCode1A = 0;
        privateCode1B = 0;
        
        privateCode2A = 0;
        privateCode2B = 0;
        
        privateCode3A = 0;
        privateCode3B = 0;
        
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(0);

    cam.begin();
    ofEnableDepthTest();
    ofPushMatrix();
    ofScale(3,3,3);
    glPointSize(3);
    
    Mesh1.drawVertices();
    Mesh2.drawVertices();
    MeshF.drawVertices();
    
    ofPopMatrix();
    ofDisableDepthTest();
    cam.end();

    ofPushMatrix();
    ofTranslate(ofGetWidth()/6, ofGetHeight()/2, 0);
    ofRotateZ(90);
    
    int dpVal1 = privateCode1A;
    int dpVal2 = privateCode1B;
    int dpVal3 = privateCode2A;
    int dpVal4 = privateCode2B;
    int dpVal5 = privateCode3A;
    int dpVal6 = privateCode3B;
    int dpRand = ofRandom(11,99);

    string displayText1 = ofToString(dpVal1);
    string displayText2 = ofToString(dpVal2);
    string displayText3 = ofToString(dpVal3);
    string displayText4 = ofToString(dpVal4);
    string displayText5 = ofToString(dpVal5);
    string displayText6 = ofToString(dpVal6);
 
    if(dpVal1 < 10){
        displayText1 = "0"+ofToString(dpVal1);
    }
    if(dpVal2 < 10){
        displayText2 = "0"+ofToString(dpVal2);
    }
    if(dpVal3 < 10){
        displayText3 = "0"+ofToString(dpVal3);
    }
    if(dpVal4 < 10){
        displayText4 = "0"+ofToString(dpVal4);
    }
    if(dpVal5 < 10){
        displayText5 = "0"+ofToString(dpVal5);
    }
    if(dpVal6 < 10){
        displayText6 = "0"+ofToString(dpVal6);
    }
  
    msg= "[00,00,00,00,00,00]";
  
    if(swingtime >= 0 && swingtime <= 16000){
        msg= "["+ofToString(dpRand)+","+ofToString(dpRand)+","+ofToString( dpRand)+","+ofToString(dpRand)+","+ofToString(dpRand)+","+ofToString(dpRand)+"]";
        
    }else if(swingtime > 16000 && swingtime <= endtime){
        msg= "["+displayText1+","+displayText2+"," +displayText3+"," +displayText4+"," +displayText5+"," +displayText6+"]";
    }else{
        msg= "[00,00,00,00,00,00]";
    }
    
    font.drawString(msg, -399, 40);
    
    
    if(swingtime >= 0 && swingtime <= 56000){
      
        smallfont.drawString("-Processing-", -209,130);
    }else if(swingtime >= 56000 && swingtime <= endtime){

        smallfont.drawString("-Printing-", -173, 130);
    }else{
    
        smallfont.drawString("-Press Button-", -245, 130);
    }
    
    ofPushStyle();
    
    ofSetColor(0,0,0,180);
    
    //adjustments for text translate has been made for exhibition TV screen
    pixelFont.drawString(ofToString(swingtime),-680,-1870);
    pixelFont.drawString("Min1:" + ofToString(SensorMin1),-680,-1845);
    pixelFont.drawString("Min2:" + ofToString(SensorMin2),-680,-1820);
    pixelFont.drawString("Min3:" + ofToString(SensorMin3),-680,-1795);
    
    
    if(!bSetupArduino){
        pixelFont.drawString("!Arduino not ready \n",-680,-1900);
    }else{
       
        pixelFont.drawString("!Arduino: On \n",-680,-1900);
    }
    
    ofPopStyle();
    
    ofPopMatrix();
    
}

//--------------------------------------------------------------
void ofApp::setupArduino(const int& version){
    ofRemoveListener(arduino.EInitialized, this, &ofApp::setupArduino);
    bSetupArduino = true;

    arduino.sendAnalogPinReporting(0, ARD_ANALOG);
    arduino.sendAnalogPinReporting(1, ARD_ANALOG);
    arduino.sendAnalogPinReporting(2, ARD_ANALOG);
    arduino.sendDigitalPinMode(8, ARD_INPUT);

    ofAddListener(arduino.EAnalogPinChanged, this, &ofApp::analogPinChanged);
    ofAddListener(arduino.EDigitalPinChanged, this, &ofApp::digitalPinChanged);
    

}

//--------------------------------------------------------------
void ofApp::updateArduino(){
    arduino.update();
 
}

//--------------------------------------------------------------
void ofApp::analogPinChanged(const int& pinNum){
    hallSensorinput1 = arduino.getAnalog(0);
    hallSensorinput2 = arduino.getAnalog(1);
    hallSensorinput3 = arduino.getAnalog(2);
}

//--------------------------------------------------------------
void ofApp::digitalPinChanged(const int& pinNum){

    digitalInput = arduino.getDigital(8);
  
    if(arduino.getDigital(8)){
        
        resetGenerator = true;

    }else{
        resetGenerator = false;
       
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    switch(key) {
    
case 'o':
            
    cam.getOrtho() ? cam.disableOrtho() : cam.enableOrtho();

    break;
case 'f':
    ofToggleFullscreen();

    break;
            
case 'p':
            
    resetGenerator = !resetGenerator;
                    
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

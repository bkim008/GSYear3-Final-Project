#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(30);
    ofBackground(255,0,130);
    

    potValue = 0;
    potValue2 = 0;
    digitalInput =0;
  
    
    font.load("verdana.ttf",34);
    arduino.connect("/dev/cu.usbmodem14201" , 57600);
    
    ofAddListener(arduino.EInitialized, this, &ofApp::setupArduino);
    bSetupArduino = false;
   
    
}

//--------------------------------------------------------------
void ofApp::update(){
    updateArduino();
    
    mydeck.push_front(potValue);
    
    if(mydeck.size() > 3){
        mydeck.pop_back();
    }
    
    int val1 = mydeck[0];
    int val2 = mydeck[1];
    int val3 = mydeck[2];
    
    
    if((mydeck[2] < mydeck[1] && mydeck[1] > mydeck[0]) || (mydeck[2] > mydeck[1] && mydeck[1] < mydeck[0])){
        BoolSwing = true;
    }else{
        BoolSwing = false;
    }

    
    
    
    if(BoolSwing == true){
        countSwing++;
    }
    
    if(countSwing == 5){     //storing sensor values of max and min
        Sensor1Min = val3;
    }
    
    if(countSwing == 6){
        Sensor1Max = val3;
    }
    
    
      for(int i=0; i<mydeck.size(); i++){
          cout<< mydeck[0] << mydeck[1] << mydeck[2] <<'\n' << countSwing << '\n'<< mydeck.size()<< '\n';
      }
    
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //simple UI to test input values using Firmata Protocol
    ofSetColor(0,0,0,127);
    ofDrawRectangle(15,15,770,65);
    ofSetColor(0,0,0,127);
    ofDrawRectangle(15, 95, 770, 270);
    
    float value = ofMap(potValue, 0 ,1023, 0, 255);
    ofSetColor(value,value,value);
    ofDrawRectangle(15, 380, 770, 205);
    
    ofSetColor(255,255,255);
    
    if(!bSetupArduino){
        font.drawString("arduino not ready \n",20,70);
    }else{
        font.drawString("arduino On \n", 20, 70);
        font.drawString("analog input:" + ofToString(potValue),20,165);
        font.drawString("analog input2:" + ofToString(potValue2),20,200);
        font.drawString("digital input:" + ofToString(digitalInput),20,235);
        
    }
    
    
    
    
    string msg;
    msg+= ofToString(Sensor1Min);
    font.drawString(msg, 200, 150);
    
    string msg2;
    msg2+= ofToString(Sensor1Max);
    font.drawString(msg2, 200, 100);
    
    
    
    
    
}

//--------------------------------------------------------------
void ofApp::setupArduino(const int& version){
    ofRemoveListener(arduino.EInitialized, this, &ofApp::setupArduino);
    bSetupArduino = true;
    
    arduino.sendAnalogPinReporting(0, ARD_ANALOG); // two hall sensor input to each pin of 0,1
    arduino.sendAnalogPinReporting(1, ARD_ANALOG);
    arduino.sendDigitalPinMode(8, ARD_INPUT); //digital input for button interaction

    ofAddListener(arduino.EAnalogPinChanged, this, &ofApp::analogPinChanged);
    ofAddListener(arduino.EDigitalPinChanged, this, &ofApp::digitalPinChanged);

}

//--------------------------------------------------------------
void ofApp::updateArduino(){
    arduino.update();

}

    
//--------------------------------------------------------------
void ofApp::analogPinChanged(const int& pinNum){
    potValue = arduino.getAnalog(0); //gets sensor value from sensor1
    potValue2 = arduino.getAnalog(1); //gets sensor value from sensor2
    

}

//--------------------------------------------------------------
void ofApp::digitalPinChanged(const int& pinNum){
    
    digitalInput = arduino.getDigital(8);
    //whether the button is pressed or not. If pressesd gets 1, if not gets 0
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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

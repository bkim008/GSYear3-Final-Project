#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    ofBackground(255,0,130);
    
    buttonState = 0;
    potValue = 0;
    PWMValue = 0;
    
    font.load("verdana.ttf",34);
    arduino.connect("/dev/cu.usbmodem14201" , 57600);
    
    ofAddListener(arduino.EInitialized, this, &ofApp::setupArduino);
    bSetupArduino = false;
   
}

//--------------------------------------------------------------
void ofApp::update(){
    updateArduino();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
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
        font.drawString("arduino Firmata On \n", 20, 70);
        font.drawString("analog input:" + ofToString(potValue),20,165);
    }
    
    
    
    
}

//--------------------------------------------------------------
void ofApp::setupArduino(const int& version){
    ofRemoveListener(arduino.EInitialized, this, &ofApp::setupArduino);
    bSetupArduino = true;
   
    arduino.sendAnalogPinReporting(0, ARD_ANALOG);//A0 pin to analog input
    
    
    arduino.sendDigitalPinMode(13, ARD_OUTPUT); //13 pin to analog output
    

    arduino.sendDigitalPinMode(9, ARD_PWM); // 9 pin to analog output
    
    //changes on the digital and analog pins
    ofAddListener(arduino.EDigitalPinChanged, this, &ofApp::digitalPinChanged);
    ofAddListener(arduino.EAnalogPinChanged, this, &ofApp::analogPinChanged);
    

}

//--------------------------------------------------------------
void ofApp::updateArduino(){
    arduino.update();
    if(bSetupArduino){
        PWMValue = (int)(128 + 128 * sin(ofGetElapsedTimef())); //PWM 0~255 value test
        arduino.sendPwm(9, PWMValue);
    }

}

//--------------------------------------------------------------
void ofApp::digitalPinChanged(const int& pinNum){
    buttonState = arduino.getDigital(pinNum);
    
}
    
//--------------------------------------------------------------
void ofApp::analogPinChanged(const int& pinNum){
    potValue = arduino.getAnalog(pinNum);
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

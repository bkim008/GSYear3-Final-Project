#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(255);
    font.load("verdana.ttf",34);
    
    serial.listDevices();
    vector<ofSerialDeviceInfo> deviceList = serial.getDeviceList();
    
    for(auto list: deviceList) {
        cout << list.getDevicePath() << endl;
    }
    
    serial.setup("/dev/cu.usbmodem14101", 9600); //Arduino port number
    recvData.clear();
}

//--------------------------------------------------------------
void ofApp::update(){
    
    char ch;
    if(serial.available()){
        while((ch = serial.readByte())>0) {
            if(ch== ' ' ){
                distance = ofToFloat(recvData);
                cout<< "Received: "<< distance<< endl;
                recvData.clear();
            } else{
                recvData+= ch;
            
            }
        }
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(20, 20, 20);
    ofSetColor(200,200,200);
    string msg;
    msg+= "Distance" + ofToString(distance);
    font.drawString(msg, 100, 100);
    ofSetColor(20, 20, 200);
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    ofScale(distance/8); //scale changes according to the sensor value
 
    ofDrawEllipse(0, 0, 50, 50);
    
    

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

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
    initialColor.setHsb(icvalue1, icvalue2, icvalue3); //initial HSB color for lerp
    
    for (int y = 0; y < height; y++){
        for (int x = 0; x <width; x++){
            
            //position the meshes to the right side so that I can put text for private code
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
    arduino.connect("/dev/cu.usbmodem14401" , 57600);
    ofAddListener(arduino.EInitialized, this, &ofApp::setupArduino);
    bSetupArduino = false;
    
    resetGenerator = false;
    buttonPressed = false;
    mouseEnter = false;
   
    swingtime = 200000; // to prevent initiating the process when first running the code
    endtime = 91000; //end time of the full process

    
}

//--------------------------------------------------------------
void ofApp::update(){

    
    if(timeflow==true){
        //the whole process is based on timeflow. Stores time in Milliseconds when pressing the button
        swingtime = ofGetElapsedTimeMillis();
        
    }
    
    if(resetGenerator==true){
        swingtime = endtime; //resets Mesh
        timeflow = true; //stores time Milliseconds to swingtime variable
        ofResetElapsedTimeCounter(); //resets Elapsed time to start new timeflow
        snapCounter = 0; //resets screen save time
        
        
        //clears vector data of previous user. Also prevent over storing during exhibition
        oFvec1.clear();
        oFvec2.clear();
        oFvec3.clear();
        
        
        //Adjustment for variation. Random generated numbers for private code 1B,2B,3B when everytime pressing the button.
        randNum1 = ofRandom(0,99);
        randNum2 = ofRandom(0,99);
        randNum3 = ofRandom(0,99);
        
        //another temporary random generated numbers to use when sensor has not detected anything or goes over expected values if when having errors.
        tempVal1 = ofRandom(0,99);
        tempVal2 = ofRandom(0,99);
        tempVal3 = ofRandom(0,99);
        
        
        //resets Minimum values from previous user. Sensor values decreases when it detects hall effects, so minimum values from each sensors are used to identify different movement of the pendulum that each users have made.
        SensorMin1 = 0;
        SensorMin2 = 0;
        SensorMin3 = 0;
    }
    
    updateArduino(); //call Arduino
    
    if(buttonPressed==true){
        
        
        //stores sensor values to a vector during detecting time
        oFvec1.emplace_back(hallSensorinput1);
        oFvec2.emplace_back(hallSensorinput2);
        oFvec3.emplace_back(hallSensorinput3);
        
        //sort the elements in vector by ascending order to get minimum value
        ofSort(oFvec1);
        ofSort(oFvec2);
        ofSort(oFvec3);
        
        //pass the minimum value to SensorMin variable to use as a private code calculation
        SensorMin1 = oFvec1[0];
        SensorMin2 = oFvec2[0];
        SensorMin3 = oFvec3[0];
        
        
    }
    
    
    //1000 Milliseconds is 1 second. Give 4 seconds to the users to make the movement before starting the process
    if(swingtime >= 4000){
        buttonPressed = true;
    }
    
    
    //stop the detecting process to fix the minimum values and to not slow down the computer when visualizing
    if(swingtime>= 16000){
        buttonPressed = false;
    }
    
    
    //each magnetic hall sensors have slightly different default values according to the low quality. In this case, sensor 1,2,3 have default values of 545,522,529. The sensor value decreases when detecting the hall effect as I am using S direction. Subtracting default value and minimum value is to create range of values. mapVal has range of 0~60 as the maximum detecting value that sensor can have for installation setup is 60.
    mapVal1 = 545 - SensorMin1;
    mapVal2 = 522 - SensorMin2;
    mapVal3 = 529 - SensorMin3;
 
    
    //map the values to numbers between 0~99. 60 divide because the max range is 60
    privateCode1A = mapVal1*(99/60);
    privateCode2A = mapVal2*(99/60);
    privateCode3A = mapVal3*(99/60);
    
    
    //safety code for going below or over the range and use temporary random number. Default values slightly changes within 1 or 2 so I have set up to activate safety code when it is lower than 3 which is when the sensor did not detect anything.
    if(mapVal1 >60 || 3>mapVal1){
   
        privateCode1A = tempVal1;
    }
    
    if(mapVal2 >60 || 3>mapVal2){
        privateCode2A = tempVal2;
    }
    
    if(mapVal3 >60 || 3>mapVal3){
        privateCode3A = tempVal3;
    }
  
    privateCode1B = randNum1; //Adjustment values
    privateCode2B = randNum2;
    privateCode3B = randNum3;
  
    
    ofColor newColor1,lerpColor1;
    ofColor newColor2,lerpColor2;
    ofColor newColorF,lerpColorF;
    
    ofVec3f newPosition1, oldPosition1, lerpPosition1;
    ofVec3f newPosition2, oldPosition2, lerpPosition2;
    ofVec3f newPositionF, oldPositionF, lerpPositionF;

    
    
    
    //add values in time to maximise the noise difference. Like a butterfly effect, time should be added to see maximised change of initial conditions
    float time = ofGetElapsedTimeMillis()/100.0 + privateCode1B*300;
    int i=0;
    
    if(perlinMesh==true){
        

        inc= inc + 0.00006; //increment for position lerp
        inc2= inc2 + 0.005; //increment for color lerp
        

        
        //prevent from going over max lerp value. position disappears and color becomes white when it goes over 1.0
        if(inc >= 1.0){
        inc = 1.0;
        }
        if(inc2 >= 1.0){
        inc2 = 1.0;
        }
        
        
        
        //By testing out visually, I have set range of maximum and minimum values of noise value and position to hold the mesh in the 300 200 rectangle frame when seeing through orthographic mode. NoiseVal1A, NoiseVal2A, NoiseVal3A is the amount how much dynamic of the pattern will be,  NoiseVal1B and  NoiseVal2B is the position where it stays. The values are converted from private code which is in between 0~99 to the range I have set throughout testing. NoiseVal3A does not have position mapvalue because it is the background mesh that is only affected by z values.
        
        NoiseVal1A = ofMap(privateCode1A, 0, 99, 100, 320);
        NoiseVal1B = ofMap(privateCode1B, 0, 99, 115, 125);
        
        NoiseVal2A = ofMap(privateCode2A, 0, 99, 50, 180);
        NoiseVal2B = ofMap(privateCode2B, 0, 99, 70, 90);
        
        NoiseVal3A = ofMap(privateCode3A, 0, 99, 0, 20);
        
        
       
        for (int y = 0; y<height; y++){
            for (int x=0; x<width; x++){
        
                //gets old position and new position then display lerp position and color
                //sensor values affect amount of dynamic of the noise values which will be the shape of the pattern, saturation of the colors.
                //random adjustment values affect the position of noise pattern in the frame and hue of the colors.
                
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
                mesh1Lv3 =250;
                
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
                mesh2Lv3 =250;
                
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
                meshFLv2 =ofMap(newPositionF.z, 0, (35+NoiseVal3A), 0 ,  255);
                meshFLv3 =255;
                
                newColorF.setHsb(meshFLv1,meshFLv2,meshFLv3);
                
                MeshF.setVertex(i, lerpPositionF);
                MeshF.setColor(i, newColorF);
                
                
                i++;
            }
        }
    }
    
    
    if(perlinMesh == true){
        snapCounter = snapCounter +1; // time counter when to save screen
    }
    if(snapCounter == 1170){
        // saves the image of screen with name of gift 0,1,2,,, just before printing and resets counter for next user
        ofSaveScreen(ofToString(fileNum)+"gift.png");
        fileNum=fileNum+1;
        snapCounter = 0;
      }
    
    
    if(swingtime >= 16000){
        
        //set detecting time for 12 seconds, after fixing the min val, start visual process
        perlinMesh = true;
    }

    if(swingtime >= 19000){
        cam.setPosition(0, 0, 610);
        cam.setTarget(orthoTarget);
        cam.enableOrtho();
    }
    
    if(swingtime >= 56000){
        //printing starts and the moving image stops and become a fabric sample
        perlinMesh = false;
    }
    

    if(swingtime >= endtime){  //end of the process and resets everything to default mesh
        
        cam.setPosition(-100, 700, 250);
        cam.setTarget(target);
        cam.disableOrtho();
      
  
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
    
    ofRotateZ(90); //display is designed for vertical screen set for exhibition
    
    int dpVal1 = privateCode1A;
    int dpVal2 = privateCode1B;
    int dpVal3 = privateCode2A;
    int dpVal4 = privateCode2B;
    int dpVal5 = privateCode3A;
    int dpVal6 = privateCode3B;
    int dpRand = ofRandom(11,99); //no use of the values but to show changing numbers to let audience know the sensor detecting process is going on

    string displayText1 = ofToString(dpVal1);
    string displayText2 = ofToString(dpVal2);
    string displayText3 = ofToString(dpVal3);
    string displayText4 = ofToString(dpVal4);
    string displayText5 = ofToString(dpVal5);
    string displayText6 = ofToString(dpVal6);
 
    
    //when the numbers of private code on the screen changes during the detecting process, the length of text changes as the width of numbers below 10 and over 10 is different. So add 0 when the number is below 10 to prevent messy length changes of the text
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
  
    
    
   //when default mode displays all 0s. When buttom pressed, displays random changing numbers to let audience know its processing. Pass the sensor values and adjustment values to the string when the detecting process is done and show private code.
    msg= "[00,00,00,00,00,00]";
  
    if(swingtime >= 0 && swingtime <= 16000){
        msg= "["+ofToString(dpRand)+","+ofToString(dpRand)+","+ofToString( dpRand)+","+ofToString(dpRand)+","+ofToString(dpRand)+","+ofToString(dpRand)+"]";
        
    }else if(swingtime > 16000 && swingtime <= endtime){
        msg= "["+displayText1+","+displayText2+"," +displayText3+"," +displayText4+"," +displayText5+"," +displayText6+"]";
    }else{
        msg= "[00,00,00,00,00,00]";
    }
    
 
    font.drawString(msg, -399, 40);
    
    
    //below the private code on the screen show text of each process to help understand the process for the audience.
    if(swingtime >= 0 && swingtime <= 56000){

        smallfont.drawString("-Processing-", -209,130);
    }else if(swingtime >= 56000 && swingtime <= endtime){
    
        smallfont.drawString("-Printing-", -173, 130);
    }else{
    
        smallfont.drawString("-Press Button-", -245, 130);
  
    }
    
    
    
    
    ofPushStyle();
    
    ofSetColor(0,0,0,180);
    pixelFont.drawString(ofToString(swingtime),-540,-1435);
    pixelFont.drawString(ofToString(snapCounter),-450,-1435);
    pixelFont.drawString("input1:" + ofToString(SensorMin1),-540,-1410);
    pixelFont.drawString("input2:" + ofToString(SensorMin2),-540,-1385);
    pixelFont.drawString("input3:" + ofToString(SensorMin3),-540,-1360);
    
   // pixelFont.drawString("Sensor1:" + ofToString(hallSensorinput1),-540,-1310);
   // pixelFont.drawString("Sensor2:" + ofToString(hallSensorinput2),-540,-1280);
   // pixelFont.drawString("Sensor3:" + ofToString(hallSensorinput3),-540,-1250);
    
    if(!bSetupArduino){
        pixelFont.drawString("!Arduino not ready \n",-540,-1460);
    }else{
        pixelFont.drawString("!Arduino: On \n",-540,-1460);
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
  
    //if the button is pressed, activate resetGenerator bool to start process
    if(arduino.getDigital(8)){
        
        resetGenerator = true;

    }else{
        resetGenerator = false;
       
    }
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    //any of the keys does not function for the project. Just for testing out. Press p to test out the project without using Arduino.
    switch(key) {
    
case 'o':
            
    cam.getOrtho() ? cam.disableOrtho() : cam.enableOrtho();

    break;
case 'f':
    ofToggleFullscreen();

    break;
            
case 's':
    ofSaveScreen(ofToString(fileNum)+"gift.png");
    fileNum=fileNum+1;

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

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //practice note
 //difference between array and vector: array stores during the compile in stack, vector stores during the runtime in hip. In my case, vector is appropriate as the elements will need to be deleted and added during the runtime.
    
//std::minmax_element(begin(v), end(v)); can output minimum and maximum elements
    
    //  vector<int> vi = { 5, 3, 4, 4, 3, 5, 3 };
    //  pair<vector<int>::iterator, vector<int>::iterator> mnmx;
      
    //  mnmx = minmax_element(vi.begin(), vi.end());
    
//    std::vector<int> nums{0,1,2,3,4,5};
//    nums.emplace_back(5);
//    for(std::size_t idx=0; idx<nums.size(); idx++)
//    {
//        std::cout << nums[idx] << std::endl;
//    }
    
//array<int,100> nums; 100 arrays
// vector<int> nums(1000,1); put 1 into 1000 spaces
    
//  vector<int> nums{0,1,2,3,4,5};
// nums.emplace_back(); constructs space and add at back
// nums.push_back(); add at back
// nums.pop_back(); delete back
// nums.emplace(nums.begin(),3); put 3 in first place but it is constructing a space and adds the number so if the size of container was 3, it becomes 4
// nums.erase(nums.begin()); delete first number. All numbers are moved to front by one space so end space with nothing in it exists after deleting. So have to use function with removing end space.
// nums.erase(remove(nums2.begin(), nums2.end(),0),nums2.end())
// nums.reserve(100); secure 100 spaces
    
 
//  for(size_t idx=0; idx<nums.size(); idx++)
//  {
//      cout << nums[idx] << endl;
//  }
    
//  equals to above
    
//  for(const int & num : nums)
//  {
//      cout << num << endl;
//  }
      
// vector<int> nums2 {0,1,0,1,0,1};
//num2.erase( num2.begin()+1); = 00101
//num2.erase( num2.begin(), num2.begin()+2); = 1101
    

    
    // simulating changing values like the sensor inputs
// increasing number adding
//  deque<int> d(3);
//  int mynums = 1;
//  for(int i = 0; i<20; i++){
        
//       d.push_back(mynums);
//       mynums = mynums+1;
// cout<< mynums << endl;
//      d.pop_front();
//   }
   
// random generated number adding
// int mynums = ofRandom(5,20);
//deque<int> d
// d.push_front(13);
// d.push_back(mynums);
    
//   for(int n : d){
//       cout << n << '\n';
//   }
    
//  for(int i=0; i<d.size(); i++){
//     cout<< d.at(i)<<" ";
//  }
    
    ofBackground(255);
    font.load("verdana.ttf",34);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    
        //exmperimentation of algorithm for automated activating process using sensor values
    
    // by storing three recent sensor values,in the perspective of one of the sensors n(current) n-1(previous) n-2(two times previous), the direction of movement of the pendulum can be analyzed. If the n-1 is larger than n-2, it means sensor value is increasing so the pendulum is moving towards the sensor. If n is larger than n-1, it means it is still moving towards the sensor. n will be larger than n-1 until it gets to the maximum value which is where pendulum has reached end point of the movement. When pendulum has reached the end point, it will swing back to opposite direction which is where n will be then smaller than n-1. Minimum case will be the opposite in same logic.
    //  comparing n-2 and n-1 is to detect the current status and comparing n and n-1 is to define maximum or minimum value at the turning point
    

    
    int mynums = ofRandom(1,9); //simulation of sensor value
    
    d.push_front(mynums);
    
    if(d.size() >3 ){
    d.pop_back();
    }
    
    int val1 = d[0];
    int val2 = d[1];
    int val3 = d[2];
    
 //   if(val2>val1){
 //       countN= countN+1;
 //   }
    
  //  if(val2 < val3 && val1 <val2){
  //      BoolN = false;
  //  }
  //  if(val2 < val3 && val1 >val2){
  //      BoolN = true;
  //  }
  //  if(val2 > val3 && val1 >val2){
   //     BoolN = false;
  //  }
  //  if(val2 > val3 && val1 <val2){
  //      BoolN = true;
  //  }else{
  //      BoolN = false;
  //  }
    
 //   if(val2< val3){
 //      if(val1> val2){
  //         BoolN = true;
  //     }
 //       else if(val1<val2){
 //           BoolN = false;
 //       }
 //   }
 //   else if(val2>val3){
 //       if(val1< val2){
 //           BoolN = true;
 //       }
 //       else if(val1>val2){
 //           BoolN = false;
 //       }
 //   }
    
  //  if(d[2] < d[1]){
  //      if(d[1] > d[0]){
  //          BoolN = true;
   //    }}
  //     else if(d[2] > d[1]){
  //     if(d[1] < d[0]) {
  //         BoolN = true;
  //     }}else{
  //         BoolN = false;
  //     }
    
    
    if((d[2] < d[1] && d[1] > d[0]) || (d[2] > d[1] && d[1] < d[0])){
        BoolN = true;
    }else{
        BoolN = false;
    }

    if(BoolN == true){
        countN = countN+1;  //count how many time the pendulum had been swinging, 1 count                   is half period
    }
    
    
    
    // counting half period in succession will give minimum and maximum number in the perspective of a sensor
    if(countN == 5){
        Sensor1 = val3;//storing max val
    }
    if(countN == 6){
        Sensor2 = val3;//storing min val
    }
 
      for(int i=0; i<d.size(); i++){
          cout<< d[0] << d[1] << d[2] <<'\n' << countN << '\n'<< d.size()<< '\n';
      }
    
    
    
    //if(direction > previousDirection && positiveDirectionBool == false ){
    //positiveDirectionBool = true;
    //count++;
    //}else if(direction < previousDirection && positiveDirectionBool == true){
    //positiveDirectionBool = false;
    //count++;
    //}
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(20, 20, 20);
    ofSetColor(200,200,200);
    string msg;
    msg+= ofToString(Sensor1);
    font.drawString(msg, 200, 100);
    

    string msg2;
    msg2+= ofToString(Sensor2);
    font.drawString(msg2, 100, 100);
    
    
   
    
    
    

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

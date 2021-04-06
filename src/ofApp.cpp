#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  mainScene.setup();
  mainScene.setID(1);
  fieldScene.setup();
  fieldScene.setID(2);
  currentScene = &mainScene;
  ofSetEscapeQuitsApp(true);
}

//--------------------------------------------------------------
void ofApp::update(){
    currentScene->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
  currentScene->draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  if( key == 'a'){
    if(currentScene->getID() == 1){
      currentScene = &fieldScene;
    }
    else{
      currentScene = &mainScene;
    }
  }
  currentScene->keyPressed(key);
  if(key == 'x'){
    currentScene->screenshot(&img);
  }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
  // for(int i =-50; i < 50; i ++){
  //   addNewParticle(x+i,y+i);
  // }
  currentScene->mouseDragged(x,y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
  currentScene->mousePressed(x,y);
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

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  mainScene.setup();
  mainScene.setID(1);
  fieldScene.setup();
  fieldScene.setID(2);
  gpuScene.setup();
  gpuScene.setID(3);
  currentScene = &mainScene;
  ofSetEscapeQuitsApp(true);
}

//--------------------------------------------------------------
void ofApp::update(){
    if(currentScene->getID() < 0){
      switch (currentScene->getID()) {
        case -1:
          currentScene->setID(2);
          currentScene = &mainScene;
        break;
        case -2:
          mainScene.getVectorField()->copy(fieldScene.getVectorField());
          currentScene->setID(2);
          currentScene = &mainScene;
          break;
        case -3:
          currentScene->setID(1);
          currentScene = &fieldScene;
          break;
        case -4:
          gpuScene.getVectorField()->copy(fieldScene.getVectorField());
          currentScene->setID(2);
          currentScene = &gpuScene;
          gpuScene.texturiseField();
          break;
        case -5:
          currentScene->setID(3);
          currentScene = &fieldScene;
          break;
        case -6:
          currentScene->setID(3);
          currentScene = &mainScene;
          break;
      }
    }
    currentScene->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
  currentScene->draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  if( key == 'a'){
    cout << currentScene->getID() << "\n";
    if(currentScene->getID() == 1){
      currentScene = &fieldScene;
    }
    else if(currentScene->getID() == 2){
      currentScene = &gpuScene;
    }
    else{
      currentScene = &mainScene;
    }
  }
  currentScene->keyPressed(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
  currentScene->mouseDragged(x,y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
  currentScene->mousePressed(x,y,button);
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

#include "ofApp.h"

void ofApp::addNewParticle(float x, float y){
  Particle * newParticle = new Particle(glm::vec2(x,y));
  particles.push_back(newParticle);
  // newParticle->setup(glm::vec2(x,y));
}
void ofApp::addNewParticles(float x, float y){

  addNewParticle(x, y);
  int thickness = 20/brushThickness;
  for (int i = -brushRadius; i < brushRadius; i +=thickness){
    for (int j = -brushRadius; j < brushRadius; j +=thickness){
      if(sqrt(pow(i, 2) + pow(j, 2)) < brushRadius){
        addNewParticle(x+i, y +j);
      }
    }
  }

}

//--------------------------------------------------------------
void ofApp::setup(){
  gui.setup();
  gui.add(maxParticles.setup("max particles", 100, 10, 20000));
  gui.add(brushRadius.setup("brush radius", 1, 5, 50));
  gui.add(brushThickness.setup("brush thickness", 1, 1, 20));
  vectorField.setup(ofGetWidth(),ofGetHeight(),1);
  vectorField.perlin();
}

//--------------------------------------------------------------
void ofApp::update(){
    while(particles.size() > maxParticles){
      particles.erase(particles.begin());
    }

    for( int i=0; i<particles.size(); i++){
      glm::vec2 pos = particles[i]->pos;
      glm::vec2 dir = vectorField.getVector(pos.x, pos.y);
      particles[i]->move(dir);
    }

    std::string title = std::to_string(ofGetFrameRate());
    std::string s = std::to_string(particles.size());
    std::string ss = " : ";
    title.append(ss);
    title.append(s);
    ofSetWindowTitle(title);
}

//--------------------------------------------------------------
void ofApp::draw(){
  // vectorField.draw();
  gui.draw();
  for( int i=0; i<particles.size(); i++){
    particles[i]->draw();
  }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  if( key == ' '){
    vectorField.perlin();
  }
  if(key == 'x'){
      img.grabScreen(0, 0 , ofGetWidth(), ofGetHeight());
      img.save("screenshot.jpg");
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
  addNewParticles(x,y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
  addNewParticles(x,y);
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

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofEnableAlphaBlending();

    ofSetWindowShape(width, height);

    ofSetFrameRate(30);

    resetField();

    for(int i =0; i < (width)/factor; i++){
      for(int j =0; j < (height)/factor; j++){
        Particle newParticle;
        glm::vec2 pos(ofRandom( 0, ofGetWidth()), ofRandom( 0, ofGetHeight()));
        // glm::vec2 pos(i*factor, j*factor);
        newParticle.setup(pos);
        particles.push_back(newParticle);
        ofPath newPath;
        newPath.draw(pos.x, pos.y);
        newPath.setStrokeColor( ofColor ( 255 , 255 , 255, 20 ) );
    		newPath.setFilled(false);
    		newPath.setStrokeWidth(0.01);
    		newPath.setCurveResolution(20);
        paths.push_back(newPath);
      }
  }
}

void ofApp::resetParticles(){


      for( int i=0; i<particles.size(); i++){
        particles[i].pos = particles[i].startPos;
        particles[i].duration = 0;
      }
}
void ofApp::resetPath(){


      for( int i=0; i<particles.size(); i++){
        paths[i].clear();
        // particles[i].pos = particles[i].startPos;
      }
}
void ofApp::resetField(){

  // allocate the vector field with the desired spacing
  vectorField.setup(width, height, 2);

  // create the vector field using perlin noise
  vectorField.randomize();
  // adjust the vector field by normalizing, scaling, biasing & blurring (to make it look nice)
  // vectorField.normalize();
  vectorField.scale(5);
  // vectorField.bias(0, 1);
  // vectorField.blur();
}


//--------------------------------------------------------------
void ofApp::update(){


    for( int i=0; i<particles.size(); i++){

        // particles[i].stayOnScreen();
        // if(!particles[i].isDead()){
          // glm::vec2 pos(ofRandom( 0, ofGetWidth()), ofRandom( 0, ofGetHeight()));
          // particles[i].pos = pos;
          particles[i].move(vectorField.getVectorInterpolated(particles[i].pos.x, particles[i].pos.y, ofGetWidth(), ofGetHeight()));
        // }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);

    ofSetColor(255, 255, 255);

    if(showField){
      vectorField.draw();
    }
    string s = "SPACE: clear paths\nr: reset field\nt: reset particles\np: toggle particles\nf: toggle field";
	  ofDrawBitmapString(s, 20, 20);

    for( int i=0; i<particles.size(); i++){
        if(!particles[i].isDead()){
          if(particles[i].pos.x >= 2 && particles[i].pos.y >= 2){
            //dirty check to avoid unnatural line artefacts at 0,0
            paths[i].curveTo(particles[i].pos.x, particles[i].pos.y);
          }
          if(showParticles){
            particles[i].draw();
          }
      }
      paths[i].draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  if( key == ' '){
    resetPath();
  }
  else if (key == 'r'){
    resetField();
  }
  else if (key == 't'){
    resetParticles();
  }
  else if (key == 'p'){
    showParticles = !showParticles;
  }
  else if (key == 'f'){
    showField = !showField;
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


#include "particle.h"

Particle::Particle(glm::vec2 p, float s, float swidth){
  pos = p;
  startPos = p;
  speed = s;
  // ofSetBackgroundAuto(false);
  path.draw(pos.x, pos.y);
  path.setStrokeColor( ofColor ( 255 , 255 , 255, 20 ) );
  path.setFilled(false);
  path.setStrokeWidth(swidth);
  path.setCurveResolution(1);
}
Particle::~Particle(){
    path.clear();
    delete [] &path;
}

void Particle::move(glm::vec2 dir){

    if(!dead){
      if(glm::length(dir) > 0.1){
        pos += dir*speed;
        path.curveTo(pos.x, pos.y);
      }
      else{
        path.simplify();
        path.tessellate();
        dead = true;
      }
  }
}

void Particle::draw(){
    ofSetColor(255, 255, 255);
    // ofDrawCircle(pos.x, pos.y, .75);
    path.draw();
}

void Particle::stayOnScreen(){
    if( pos.x < 0 ) pos.x = ofGetWidth();
    if( pos.x >= ofGetWidth() ) pos.x = 0;
    if( pos.y < 0 ) pos.y = ofGetHeight();
    if( pos.y >= ofGetHeight() ) pos.y = 0;
}

bool Particle::isOffScreen(){
    if( pos.x <= 0 || pos.x >= ofGetWidth() || pos.y <= 0 || pos.y >= ofGetHeight() ){
        return true;
    }

    return false;
}

bool Particle::isDead(){
    return isOffScreen() || dead;
}


#include "particle.h"

Particle::Particle(glm::vec2 p, float s, float swidth, float d, float size){
  startTime = ofGetElapsedTimef();
  speed = s;
  strokeWidth = swidth;
  duration = d;
  radius = size;
  pos = p;
  startPos = p;
  // ofSetBackgroundAuto(false);
  path.draw(pos.x, pos.y);
  path.setStrokeColor(trailColour);
  path.setFilled(false);
  path.setStrokeWidth(swidth);
  path.setCurveResolution(1);
}
Particle::~Particle(){
    path.clear();
    delete [] &colour;
    delete [] &trailColour;
    delete [] &path;
}


void Particle::setColour(int r, int g, int b){
  colour.r = r;
  colour.g = g;
  colour.b = b;
  ofSetColor(colour);
}

void Particle::setColour(ofColor * col){
  colour.r = col->r;
  colour.g = col->g;
  colour.b = col->b;
  ofSetColor(colour.r, colour.g, colour.b);
}


void Particle::setTrailColour(int r, int g, int b){
  trailColour.r = r;
  trailColour.g = g;
  trailColour.b = b;
  path.setStrokeColor(trailColour);
}

void Particle::setTrailColour(ofColor * col){
  trailColour.r = col->r;
  trailColour.g = col->g;
  trailColour.b = col->b;
  path.setStrokeColor(trailColour);
}


void Particle::setOpacity(int a){
  colour.a = a;
  ofSetColor(colour.r, colour.g, colour.b, colour.a);
}

void Particle::setTrailOpacity(int a){
  trailColour.a = a;
  path.setStrokeColor(trailColour);
}

void Particle::setSpeed(float s){
  speed = s;
}

void Particle::setStrokeWidth(float s){
  strokeWidth = s;
  path.setStrokeWidth(strokeWidth);
}

glm::vec2 Particle::getPosition(){
  return pos;
}


void Particle::move(glm::vec2 dir){

    if(!isDead()){
      bool condition;
      if(duration == 0){
        condition = glm::length(dir) > 0.01; //stops when vecolity magnitude low
      }
      else{
        condition = ofGetElapsedTimef() < startTime + duration;
      }
      if(condition){
        pos += dir*speed;
        path.curveTo(pos.x, pos.y);
      }
      else{
        path.simplify();
        // path.tessellate();
        dead = true;
      }
  }
}

void Particle::draw(){
  if(!dead){
    ofSetColor(colour);
    ofDrawCircle(pos.x, pos.y, radius);
  }
}

void Particle::drawTrail(){
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

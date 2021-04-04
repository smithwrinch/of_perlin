#include "mainScene.h"

void MainScene::addNewParticle(float x, float y){
  Particle * newParticle = new Particle(glm::vec2(x,y));
  particles.push_back(newParticle);
  // newParticle->setup(glm::vec2(x,y));
}
void MainScene::addNewParticles(float x, float y){

  addNewParticle(x, y);
  int thickness = 100/brushThickness;
  for (int i = -brushRadius; i < brushRadius; i +=thickness){
    for (int j = -brushRadius; j < brushRadius; j +=thickness){
      if(sqrt(pow(i, 2) + pow(j, 2)) < brushRadius){
        addNewParticle(x+i, y +j);
      }
    }
  }

}


void MainScene::setup(){
  id = 1;
  gui.setup();
  gui.add(maxParticles.setup("max particles", 100, 10, 20000));
  gui.add(brushRadius.setup("brush radius", 1, 5, 100));
  gui.add(brushThickness.setup("brush thickness", 1, 1, 50));
  vectorField.setup(ofGetWidth(),ofGetHeight(),1);
  vectorField.perlin(0.0077);
}
void MainScene::draw(){
  gui.draw();
  for( int i=0; i<particles.size(); i++){
    particles[i]->draw();
  }
}
void MainScene::update(){
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

void MainScene::mouseDragged(int x, int y){
  addNewParticles(x,y);
}

//--------------------------------------------------------------
void MainScene::mousePressed(int x, int y){
  addNewParticles(x,y);
}

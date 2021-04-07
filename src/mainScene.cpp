#include "mainScene.h"

void MainScene::addNewParticle(float x, float y){
  Particle * newParticle = new Particle(glm::vec2(x,y), particleSpeed, avgLineWidth, particleLifetime);
  newParticle->setColour(particleColour.get().r, particleColour.get().g, particleColour.get().b);
  newParticle->setOpacity(particleColour.get().a);
  newParticle->setTrailColour(particleTrailColour.get().r, particleTrailColour.get().g, particleTrailColour.get().b);
  newParticle->setTrailOpacity(particleTrailColour.get().a);
  particles.push_back(newParticle);
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

void MainScene::loadVectorField(){
  loading = true;
  ofFileDialogResult result = ofSystemLoadDialog("Load file");
  if(result.bSuccess) {
    string path = result.getPath();
    // load your file at `path`
    vectorField.loadFromFile(path);
    loading = false;
    cout << "loaded" << "\n";
  }
}

void MainScene::toggleVectorField(bool & value){
  showField = !showField;
}
void MainScene::clearParticles(){
  particles.clear();
}


void MainScene::saveImage(){
  screenshotting = true;
  MainScene::screenshot(&img);
  screenshotting = false;
}

void MainScene::screenshot(ofImage * img){
  BaseScene::screenshot(img);
}
// bool MainScene::toggleParticle(){
//   return true;
// }
// bool MainScene::toggleParticleTrail(){
//   return true;
// }

void MainScene::setup(){
  id = 1;
  gui.setup("(g) to toggle");
  gui.add(brushRadius.setup("brush radius", 1, 5, 100));
  gui.add(brushThickness.setup("brush thickness", 1, 1, 50));
  gui.add(resetButton.setup("clear (c)"));
  resetButton.addListener(this, &MainScene::clearParticles);
  gui.add(saveImageButton.setup("save image (x)"));
  saveImageButton.addListener(this, &MainScene::saveImage);

  gui.add(particleGroup.setup("particles"));
  particleGroup.add(maxParticles.setup("max particles", 100, 0, 50000));
  particleGroup.add(particleLifetime.setup("particle lifetime", 0, 0, 20));
  particleGroup.add(particleSpeed.setup("particle speed", 10, 0, 10));
  particleGroup.add(showParticleButton.setup("show particle", true));
  particleGroup.add(particleColour.set("particle color", ofColor(255, 255, 255, 255)));

  particleGroup.add(showTrailButton.setup("show particle path", true));
  particleGroup.add(avgLineWidth.setup("particle path width", 1, 1, 10));
  particleGroup.add(particleTrailColour.set("particle path color", ofColor(255, 255, 255, 20)));

  gui.add(vectorFieldGroup.setup("vector field"));
  gui.add(loadVectorFieldButton.setup("load main (l)"));
  gui.add(toggleVectorFieldButton.setup("toggle field (f)", false));
  gui.add(createVectorFieldButton.setup("create field (a)"));
  loadVectorFieldButton.addListener(this, &MainScene::loadVectorField);
  toggleVectorFieldButton.addListener(this, &MainScene::toggleVectorField);
  createVectorFieldButton.addListener(this, &MainScene::createVectorField);

  // fbo.allocate(1080, 800, GL_RGBA, 12);

  vectorField.setup(3);
  vectorField.perlin(0.0077);


}
void MainScene::draw(){
  if(showField){
    vectorField.draw();
  }
  // fbo.begin();
  // ofClear(255,255,255, 0);

  for( int i=0; i<particles.size(); i++){
    if(showParticleButton){
      particles[i]->draw();
    }
    if(showTrailButton){
      particles[i]->drawTrail();
    }
  }
  if(!screenshotting){
    ofNoFill();
    ofDrawCircle(ofGetMouseX(), ofGetMouseY(), brushRadius);
    ofFill();
    if(guiOn){
      gui.draw();
    }
  }
  // fbo.end();
  // fbo.draw(0,0);
}
void MainScene::update(){
  while(particles.size() > maxParticles){
    particles.erase(particles.begin());
  }

  for( int i=0; i<particles.size(); i++){
    glm::vec2 pos = particles[i]->getPosition();
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

VectorField * MainScene::getVectorField(){
  return &vectorField;
}

void MainScene::createVectorField(){
  BaseScene::setID(-3);
}

void MainScene::mouseDragged(int x, int y){
  addNewParticles(x,y);
}

//--------------------------------------------------------------
void MainScene::mousePressed(int x, int y){
  addNewParticles(x,y);
}

//--------------------------------------------------------------
void MainScene::keyPressed(int key){
  cout << key << "\n";
   switch (key){
     case 'f':
      cout << "hasdfhjksdf" << "\n";
      toggleVectorField(showField);
     break;
     case 'c':
      clearParticles();
     break;
     case 'l':
      loadVectorField();
     break;
     case 'g':
      guiOn = !guiOn;
     break;
   }
}

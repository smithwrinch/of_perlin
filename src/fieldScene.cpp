#include "fieldScene.h"

void FieldScene::setup(){
  gui.setup();
  // gui.add(width.setup("width", ofGetWidth(), 1, ofGetWidth()));
  // gui.add(height.setup("height", ofGetHeight(), 1, ofGetHeight()));
  gui.add(spacing.setup("scale", 6, 1, 10));


  gui.add(saveGroup.setup("save/load"));
  saveGroup.add(saveText.setup("enter fname here", "s"));
  saveGroup.add(saveButton.setup("save field"));
  saveButton.addListener(this, &FieldScene::saveField);
  saveGroup.add(loadButton.setup("load field"));
  loadButton.addListener(this, &FieldScene::loadField);


  gui.add(perlinGui.setup("perlin"));
  // perlinButton.addListener(this, &FieldScene::perlin);

  perlinGui.add(perlinSpacing.setup("scale", 0.0578648, 0.0005, 0.1));
  perlinGui.add(perlinParameterX.setup("x parameter", 10, 0, 100));
  perlinGui.add(perlinParameterY.setup("y parameter", 10, 0, 100));

  perlinGui.add(randomiseButton.setup("generate"));
  randomiseButton.addListener(this, &FieldScene::randomise);
  // perlinGui.add(backButton.setup("go back"));
  // backButton.addListener(this, &FieldScene::goBack);


  gui.add(normaliseButton.setup("normalise"));
  normaliseButton.addListener(this, &FieldScene::normalise);
  gui.add(resetButton.setup("reset"));
  resetButton.addListener(this, &FieldScene::reset);
  gui.add(sendToMainButton.setup("send to main"));
  sendToMainButton.addListener(this, &FieldScene::sendToMain);
  gui.add(goToMainButton.setup("go back to main (a)"));
  goToMainButton.addListener(this, &FieldScene::goToMain);

  vectorField.setup(1);
  vectorField.uniform(glm::vec2(1,1));
  // vectorField.save();
}


void FieldScene::saveField(){
  vectorField.save(saveText);
}
void FieldScene::loadField(){
  loading = true;
  ofFileDialogResult result = ofSystemLoadDialog("Load file");
  if(result.bSuccess) {
    string path = result.getPath();

    cout << path << "\n";
    // load your file at `path`
    minSpacing = vectorField.loadFromFile(path);
    // spacing.setMin(minSpacing);
    loading = false;
    cout << "loaded" << "\n";
    cout << spacing << "\n";

  }
}

void FieldScene::sendToMain(){
  cout << "Sending to main scene" << "\n";
  BaseScene::setID(-2);
}

void FieldScene::goToMain(){
  cout << "Going to main scene" << "\n";
  BaseScene::setID(-1);
  cout << BaseScene::getID() << "\n";
}

void FieldScene::reset(){
  vectorField.setSpacing(1);
  vectorField.uniform(glm::vec2(1,0));
  minSpacing = 1;
}

void FieldScene::normalise(){
  vectorField.normalise();
}

void FieldScene::randomise(){
  vectorField.perlin(perlinSpacing, perlinParameterX, perlinParameterY);
}

void FieldScene::update(){
  ofSetWindowTitle("Vector Field Creator");

  vectorField.setSpacing(spacing);
}

void FieldScene::draw(){
    vectorField.draw();
    if(!loading){
      gui.draw();
    }
}


VectorField * FieldScene::getVectorField(){
  return &vectorField;
}

void FieldScene::setVectorField(VectorField * field){
  vectorField = *field;
}

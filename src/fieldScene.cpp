#include "fieldScene.h"

void FieldScene::setup(){
  gui.setup();
  // gui.add(width.setup("width", ofGetWidth(), 1, ofGetWidth()));
  // gui.add(height.setup("height", ofGetHeight(), 1, ofGetHeight()));
  // gui.add(dimsButton.setup("Apply dimensions"));
  // dimsButton.addListener(this, &FieldScene::applyDims);
  gui.add(spacing.setup("spacing", 1, 1, 10));


  gui.add(saveGroup.setup("save/load"));
  saveGroup.add(saveText.setup("save.xml", "s"));
  saveGroup.add(saveButton.setup("save field"));
  saveButton.addListener(this, &FieldScene::saveField);
  // saveGroup.add(loadText.setup("load.xml", "s"));
  saveGroup.add(loadButton.setup("load field"));
  loadButton.addListener(this, &FieldScene::loadField);


  gui.add(perlinGui.setup("perlin"));
  // perlinButton.addListener(this, &FieldScene::perlin);

  perlinGui.add(perlinSpacing.setup("spacing", 0.0001, 0.0005, 0.01));
  perlinGui.add(randomiseButton.setup("randomly generate"));
  randomiseButton.addListener(this, &FieldScene::randomise);
  // perlinGui.add(backButton.setup("go back"));
  // backButton.addListener(this, &FieldScene::goBack);

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
    // load your file at `path`
    minSpacing = vectorField.loadFromFile(path);
    spacing.setMin(minSpacing);
    loading = false;
    cout << "loaded" << "\n";
  }
}

void FieldScene::reset(){
  // TODO: add vector field reset
  // add vector field normalise
  // add affordance st can just get vf from other window without loading
  // make line width do something
  // add vector field functionality to affect line width
  // add particle lifetime as parameter
  // add colour pickers
}

void FieldScene::randomise(){
  vectorField.perlin(perlinSpacing);
}

void FieldScene::update(){
  ofSetWindowTitle("Create Vector");

  vectorField.setSpacing(spacing);
}

void FieldScene::draw(){
    vectorField.draw();
    if(!loading){
      gui.draw();
    }
}

#include "fieldScene.h"

void FieldScene::setup(){
  gui.setup();
  // gui.add(width.setup("width", ofGetWidth(), 1, ofGetWidth()));
  // gui.add(height.setup("height", ofGetHeight(), 1, ofGetHeight()));
  gui.add(spacing.setup("scale", 6, 1, 20));
  gui.add(brushRadius.setup("brush radius", 0, 0, 400));
  gui.add(effect.setup("smudge strength (right)", 1, -1, 1));
  gui.add(strength.setup("source strength (left)", 1, -1, 1));


  gui.add(saveGroup.setup("save/load"));
  saveGroup.add(saveText.setup("fname = ", ""));
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


  gui.add(eqnGui.setup("custom equation"));
  eqnGui.add(eqnLabel.setup("(middle mouse)","apply with brush"));
  eqnGui.add(eqnXText.setup("x = ", ""));
  eqnGui.add(eqnYText.setup("y = ", ""));
  eqnGui.add(eqnButton.setup("apply to all"));
  eqnButton.addListener(this, &FieldScene::applyEqn);
  eqnGui.add(eqnBrushButton.setup("apply to brush"));
  eqnBrushButton.addListener(this, &FieldScene::applyBrushEqn);



  gui.add(smoothKernel.setup("smooth kernel", 3, 3, 9));
  gui.add(smoothSigma.setup("smooth sigma", 1, 0.1, 3));
  gui.add(smoothStrength.setup("smooth strength", 1, 1, 3));
  gui.add(smoothButton.setup("smooth"));
  smoothButton.addListener(this, &FieldScene::smooth);
  gui.add(normaliseButton.setup("normalise"));
  normaliseButton.addListener(this, &FieldScene::normalise);
  gui.add(divideScalar.setup("scalar factor", 1, 0, 2));
  gui.add(normaliseScalarButton.setup("divide"));
  normaliseScalarButton.addListener(this, &FieldScene::normaliseWrtScalar);
  gui.add(clearButton.setup("clear"));
  clearButton.addListener(this, &FieldScene::clear);
  gui.add(resetButton.setup("reset"));
  resetButton.addListener(this, &FieldScene::reset);
  gui.add(sendToGPUButton.setup("send to gpu"));
  sendToGPUButton.addListener(this, &FieldScene::sendToGPU);
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

void FieldScene::sendToGPU(){
  cout << "Sending to gpu scene" << "\n";
  BaseScene::setID(-4);
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

void FieldScene::clear(){
  vectorField.setAll(0,0);
}

void FieldScene::smooth(){
  vectorField.blur(smoothKernel, smoothSigma, smoothStrength);
}

void FieldScene::normalise(){
  vectorField.normalise();
}
void FieldScene::normaliseWrtScalar(){
  vectorField.normalise(divideScalar);
}

void FieldScene::randomise(){
  vectorField.perlin(perlinSpacing, perlinParameterX, perlinParameterY);
}

void FieldScene::applyEqn(){
  vectorField.setVector(eqnXText, eqnYText, 0, 0, 0);
  eqnX = eqnXText;
  eqnY = eqnYText;
}

void FieldScene::applyBrushEqn(){
  eqnX = eqnXText;
  eqnY = eqnYText;
}


void FieldScene::update(){
  ofSetWindowTitle("Vector Field Creator");

  vectorField.setSpacing(spacing);
}

void FieldScene::draw(){
    if(!loading){
      gui.draw();
    }
    vectorField.draw();
    ofNoFill();
    ofDrawCircle(ofGetMouseX(), ofGetMouseY(), brushRadius);
    ofFill();
}


VectorField * FieldScene::getVectorField(){
  return &vectorField;
}

void FieldScene::setVectorField(VectorField * field){
  vectorField = *field;
}

void FieldScene::mouseDragged(int x, int y, int button){

  switch(button){
    case 0:
      vectorField.addSink(x,y,brushRadius,float(strength));
    break;
    case 1:
      vectorField.addEqnBrush(eqnX, eqnY, x,y,brushRadius);
    break;
    case 2:
    vectorField.addMagnet(x,y,brushRadius,float(effect));
    break;
  }
}

//--------------------------------------------------------------
void FieldScene::mousePressed(int x, int y, int button){
  lastX = x;
  lastY = y;
  switch(button){
    case 0:
      vectorField.addSink(x,y,brushRadius,float(strength));
    break;
    case 1:
      vectorField.addEqnBrush(eqnX, eqnY, x,y,brushRadius);
    break;
    case 2:
      vectorField.addMagnet(x,y,brushRadius,float(effect));
    break;
  }
}

void FieldScene::mouseReleased(int x, int y, int button){
  // if(button ==2 ){
  //   vectorField.addMagnet(x,y,brushRadius, float(effect));
  // }
  // else if (button == 0){
  //
  //   vectorField.addSink(x,y,brushRadius,float(strength));
  // }
}

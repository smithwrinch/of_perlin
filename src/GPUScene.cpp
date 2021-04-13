#include "GPUScene.h"


void GPUScene::setupGui(){
  gui.setup();
  gui.add(brushRadius.setup("brush radius", 0, 0, 400));
  gui.add(timeStep.setup("particle speed", 0.005, 0.0001, 0.01));
  gui.add(particleSize.setup("particle size", 30., 10., 100.));
  gui.add(particleColour.set("particle color", ofColor(255, 255, 255, 255)));
  gui.add(loadButton.setup("load field"));
  loadButton.addListener(this, &GPUScene::loadVectorField);
  gui.add(loadParticleButton.setup("load particle texture"));
  loadParticleButton.addListener(this, &GPUScene::loadParticleTexture);
  gui.add(playButton.setup("play/pause"));
  playButton.addListener(this, &GPUScene::togglePlay);
}

void GPUScene::texturiseField(){
  vectorField.convertToImage();
  image.load("temp.png");
  image.resize(800,800);
  ofSaveImage(image.getPixels(), "temp2.png", OF_IMAGE_QUALITY_BEST);
}

void GPUScene::resetPositions(){
  for (int x = 0; x < textureRes; x++){
      for (int y = 0; y < textureRes; y++){
          int i = textureRes * y + x;
          pos[i*3 + 0] = -100.; //x*offset;
          pos[i*3 + 1] = -100.; //y*offset;
          pos[i*3 + 2] = 0.0;
      }
  }
  posPingPong.src->getTexture().loadData(pos.data(), textureRes, textureRes, GL_RGB);
  posPingPong.dst->getTexture().loadData(pos.data(), textureRes, textureRes, GL_RGB);
}


void GPUScene::addParticle(float x, float y){
  pos[activeParticles*3] = (x-offsets.x)/width;
  pos[activeParticles*3 + 1] = (y-offsets.y)/height;
  posPingPong.src->getTexture().loadData(pos.data(), textureRes, textureRes, GL_RGB);
  // posPingPong.dst->getTexture().loadData(pos.data(), textureRes, textureRes, GL_RGB);
  activeParticles++;
}

void GPUScene::loadVectorField(){
  ofFileDialogResult result = ofSystemLoadDialog("Load file");
  if(result.bSuccess) {
    string path = result.getPath();
    vectorField.loadFromFile(path);
    cout << "loaded" << "\n";
  }
  texturiseField();
}

void GPUScene::loadParticleTexture(){
}

void GPUScene::togglePlay(){
}


void GPUScene::setup(){
  setupGui();
  showField = false;
  vectorField.setup(3);
  vectorField.perlin(0.0077);
  offsets = vectorField.getOffset();
  texturiseField();
  // particleSize = 30.0f;
  // timeStep = 0.005f;
  numParticles = MAX_PARTICLES;
  activeParticles= 0;
  width = 800;
  height = 800;
  // gui.setup("(g) to toggle");
  ofSetWindowTitle("GPU scene");
  updatePos.load("shaders/passthru.vert","shaders/posUpdate.frag");// shader for updating the texture that store the particles POSITION on RG channels
  updateVel.load("shaders/passthru.vert","shaders/velUpdate.frag");// shader for updating the texture that store the particles VELOCITY on RG channels

  // Frag, Vert and Geo shaders for the rendering process of the spark image
  updateRender.setGeometryInputType(GL_POINTS);
  updateRender.setGeometryOutputType(GL_TRIANGLE_STRIP);
  updateRender.setGeometryOutputCount(6);
  updateRender.load("shaders/render.vert","shaders/render.frag","shaders/render.geom");


  // Seting the textures where the information ( position and velocity ) will be
  textureRes = (int)sqrt((float)numParticles);
  numParticles = textureRes * textureRes;

  // 1. Making arrays of float pixels with position information
  pos.resize(numParticles*3);
  for (int x = 0; x < textureRes; x++){
      for (int y = 0; y < textureRes; y++){
          int i = textureRes * y + x;
          pos[i*3 + 0] = -100.0; //x*offset;
          pos[i*3 + 1] = -100.0; //y*offset;
          pos[i*3 + 2] = 0.0;
      }
  }
  // Load this information in to the FBO's texture
  posPingPong.allocate(textureRes, textureRes, GL_RGB32F);
  posPingPong.src->getTexture().loadData(pos.data(), textureRes, textureRes, GL_RGB);
  posPingPong.dst->getTexture().loadData(pos.data(), textureRes, textureRes, GL_RGB);
  //
  //
  // // 2. Making arrays of float pixels with velocity information and the load it to a texture
  // vector<float> vel(numParticles*3);
  // for (int i = 0; i < numParticles; i++){
  //     vel[i*3 + 0] = 0.0;
  //     vel[i*3 + 1] = 0.0;
  //     vel[i*3 + 2] = 1.0;
  // }
  // // Load this information in to the FBO's texture
  // velPingPong.allocate(textureRes, textureRes, GL_RGB32F);
  // velPingPong.src->getTexture().loadData(vel.data(), textureRes, textureRes, GL_RGB);
  // velPingPong.dst->getTexture().loadData(vel.data(), textureRes, textureRes, GL_RGB);

  // Loading and setings of the variables of the textures of the particles
  sparkImg.load("spark.png");
  imgWidth = sparkImg.getWidth();
  imgHeight = sparkImg.getHeight();

  // Allocate the final
  renderFBO.allocate(width, height, GL_RGBA32F);
  renderFBO.begin();
  ofClear(0, 0, 0, 255);
  renderFBO.end();


  mesh.setMode(OF_PRIMITIVE_POINTS);
  for(int x = 0; x < textureRes; x++){
      for(int y = 0; y < textureRes; y++){
          mesh.addVertex({x,y,0});
          mesh.addTexCoord({x, y});
      }
  }
}
void GPUScene::draw(){
  ofBackground(0);
  gui.draw();
  ofSetColor(100,255,255);
  renderFBO.draw(offsets.x,offsets.y);

  ofSetColor(255);
  ofDrawBitmapString("Fps: " + ofToString( ofGetFrameRate()), 15,15);
  if(showField){
    vectorField.draw();
  }
}
void GPUScene::update(){
  // velPingPong.dst->begin();
  ofClear(0);
  updateVel.begin();
  // updateVel.setUniformTexture("backbuffer", velPingPong.src->getTexture(), 0);   // passing the previous velocity information
  updateVel.setUniformTexture("backbuffer", image.getTexture() , 0); // passing in field texture
  updateVel.setUniformTexture("posData", posPingPong.src->getTexture(), 1);  // passing the position information
  updateVel.setUniform1i("resolution", (int)textureRes);
  updateVel.setUniform2f("screen", (float)width, (float)height);
  updateVel.setUniform1f("timestep", (float)timeStep);

  // draw the source velocity texture to be updated
  // velPingPong.src->draw(0, 0);

  updateVel.end();
  // velPingPong.dst->end();

  // velPingPong.swap();


  // Positions PingPong
  //
  // With the velocity calculated updates the position
  //
  posPingPong.dst->begin();
  ofClear(0);
  updatePos.begin();
  updatePos.setUniformTexture("prevPosData", posPingPong.src->getTexture(), 0); // Previus position
  // updatePos.setUniformTexture("velData", velPingPong.src->getTexture(), 1);  // Velocity
  updatePos.setUniformTexture("velData", image.getTexture() , 1); // passing in field texture
  updatePos.setUniform1f("timestep",(float) timeStep );

  // draw the source position texture to be updated
  posPingPong.src->draw(0, 0);

  updatePos.end();
  posPingPong.dst->end();

  posPingPong.swap();


  // Rendering
  //
  // 1.   Sending this vertex to the Vertex Shader.
  //      Each one it's draw exactly on the position that match where it's stored on both vel and pos textures
  //      So on the Vertex Shader (that's is first at the pipeline) can search for it information and move it
  //      to it right position.
  // 2.   Once it's in the right place the Geometry Shader make 6 more vertex in order to make a billboard
  // 3.   that then on the Fragment Shader is going to be filled with the pixels of sparkImg texture
  //
  renderFBO.begin();
    ofClear(0,0,0,0);
    updateRender.begin();
    updateRender.setUniformTexture("posTex", posPingPong.dst->getTexture(), 0);
    updateRender.setUniformTexture("sparkTex", sparkImg.getTexture() , 1);
    updateRender.setUniform1i("resolution", (float)textureRes);
    updateRender.setUniform2f("screen", (float)width, (float)height);
    updateRender.setUniform1f("size", (float)particleSize);
    updateRender.setUniform1f("imgWidth", (float)sparkImg.getWidth());
    updateRender.setUniform1f("imgHeight", (float)sparkImg.getHeight());

    ofPushStyle();
    ofEnableBlendMode( OF_BLENDMODE_ADD );
    ofSetColor(255);

    mesh.draw();

    ofDisableBlendMode();
    glEnd();

    updateRender.end();
    renderFBO.end();
    ofPopStyle();
}

VectorField * GPUScene::getVectorField(){
  cout << "getting vector field" <<"\n";
  vectorField.perlin(0.2);
  return &vectorField;
}
void GPUScene::mouseDragged(int x, int y, int button){
  addParticle(x, y);
}

//--------------------------------------------------------------
void GPUScene::mousePressed(int x, int y, int button){
  addParticle(x, y);
}

//--------------------------------------------------------------
void GPUScene::keyPressed(int key){
  switch(key){
    case ' ':
    resetPositions();
    break;

    case 'l':
    loadVectorField();
    break;
    case 'f':
      showField = !showField;
      // glm::vec2 * field_arr = vectorField.getField();
      //
      //
      cout << showField <<"\n";

      break;
  }
}

#include "baseScene.h"


class MainScene : public BaseScene{
  public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
		void mouseDragged(int x, int y);
		void mousePressed(int x, int y);
    int id = 1;


		VectorField vectorField;
    vector<Particle *> particles;

  private:
    void screenshot(ofImage* img) override;
    void addNewParticle(float x, float y);
    void addNewParticles(float x, float y);
    void loadVectorField();
    void toggleVectorField(bool & value);
    void clearParticles();
    void saveImage();
    bool toggleParticle();
    bool toggleParticleTrail();

    bool loading = false;
    bool showField = false;
    bool screenshotting = false;
    bool guiOn = true;
		ofImage img; //for screenshots
    ofFbo fbo;

    ofxIntSlider brushRadius;
    ofxIntSlider brushThickness;
    ofxButton resetButton;
    ofxButton saveImageButton;

    ofxGuiGroup particleGroup;
    ofxIntSlider maxParticles;
    ofxIntSlider avgLineWidth;
    ofxIntSlider particleOpacity;
    ofxFloatSlider particleLifetime;
    ofxFloatSlider particleSpeed;
    ofParameter<ofColor> particleColour;
    ofxToggle showParticleButton;
    ofxToggle showTrailButton;
    ofParameter<ofColor> particleTrailColour;

    ofxGuiGroup vectorFieldGroup;
    ofxButton loadVectorFieldButton;
    ofxToggle toggleVectorFieldButton;
    ofxPanel gui;

};

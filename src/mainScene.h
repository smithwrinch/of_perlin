#include "baseScene.h"


class MainScene : public BaseScene{
  public:
    void setup();
    void update();
    void draw();


    VectorField * getVectorField();
    void keyPressed(int key);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
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
    void createVectorField();
    bool toggleParticle();
    bool toggleParticleTrail();

    bool loading = false;
    bool showField = false;
    bool screenshotting = false;
    bool guiOn = true;
		ofImage img; //for screenshots
    ofFbo fbo;
    glm::vec2 offsets;

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
    ofxButton createVectorFieldButton;
    ofxPanel gui;

};

#include "baseScene.h"


class MainScene : public BaseScene{
  public:
    void setup();
    void update();
    void draw();

		void mouseDragged(int x, int y);
		void mousePressed(int x, int y);
    int id = 1;


		VectorField vectorField;
    vector<Particle *> particles;

  private:
    void addNewParticle(float x, float y);
    void addNewParticles(float x, float y);
    void loadVectorField();
    void toggleVectorField();

    bool loading = false;
    bool showField = false;

    ofxIntSlider brushRadius;
    ofxIntSlider brushThickness;

    ofxGuiGroup particleGroup;
    ofxIntSlider maxParticles;
    ofxIntSlider avgLineWidth;
    ofxIntSlider particleOpacity;

    ofxGuiGroup vectorFieldGroup;
    ofxButton loadVectorFieldButton;
    ofxButton toggleVectorFieldButton;
    ofxPanel gui;

};

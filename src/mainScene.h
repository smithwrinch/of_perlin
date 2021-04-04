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

    ofxIntSlider maxParticles;
    ofxIntSlider brushRadius;
    ofxIntSlider brushThickness;
    ofxPanel gui;

};

#include "baseScene.h"
// #include "vectorField.h"
// #include "particle.h"
// #include "ofxGui.h"
// #include <stdlib.h>
// #include <math.h>

class FieldScene : public BaseScene{
  public:
    void setup();
    void update();
    void draw();

		// void mouseDragged(int x, int y){};
		// void mousePressed(int x, int y){};
    int id = 2;

		VectorField vectorField;

  private:
    bool loading = false;
    int minSpacing = 1; //to prevent loaded fields with high spacing crashing
    void saveField();
    void loadField();
    void perlin();
    void randomise();
    void reset();

// panels
    ofxPanel gui;
    ofxGuiGroup saveGroup;

// main gui
    ofxIntSlider width;
    ofxIntSlider height;
    ofxButton dimsButton;
    ofxIntSlider spacing;
    ofxButton perlinButton;
    ofxButton saveButton;
    ofxButton loadButton;
    ofxTextField saveText;
    ofxButton resetButton;
    // ofxTextField loadText;


// perlin gui

    ofxGuiGroup perlinGui;
    ofxButton randomiseButton;
    ofxButton backButton;
    ofxFloatSlider perlinSpacing;
    ofxFloatSlider perlinParameter;

};
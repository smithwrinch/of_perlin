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
    int state = 0;
    void saveField();
    void loadField();
    void perlin();
    void randomise();
    void applyDims();

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
    ofxTextField loadText;


// perlin gui

    ofxGuiGroup perlinGui;
    ofxButton randomiseButton;
    ofxButton backButton;
    ofxFloatSlider perlinSpacing;
    ofxFloatSlider perlinParameter;

};

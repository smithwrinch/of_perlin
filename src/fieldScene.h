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
    void setVectorField(VectorField * field);
    VectorField* getVectorField();
    void mousePressed(int x, int y, int button);
		void mouseDragged(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
    int id = 2;

		VectorField vectorField;

  private:
    bool loading = false;
    int minSpacing = 1; //to prevent loaded fields with high spacing crashing
    int lastX;
    int lastY;
    string eqnX = "";
    string eqnY = "";
    void saveField();
    void loadField();
    void perlin();
    void randomise();
    void smooth();
    void normalise();
    void normaliseWrtScalar();
    void reset();
    void clear();
    void sendToMain();
    void sendToGPU();
    void goToMain();
    void applyEqn();
    void applyBrushEqn();

// panels
    ofxPanel gui;
    ofxGuiGroup saveGroup;

// main gui
    ofxIntSlider width;
    ofxIntSlider height;
    ofxIntSlider brushRadius;
    ofxButton dimsButton;
    ofxIntSlider spacing;
    ofxFloatSlider strength;
    ofxFloatSlider divideScalar;
    ofxFloatSlider effect;
    ofxButton perlinButton;
    ofxButton saveButton;
    ofxButton loadButton;
    ofxTextField saveText;
    ofxButton normaliseButton;
    ofxButton normaliseScalarButton;
    ofxButton resetButton;
    ofxButton clearButton;
    ofxButton sendToMainButton;
    ofxButton sendToGPUButton;
    ofxButton goToMainButton;
    ofxIntSlider smoothKernel;
    ofxFloatSlider smoothSigma;
    ofxFloatSlider smoothStrength;
    ofxButton smoothButton;
    // ofxTextField loadText;


// perlin gui

    ofxGuiGroup perlinGui;
    ofxButton randomiseButton;
    ofxFloatSlider perlinSpacing;
    ofxIntSlider perlinParameterX;
    ofxIntSlider perlinParameterY;

// custom eqn gui

  ofxGuiGroup eqnGui;
  ofxLabel eqnLabel;
  ofxTextField eqnXText;
  ofxTextField eqnYText;
  ofxButton eqnButton;
  ofxButton eqnBrushButton;

};

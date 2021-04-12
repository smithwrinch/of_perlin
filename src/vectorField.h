#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "exprtk.hpp"
#include <iostream>
#include <fstream>

#define WIDTH 800
#define HEIGHT 800

class VectorField {
  public:
    VectorField();
    ~VectorField();

    void setup(float spacing, float offX = ofGetWidth()/2 - WIDTH/2, float offY = ofGetHeight()/2 - HEIGHT/2);

    void draw();
    void perlin(float spacing=0.0077, float t1 = ofRandom(0,30), float t2 = ofRandom(0,30));
    void uniform(glm::vec2 u);
    void blur(int kernelSize, float sigma, float strength);
    void setFromImage(ofImage & img);
    void normalise(float scalar=1);
    void normalise(int i);
    void setSpacing(float s);
    void copy(VectorField*vf);

    void setVector(string eqnX, string eqnY, double x, double y, int brushRadius);
    void addSink(float x, float y, int brushRadius, float strength);
    void addMagnet(float x, float y, int brushRadius, float strength);
    void addEqnBrush(string eqnX, string eqnY, float x, float y, int brushRadius);
    void save(string fname);
    int loadFromFile(string fname);

    void saveXML(string fname);
    bool loadFromXML(string fname);

    glm::vec2 getVector(float x, float y);
    glm::vec2 getOffset();

    // for parsing equation
    // typedef exprtk::symbol_table<double> symbol_table_t;
    // typedef exprtk::expression<double>     expression_t;
    // typedef exprtk::parser<double>             parser_t;
    exprtk::symbol_table<double>  symbol_table;
    exprtk::expression<double>  expressionX;
    exprtk::expression<double>  expressionY;

  protected:
    glm::vec2 * field;
    int spacing;
  private:
     int width;
     int height;
     float offX;
     float offY;
     // for saving
     ofxXmlSettings settings;

  };

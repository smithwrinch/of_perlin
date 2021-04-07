#include "ofMain.h"
#include "ofxXmlSettings.h"
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
    void setSpacing(float s);
    void copy(VectorField*vf);

    void normalise();
    // void setWidth(int w);
    // void setHeight(int h);
    void save(string fname);
    int loadFromFile(string fname);
    void saveXML(string fname);
    bool loadFromXML(string fname);

    glm::vec2 getVector(float x, float y);
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

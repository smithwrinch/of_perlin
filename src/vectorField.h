#include "ofMain.h"
#include "ofxXmlSettings.h"
#include <iostream>
#include <fstream>

#define WIDTH 1024
#define HEIGHT 800

class VectorField {
  public:
    VectorField();
    ~VectorField();

    void setup(float spacing);

    void draw();
    void perlin(float spacing=0.0077);
    void uniform(glm::vec2 u);
    void setSpacing(float s);
    // void setWidth(int w);
    // void setHeight(int h);
    void save(string fname);
    int loadFromFile(string fname);
    void saveXML(string fname);
    bool loadFromXML(string fname);


    glm::vec2 getVector(float x, float y);


  private:
	   glm::vec2 * field;
     int spacing;
     int width;
     int height;
     // for saving
     ofxXmlSettings settings;

  };

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include <iostream>

class VectorField {
  public:
    VectorField();
    ~VectorField();

    void setup(int height, int width, int spacing);

    void draw();
    void perlin(float spacing=0.0077);
    void uniform(glm::vec2 u);
    void setSpacing(int s);
    void setWidth(int w);
    void setHeight(int h);
    void save(string fname);
    bool loadFromFile(string fname);


    glm::vec2 getVector(float x, float y);


  private:
	   glm::vec2 * field;
     int spacing;
     int width;
     int height;
     // for saving
     ofxXmlSettings settings;

  };

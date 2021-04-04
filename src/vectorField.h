#include "ofMain.h"
#include <iostream>

class VectorField {
  public:
    VectorField();
    ~VectorField();

    void setup(int height, int width, int spacing);

    void draw();
    void perlin();

    glm::vec2 getVector(float x, float y);

    int width;
    int height;

  private:
	   glm::vec2 * field;
     int spacing;
  };

#include "ofMain.h"

class Particle {
public:

    Particle(glm::vec2 startPos, float s = 10, float swidth = 0.01);
    // Particle(glm::vec2 startPos, float s, float swidth);
    ~Particle();

    // void setup(glm::vec2 startPos);
    void setColour(int r, int g, int b, int a);
    void setOpacity(int a);
    void move(glm::vec2 dir);
    void draw();
    void stayOnScreen();
    bool isOffScreen();
    bool isDead();

    glm::vec2 startPos;
    glm::vec2 pos;

    int duration;
    bool dead = false;
    float speed;

    ofPath path;
    ofColor colour = ofColor ( 255 , 255 , 255, 20 ) ;

};

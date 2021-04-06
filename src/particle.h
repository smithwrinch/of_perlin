#include "ofMain.h"

class Particle {
public:

    Particle(glm::vec2 startPos, float speed = 10, float swidth = 0.01, float d = 0);
    // Particle(glm::vec2 startPos, float s, float swidth);
    ~Particle();

    // void setup(glm::vec2 startPos);
    void setColour(int r, int g, int b);
    void setColour(ofColor *col);
    void setTrailColour(int r, int g, int b);
    void setTrailColour(ofColor *col);
    void setOpacity(int a);
    void setTrailOpacity(int a);
    void setSpeed(float s);
    void setStrokeWidth(float s);
    void setDuration(float d);
    glm::vec2 getPosition();
    void move(glm::vec2 dir);
    void draw();
    void drawTrail();
    void stayOnScreen();
    bool isOffScreen();
    bool isDead();

  private:
    glm::vec2 startPos;
    glm::vec2 pos;

    float startTime;
    float strokeWidth;
    float duration;
    bool dead = false;
    float speed;

    ofPath path;
    ofColor colour = ofColor ( 255 , 255 , 255, 20 ) ;
    ofColor trailColour = ofColor ( 255 , 255 , 255, 20 ) ;

};

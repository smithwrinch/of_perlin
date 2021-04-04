#pragma once
#include "ofMain.h"
#include "vectorField.h"
#include "particle.h"
#include "ofxGui.h"
#include <stdlib.h>
#include <math.h>

class BaseScene{
	public:
		virtual void setup(){};
		virtual void update(){};
		virtual void draw(){};
    int id;
    virtual int getID(){
      return id;
    };
    virtual void setID(int i){
      id = i;
    }
		// virtual void keyPressed(int key);
		// virtual void keyReleased(int key);
		// virtual void mouseMoved(int x, int y);
		virtual void mouseDragged(int x, int y){};
		virtual void mousePressed(int x, int y){};
		// virtual void mouseReleased(int x, int y, int button);
		// virtual void mouseEntered(int x, int y);
		// virtual void mouseExited(int x, int y);
		// virtual void windowResized(int w, int h);
		// virtual void dragEvent(ofDragInfo dragInfo);
		// virtual void gotMessage(ofMessage msg);

		// VectorField vectorField;
    // vector<Particle *> particles;
		// ofImage img; //for screenshots

		// int maxParticles = 20000;
};

#pragma once

#include "ofMain.h"
#include <iostream>
#include "mainScene.h"
#include "fieldScene.h"
#include "baseScene.h"


class ofApp : public ofBaseApp{
	public:

		ofImage img; //for screenshots
		BaseScene * currentScene;
		MainScene mainScene;
		FieldScene fieldScene;

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		// VectorField vectorField;
    // vector<Particle *> particles;
		// int maxParticles = 20000;
	// private:
	// 	void addNewParticle(float x, float y);
	// 	void addNewParticles(float x, float y);
	//
	// 	ofxIntSlider maxParticles;
	// 	ofxIntSlider brushRadius;
	// 	ofxIntSlider brushThickness;
	// 	ofxPanel gui;
};

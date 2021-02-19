#pragma once

#include "ofMain.h"
#include "ofxVectorField.h"
#include "Particle.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void resetParticles();
		void resetPath();
		void resetField();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

    ofxVectorField vectorField;
    int width = 720;
    int height = 480;
		int factor = 10; //affects num particles so 10 would be 720/10 * 480/10
		bool showParticles = true;
		bool showField = false;

    vector <Particle> particles;
		vector <ofPath> paths;
};

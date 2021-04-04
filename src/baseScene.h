#include "ofMain.h"

class BaseScene{
	public:
		virtual void setup();
		virtual void update();
		virtual void draw();

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

		VectorField vectorField;
    vector<Particle *> particles;
		ofImage img; //for screenshots

		// int maxParticles = 20000;
	private:
};

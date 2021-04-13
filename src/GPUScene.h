#include "ofMain.h"
#include "baseScene.h"


struct pingPongBuffer {
public:
	void allocate( int _width, int _height, int _internalformat = GL_RGBA){
		// Allocate
		for(int i = 0; i < 2; i++){
			FBOs[i].allocate(_width,_height, _internalformat );
			FBOs[i].getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
		}

		//Assign
		src = &FBOs[0];
		dst = &FBOs[1];

		// Clean
		clear();
	}

	void swap(){
		std::swap(src,dst);
	}

	void clear(){
		for(int i = 0; i < 2; i++){
			FBOs[i].begin();
			ofClear(0,255);
			FBOs[i].end();
		}
	}

	ofFbo& operator[]( int n ){ return FBOs[n];}
	ofFbo   *src;       // Source       ->  Ping
	ofFbo   *dst;       // Destination  ->  Pong

private:
	ofFbo   FBOs[2];    // Real addresses of ping/pong FBO«s
};

class GPUScene : public BaseScene{
  public:
    void setup();
    void update();
    void draw();

		VectorField * getVectorField();
    void keyPressed(int key);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);

  private:

		VectorField vectorfield;
    void resetPositions();
    void loadVectorField();
		void texturiseField();
    glm::vec2 offsets;
		ofImage image;

    ofShader    updatePos;
  	ofShader    updateVel;
  	ofShader    updateRender;

  	pingPongBuffer posPingPong;
  	pingPongBuffer velPingPong;

  	ofFbo   renderFBO;

  	ofImage sparkImg;
  	ofImage fieldVelocities;

  	float   timeStep;
  	float   particleSize;

  	int     width, height;
  	int     imgWidth, imgHeight;
  	int     numParticles;
  	int     textureRes;


  	ofVboMesh mesh;
};

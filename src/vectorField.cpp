#include "vectorField.h"

VectorField::VectorField(){

}
VectorField::~VectorField(){
  delete [] field;
}

void VectorField::setup(int w, int h, int s){
  width = w/s;
  height = h/s;
  spacing = s;
  field = new glm::vec2[width*height];

	// glPopMatrix();
}

void VectorField::draw(){
  // glPushMatrix();

  	ofSetColor(255, 255, 255);

  	glTranslatef(spacing/2, spacing/2, 0);

  	for(int y=0; y<height; y+=2){
  		for(int x=0; x<width; x+=2){

  			int pos = y * width + x;
  			int startX = x * spacing;
  			int startY = y * spacing;

        ofDrawLine(startX, startY, startX+field[pos].x*spacing, startY+field[pos].y*spacing);
  		}
  	}

  	// glPopMatrix();
}
void VectorField::perlin(){
  	float t1 = ofRandom(0,30);
  	float t2 = ofRandom(0,30);
  	float spacing = 0.0077;

  	int numVectors = width * height;

  	for(int i=0; i<numVectors; i++){

  		int xPos = i % width;
  		int yPos = i / width;

  		field[i].x = ofSignedNoise(xPos*spacing, yPos*spacing, t1);
  		field[i].y = ofSignedNoise(xPos*spacing, yPos*spacing, t2);
  	}

    cout << field;
}
// returns interpolated vector at position x and y
glm::vec2 VectorField::getVector(float x, float y){
  if(x < 0 || y < 0 || x > width || y > height){
    // return glm::vec2(ofRandom(-1, 1),ofRandom(-1, 1));
    return glm::vec2(0,0);
  }
  glm::vec2 newVector(0);

	float pctX = float(x)/ofGetWidth();
	float pctY = float(y)/ofGetHeight();

	int stepX = pctX * width;
	int stepY = pctY * height;

	pctX = float(stepX % spacing)/spacing;
	pctY = float(stepY % spacing)/spacing;

	stepX = ofClamp(stepX, 0, width-2);
	stepY = ofClamp(stepY, 0, height-2);
  // was -1 but changed as was seg faulting here.


	newVector.x = field[stepY * width + stepX + 1].x * pctX + field[stepY * width + stepX].x  * (1.0 - pctX);
	newVector.y = field[(stepY + 1) * width + stepX].y * pctY + field[stepY * width + stepX].y  * (1.0 - pctY);

	return newVector;

}

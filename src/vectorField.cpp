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
void VectorField::perlin(float s){
  	float t1 = ofRandom(0,30);
  	float t2 = ofRandom(0,30);
  	float spacing = s;

  	int numVectors = width * height;

  	for(int i=0; i<numVectors; i++){

  		int xPos = i % width;
  		int yPos = i / width;

  		field[i].x = ofSignedNoise(xPos*spacing, yPos*spacing, t1);
  		field[i].y = ofSignedNoise(xPos*spacing, yPos*spacing, t2);
  	}

}

void VectorField::uniform(glm::vec2 u){

    glm::vec2 v = glm::normalize(u);

  	int numVectors = width * height;

  	for(int i=0; i<numVectors; i++){

  	   field[i].x = v.x;
   	   field[i].y = v.y;
  	}

}

void VectorField::setSpacing(int s){
  spacing = s;
}

void VectorField::setWidth(int w){
  width = w;
}

void VectorField::setHeight(int h){
  height = h;
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

void VectorField::save(string fname){

  settings.setValue("settings:width", width);
  settings.setValue("settings:height", height);
  settings.setValue("settings:spacing", spacing);

  settings.addTag("positions");
  settings.pushTag("positions");
  //points is a vector<ofPoint> that we want to save to a file
  int numVectors = width * height;

  cout <<numVectors;
  cout << "\n";
  for(int i=0; i<numVectors; i++){

    //each position tag represents one point
    settings.addTag("position");
    settings.pushTag("position",i);
    //so set the three values in the file
    settings.addValue("X", field[i].x);
    settings.addValue("Y", field[i].y);
    // positions.addValue("Z", points[i].z);
    settings.popTag();//pop position
  }
  settings.popTag(); //pop position
  settings.saveFile(fname);

}

bool VectorField::loadFromFile(string fname){
    if(settings.loadFile(fname)){

      delete [] field;

      int w = settings.getValue("settings:width", 0);
      int h = settings.getValue("settings:width", 0);
      int s = settings.getValue("settings:width", 0);
      setWidth(w);
      setHeight(h);
      setSpacing(s);

      field = new glm::vec2[w*h];
      settings.pushTag("positions");
      for(int i = 0; i < settings.getNumTags("position"); i++){
          settings.pushTag("position", i);
          field[i].x = settings.getValue("X", 0.0);
          field[i].y = settings.getValue("Y", 0.0);
          settings.popTag();
      }

      settings.popTag(); //pop position
      return true;
  }
  else{
      ofLogError("Position file did not load!");
      return false;
  }
}

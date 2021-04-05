#include "vectorField.h"

VectorField::VectorField(){

}
VectorField::~VectorField(){
  delete [] field;
}

void VectorField::setup(float s){
  spacing = s;
  width = WIDTH/s;
  height = HEIGHT/s;
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
  	// float spacing = s;

  	int numVectors = width * height;

  	for(int i=0; i<numVectors; i++){

  		int xPos = i % width;
  		int yPos = i / width;

  		field[i].x = ofSignedNoise(xPos*s, yPos*s, t1);
  		field[i].y = ofSignedNoise(xPos*s, yPos*s, t2);
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

void VectorField::setSpacing(float s){
  spacing = s;
  // setWidth(WIDTH/s);
  // setHeight(HEIGHT/s);
  width = WIDTH/s;
  height = HEIGHT/s;
}

// void VectorField::setWidth(int w){
//   width = w;
// }
//
// void VectorField::setHeight(int h){
//   height = h;
// }
// returns interpolated vector at position x and y
glm::vec2 VectorField::getVector(float x, float y){
  // if(x < 0 || y < 0 || x > width || y > height){
  //   // return glm::vec2(ofRandom(-1, 1),ofRandom(-1, 1));
  //   return glm::vec2(0,0);
  // }
  glm::vec2 newVector(0);

	float pctX = float(x)/WIDTH;
	float pctY = float(y)/HEIGHT;

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

void VectorField::saveXML(string fname){
  settings.setValue("settings:width", width);
  settings.setValue("settings:height", height);
  settings.setValue("settings:spacing", spacing);

  settings.addTag("positions");
  settings.pushTag("positions");
  int numVectors = width * height;

  std::ofstream outFile(fname);
  for(int i=0; i<numVectors; i++){
    settings.addTag("position");
    settings.pushTag("position",i);
    settings.addValue("X", field[i].x);
    settings.addValue("Y", field[i].y);
    settings.popTag();//pop position

    if(i%1000 == 0){
      cout << float(100*float(i) / float(numVectors));
      cout << "% remaining... \n";
    }
  }
  settings.popTag(); //pop position
  settings.saveFile(fname);

}

void VectorField::save(string fname){

  int numVectors = width * height;

  std::ofstream outFile("data/"+fname);
  outFile << std::to_string(spacing) << "\n";
  outFile << std::to_string(width) << "\n";
  outFile << std::to_string(height) << "\n";
  for(int i=0; i<numVectors; i++){
    if(i%1000 == 0){
      cout << float(100*float(i) / float(numVectors));
      cout << "% remaining... \n";
    }
    outFile << std::to_string(field[i].x) << "\n" << std::to_string(field[i].y) << "\n";
  }


}


int VectorField::loadFromFile(string fname){

  fstream newfile;
  newfile.open(fname,ios::in); //open a file to perform read operation using file object
  if (newfile.is_open()){   //checking whether the file is open

    delete [] field;
    // field = new glm::vec2[width*height];
    string tp;
    int i = 0;
    int idx = 0;

    while(getline(newfile, tp)){ //read data from file object and put it into string.
       switch(i){
         case 0:
         spacing = std::stof(tp);
         cout << std::stof(tp) << "\n";
         break;
         case 1:
         width = std::stof(tp);
         cout << std::stof(tp) << "\n";
         break;
         case 2:
          height = std::stof(tp);
          cout << std::stof(tp) << "\n";
          field = new glm::vec2[width*height];
          break;
         default:
           if(i % 2 == 0){
             field[idx].y = std::stof(tp);
           }else{
             field[idx].x = std::stof(tp);
             idx ++;
           }
       }
      i++;
    }
    newfile.close(); //close the file object.
  }
  return spacing;
}

bool VectorField::loadFromXML(string fname){
    if(settings.loadFile(fname)){

      delete [] field;

      int w = settings.getValue("settings:width", 0);
      int h = settings.getValue("settings:height", 0);
      float s = settings.getValue("settings:spacing", 0.0);
      // setWidth(w);
      // setHeight(h);
      setSpacing(s);

      field = new glm::vec2[w*h];
      settings.pushTag("positions");
      for(int i = 0; i < settings.getNumTags("position"); i++){
          settings.pushTag("position", i);
          field[i].x = settings.getValue("X", 0.0);
          field[i].y = settings.getValue("Y", 0.0);
          settings.popTag();
          if(i%1000 == 0){
            cout << i / settings.getNumTags("position");
            cout << "% remaining... \n";
          }
      }

      settings.popTag(); //pop position
      return true;
  }
  else{
      ofLogError("Position file did not load!");
      return false;
  }
}

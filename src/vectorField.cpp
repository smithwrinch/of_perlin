#include "vectorField.h"

/*
TODO:
- add vector field from image
- add perlin noise effect on generation (possibly)
- fix screenshot
- look into possibility of video
*/

VectorField::VectorField(){

}
VectorField::~VectorField(){
  delete [] field;
}

void VectorField::setup(float s, float oX, float oY){
  spacing = s;
  offX = oX;
  offY = oY;
  width = WIDTH/s;
  height = HEIGHT/s;
  field = new glm::vec2[WIDTH*HEIGHT];

  // Instantiate expression and register symbol_table
  expressionX.register_symbol_table(symbol_table);
  expressionY.register_symbol_table(symbol_table);

	// glPopMatrix();
}

void VectorField::draw(){
  // glPushMatrix();

  	ofSetColor(255, 255, 255);

  	glTranslatef(spacing/2, spacing/2, 0);

  	for(int y=0; y<height; y+=2){
  		for(int x=0; x<width; x+=2){

  			int pos = y * width + x;
  			int startX = x * spacing + offX;
  			int startY = y * spacing + offY;

        float endX = startX+field[pos].x*spacing;
        float endY = startY+field[pos].y*spacing;

        float dX = endX - startX;
        float dY = endY - startY;

        float dist = sqrt(pow(dX, 2) + pow(dY, 2));


        if(dist > spacing){
          ofSetColor(255 - dist*spacing, 255 - dist*spacing, 255);
          dX /= dist/spacing;
          dY /= dist/spacing;
        }

        ofDrawLine(startX, startY, dX + startX, dY + startY);

        // for arrow head
        //
        // ofDrawCircle(endX, endY, spacing*0.3);

      }
  	}

  	// glPopMatrix();
}
void VectorField::perlin(float s, float t1, float t2){

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

void VectorField::normalise(float scalar){
  for(int i=0; i<width*height; i++){
    normalise(i);
    if(scalar == 1) continue;
    field[i].x /= scalar;
    field[i].y /= scalar;
  }
}

void VectorField::normalise(int i){
    if(field[i].x == 0){
      field[i].x += 0.0001; //to prevent NaN on normalisation
    }
    if(field[i].y == 0){
      field[i].y += 0.0001;
    }
   field[i] = glm::normalize(field[i]);
}


void VectorField::setVector(string eqnX, string eqnY, double x, double y, int brushRadius){

  exprtk::parser<double> parser;
  for(int i=0; i<width*height; i++){
  	double xPos = i % width;
  	double yPos = i / width;

    if( i % 1000 == 0){
      cout << (i *100/(width*height)) << "% remaining" << "\n";
    }

    // Register x with the symbol_table

     symbol_table.remove_variable("x");
     symbol_table.remove_variable("y");
     symbol_table.add_variable("x",xPos);
     symbol_table.add_variable("y",yPos);


     // Instantiate parser and compile the expression

     if(!parser.compile(eqnX,expressionX) || !parser.compile(eqnY,expressionY)){
       cout << "error: bad equation" << "\n";
       return;
     };

     double resultX = 0.0;
     double resultY = 0.0;

     // Evaluate and print result
     resultX = expressionX.value();
     // printf("Result1: %10.5f\n",resultX);
     resultY = expressionY.value();
     // printf("Result1: %10.5f\n",resultY);
     field[i].x = float(resultX);
     field[i].y = float(resultY);
   }

}


void VectorField::addMagnet(float x, float y, int brushRadius, float strength){
  for(int i=0; i<width*height; i++){

    int w = i % width;
    int h = i / width;
    float xPos = w * spacing + offX;
    float yPos = h * spacing + offY;

    float xVal = field[i].x;
    float yVal = field[i].y;

    float dirX = xPos - x;
    float dirY = yPos - y;

    float dist = sqrt(pow(dirX, 2) + pow(dirY, 2));

    if(dist > brushRadius && brushRadius !=0){ //outside cricle
      continue;
    }

    if(dirX == 0){
      dirX = 0.001;
    }
    float theta = atan(dirY / dirX);

    if(dist == 0){
      dist = 0.001;
    }

    float r = (strength*500/(dist*dist));

    float newX = r*cos(theta);
    float newY = r*sin(theta);


    xVal += newX;
    yVal += newY;

    field[i].x = xVal;//*(effect);
    field[i].y = yVal;//*(effect);
    float newdist = sqrt(pow(xVal, 2) + pow(yVal, 2));
    if(newdist > 1 && r > 0.005){
      normalise(i);
    }

  }
}

void VectorField::addSink(float x, float y, int brushRadius, float strength){
  for(int i=0; i<width*height; i++){
    int w = i % width;
    int h = i / width;
    float xPos = w * spacing + offX;
    float yPos = h * spacing + offY;
    float dirX = xPos - x;
    float dirY = yPos - y;

    float xVal = field[i].x;
    float yVal = field[i].y;

    float dist = sqrt(pow(dirX, 2) + pow(dirY, 2));
    if(dist > brushRadius && brushRadius !=0){ //inside cricle
      continue;
    }

    if(dist == 0){
      dist = 0.001;
    }

    // float outX = -(strength/100)*(xVal*dirX)/(pow(xVal,2) + pow(yVal,2));
    // float outY = -(strength/100)*(yVal*dirY)/(pow(xVal,2) + pow(yVal,2));

    float outX = strength *dirX/dist;
    float outY = strength *dirY/dist;
    if(brushRadius !=0){
      outX *= (1 - dist/brushRadius);
      outY *= (1 - dist/brushRadius);
    }
    field[i].x += outX;
    field[i].y += outY;

  }
  // normalise();
}

void VectorField::addEqnBrush(string eqnX, string eqnY, float x, float y, int brushRadius){
  exprtk::parser<double> parser;
  if(brushRadius==0){
    return;
  }
  for(int i=0; i<width*height; i++){
    int w = i % width;
    int h = i / width;
    double xPos = w * spacing + offX;
    double yPos = h * spacing + offY;
    float dirX = xPos - x;
    float dirY = yPos - y;
    float dist = sqrt(pow(dirX, 2) + pow(dirY, 2));
    if(dist > brushRadius){ //inside cricle
      continue;
    }

    // Register x with the symbol_table
    xPos -= offX;
    yPos -= offY;

    xPos -= WIDTH/2;
    yPos -= HEIGHT/2;

    xPos /= spacing;
    yPos /= spacing;

    symbol_table.remove_variable("x");
    symbol_table.remove_variable("y");
    symbol_table.add_variable("x",xPos);
    symbol_table.add_variable("y",yPos);


    // Instantiate parser and compile the expression

    if(!parser.compile(eqnX,expressionX) || !parser.compile(eqnY,expressionY)){
     cout << "error: bad equation" << "\n";
     return;
    };

    double resultX = 0.0;
    double resultY = 0.0;

    // Evaluate and print result
    resultX = expressionX.value();
    // printf("Result1: %10.5f\n",resultX);
    resultY = expressionY.value();
    // printf("Result1: %10.5f\n",resultY);
    field[i].x = float(resultX);
    field[i].y = float(resultY);


  }
}


void VectorField::setFromImage(ofImage & image){

    int imgW = image.getWidth();
    int imgH = image.getHeight();
	  int imgPixelCount = imgW * imgH;


	// storage for brightness
	unsigned char * imagePixels = image.getPixels().getData();
	unsigned char* brightness = new unsigned char[imgPixelCount];

	if( image.getPixels().getImageType() == OF_IMAGE_GRAYSCALE){

		for(int x=0; x<imgW; x++){
			for(int y=0; y<imgH; y++){

				int srcPos = y * imgW + x;

				unsigned char b = imagePixels[srcPos];

				brightness[srcPos] = b;
			}
		}

	} else {

		// convert RGB to luma
		unsigned char * imagePixels = image.getPixels().getData();
		unsigned char* brightness = new unsigned char[imgPixelCount];
		int bpp = image.getPixels().getBytesPerPixel();

		for(int x=0; x<imgW; x++){
			for(int y=0; y<imgH; y++){

				int dstPos = y * imgW + x;
				int srcPos = dstPos * 3;

				unsigned char r = imagePixels[srcPos];
				unsigned char g = imagePixels[srcPos+1];
				unsigned char b = imagePixels[srcPos+2];

				brightness[dstPos] = ( r * 0.299) + (.587 * g) + (.114 * b);
			}
		}
	}

	// detetermine the vector at each position in the image

	for(int x=1; x<width-1; x++){
		for(int y=1; y<height-1; y++){

			int vecPos = y * width + x;
			char areaPixels[9];

			// loop through the area pixels
			for(int i=-1; i<=1; i++){
				for(int j=-1; j<=1; j++){

					// determine where to read from in the area (not optimized)
					int readPos = ((y + j) * spacing * imgW + (x + i)*spacing) * 3;

					unsigned char R = imagePixels[readPos];
					unsigned char G = imagePixels[readPos+1];
					unsigned char B = imagePixels[readPos+2];

					char BR = (0.299 * R) + (.587 * G) + (.114 * B);

					int writePos = (j+1) * 3 + (i + 1);

					areaPixels[writePos] = BR;
				}
			}

			float dX = (areaPixels[0] + areaPixels[3] + areaPixels[6])/3 - (areaPixels[2] + areaPixels[5] + areaPixels[8])/3;
			float dY = (areaPixels[0] + areaPixels[1] + areaPixels[2])/3 - (areaPixels[6] + areaPixels[7] + areaPixels[8])/3;

			field[vecPos].x = dY;
			field[vecPos].y = dX;
		}
	}
}


void VectorField::setSpacing(float s){
  spacing = s;
  // setWidth(WIDTH/s);
  // setHeight(HEIGHT/s);
  width = WIDTH/s;
  height = HEIGHT/s;
}


glm::vec2 VectorField::getOffset(){
  return glm::vec2(offX, offY);
}
// returns interpolated vector at position x and y
glm::vec2 VectorField::getVector(float x, float y){
  // if(x < 0 || y < 0 || x > width || y > height){
  //   // return glm::vec2(ofRandom(-1, 1),ofRandom(-1, 1));
  //   return glm::vec2(0,0);
  // }
  glm::vec2 newVector(0);
  x -= offX;
  y -= offY;

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

void VectorField::copy(VectorField* vf){
  setSpacing(vf->spacing);
  for (int i =0; i < width*height; i++){
    field[i].x = vf->field[i].x;
    field[i].y = vf->field[i].y;
  }
}

int VectorField::loadFromFile(string fname){

  fstream newfile;
  newfile.open(fname,ios::in); //open a file to perform read operation using file object
  if (newfile.is_open()){   //checking whether the file is open

    // delete [] field;
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
          // field = new glm::vec2[width*height];
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

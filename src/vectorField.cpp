#include "vectorField.h"

/*
TODO:
- add vector field from image
- add perlin noise effect on generation (possibly)
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

//  floatingPointFbo.allocate(WIDTH, HEIGHT, GL_RGBA32F);

  // Instantiate expression and register symbol_table
  expressionX.register_symbol_table(symbol_table);
  expressionY.register_symbol_table(symbol_table);

  // out.allocate(WIDTH, HEIGHT, OF_IMAGE_COLOR);
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
          ofSetColor(255 - dist*3/spacing, 255 - dist*3/spacing, 255);
          dX /= dist/spacing;
          dY /= dist/spacing;
        }

        ofDrawLine(startX, startY, dX + startX, dY + startY);

        // for arrow head
        //

        // ofDrawCircle(dX + startX, dY + startY, spacing*0.05*dist);
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
// gaussian blur
void VectorField::blur(int kernelSize, float sigma, float strength){

  if(kernelSize % 2 == 0){
    cout << "kernel cannot be even" << "\n";
    return;
  }

  double kernel[kernelSize][kernelSize];
  double mean = kernelSize/2;
  double sum = 0.0; // For accumulating the kernel values
  for (int x = 0; x < kernelSize; ++x)
      for (int y = 0; y < kernelSize; ++y) {
          kernel[x][y] = exp( -0.5 * (pow((x-mean)/sigma, 2.0) + pow((y-mean)/sigma,2.0)) )
                           / (2 * M_PI * sigma * sigma);

          // Accumulate the kernel values
          sum += kernel[x][y];
      }



  // Normalize the kernel
  for (int x = 0; x < kernelSize; ++x){
    for (int y = 0; y < kernelSize; ++y){
      kernel[x][y] /= sum;
      kernel[x][y] *= strength;
      // cout << kernel[x][y] << " ,";
    }
    // cout << "\n";
  }


  vector<glm::vec2> tmpArray;

	float blurTotal = 1.0;

	// for(int i=0; i<kernelSize*kernelSize; i++) blurTotal += kernel[i][i%kernelSize];
    for(int i=0; i<width*height; i++){
        glm::vec2 tmp = glm::vec2(0, 0);
        tmpArray.push_back(tmp);
    }

  int knum = (kernelSize-1)/2;

	for(int x=knum; x<width-knum; x++){
		for(int y=knum; y<height-knum; y++){

			int dstPos = y * width + x;

			for(int i=0; i<2*knum; i++){
				for(int j=0; j<2*knum; j++){

					int srcPos = (y + j-knum) * width + x + i-knum;
					// int arrayPos = (j + 1) * 3 + i + 1;
          // int iPos =

          tmpArray[dstPos] += field[srcPos] * kernel[i][j];
					//tmpArray[dstPos] += vectorField[srcPos] * blurVals[arrayPos];
				}
			}
		}
	}
	/*
	for(int x = 0; x<width; x++) tmpArray[x] = vectorField[x];
	for(int x = 0; x<width; x++) tmpArray[(height-1)*width+x] = vectorField[(height-1)*width+x];
	for(int y = 0; y<height; y++) tmpArray[y*width] = vectorField[y*width];
	for(int y = 0; y<height; y++) tmpArray[y*width+width-1] = vectorField[y*width+width-1];
	*/
    // for(int x = 0; x<width; x++) tmpArray.at(x)= field[x];
    // for(int x = 0; x<width; x++) tmpArray.at((height-1)*width+x) = field[(height-1)*width+x];
    // for(int y = 0; y<height; y++) tmpArray.at(y*width) = field[y*width];
    // for(int y = 0; y<height; y++) tmpArray.at(y*width+width-1) = field[y*width+width-1];

	for(int i=0; i<width*height; i++) {

		field[i] = tmpArray[i] / blurTotal;
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


    xPos -= width/2;
    yPos -= height/2;

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
    //xPos -= offX;
    //yPos -= offY;

    // xPos -= WIDTH/2;
    // yPos -= HEIGHT/2;
    //
    // xPos /= spacing;
    // yPos /= spacing;

    xPos -= x;
    yPos -= y;

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


ofFbo * VectorField::convertToFloatBuffer(){


//  floatingPointFbo.getTexture().loadData(field, WIDTH, HEIGHT);


  return &floatingPointFbo;
}

//
// // converts field to an image to be used as shader
void VectorField::convertToImage(){
  ofImage a;
  a.allocate(width,height, OF_IMAGE_COLOR);
  a.setColor(ofColor::white);
  a.update();
  for(int i=0; i<width*height; i++){
    int w = i % width;
    int h = i / width;
    // out.setColor(w, h, ofColor(field[i].x, field[i].y, 0));

    float x = field[i].x;
    float y = field[i].y;

    // float dist = sqrt(pow(x,2)+ pow(y,2));
    // x /= dist;
    // y/= dist;
    //
    // x += 1;
    // y += 1;
    // x *= 128;
    // y *= 128;
    //
    // a.getPixels()[i*3+2] = 0;
    // if(field[i].x < 0){
    //   a.getPixels()[i*3+2] = 64;
    // }
    // if(field[i].y < 0){
    //   a.getPixels()[i*3+2] += 128;
    // }
    //
    // a.getPixels()[i*3] = x;
    // a.getPixels()[i*3+1] = y;
    a.getPixels()[i*3+2] = 0;

    a.getPixels()[i*3+2] = 0;
    if(field[i].x < 0){
      a.getPixels()[i*3+2] = 64;
    }
    if(field[i].y < 0){
      a.getPixels()[i*3+2] += 128;
    }

    a.getPixels()[i*3] = abs(255*field[i].x);
    a.getPixels()[i*3+1] = abs(255*field[i].y);

  }

  ofPixels & pixels = a.getPixels();
  // pixels.swapRgb();   // fix inverted R and B channels
  ofSaveImage(pixels, "temp.png", OF_IMAGE_QUALITY_BEST);
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

glm::vec2 ** VectorField::getField(){
  return &field;
}

int VectorField::getSpacing(){
  return spacing;
}

void VectorField::setAll(float x, float y){
  for (int i = 0; i < width*height; i++){
    field[i].x = x;
    field[i].y = y;
  }
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

  cout << field[0] << "\n";
  cout << field[1] << "\n";
  cout << field[2] << "\n";
  cout << field[3] << "\n";

  cout << field[width*height-4] << "\n";
  cout << field[width*height-3] << "\n";
  cout << field[width*height-2] << "\n";
  cout << field[width*height-1] << "\n";
  cout << width*height << "\n";

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
             idx ++;
           }else{
             field[idx].x = std::stof(tp);
           }
           break;
       }
      i++;
    }
    newfile.close(); //close the file object.
  }

  cout << field[0] << "\n";
  cout << field[1] << "\n";
  cout << field[2] << "\n";
  cout << field[3] << "\n";

  cout << field[width*height-4] << "\n";
  cout << field[width*height-3] << "\n";
  cout << field[width*height-2] << "\n";
  cout << field[width*height-1] << "\n";
  cout << width*height << "\n";

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

#version 150

uniform sampler2DRect prevPosData;  // previous position texture
uniform sampler2DRect velData;      // velocity texture
//uniform sampler2DRect field;      // velocity texture

uniform float timestep;
uniform float spacing;
uniform float width;

in vec2 vTexCoord;

out vec4 vFragColor;


vec2 getDir(vec2 pos_, vec2 field, vec2 field2){

  //int width = int(800/spacing);
  //int height = int(800/spacing);

  int stepX = int(pos_.x *width);
  int stepY = int(pos_.y *width);

	float pctX = float(stepX % int(spacing))/spacing;
	float pctY = float(stepY % int(spacing))/spacing;

//  vec2 diff = field - field2;

  //return vec2(0,0);
  return vec2(field2.x*pctX + field.x*(1-pctX), field2.y*pctY + field.y*(1-pctY));
}

void main(void){
    // Get the position and velocity from the pixel color.
    //int w = 266;
    vec2 pos = texture( prevPosData, vTexCoord ).xy;
    vec3 vel = texture( velData, pos*width).xyz;


    //interpolate
    if(pos.y < float(798/800) && pos.x <float(798/800)){
      vec3 vel2 = texture( velData, (pos+1)*800).xyz;
      vel.xy = getDir(pos, vel.xy, vel2.xy);
    }

    // Update the position.


    if(vel.z <= 0.25){
      pos += vel.xy*timestep;
    }
    else if(vel.z <= 0.5){
      pos.x -= vel.x * timestep;
      pos.y += vel.y * timestep;
    }
    else if (vel.z <= 0.75){
      pos.x += vel.x * timestep;
      pos.y -= vel.y * timestep;
    }
    else{
      pos -= vel.xy * timestep;
    }

    //pos += (fieldVel/255);

    // And finally store it on the position FBO.
    vFragColor = vec4(pos.x,pos.y,1.0,1.0);
}

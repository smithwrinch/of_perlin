#version 150

uniform sampler2DRect prevPosData;  // previous position texture
uniform sampler2DRect velData;      // velocity texture
//uniform sampler2DRect fieldVel;      // velocity texture
//uniform float fieldVel[800*800*2];
uniform float timestep;
uniform float spacing;
uniform float width;

in vec2 vTexCoord;

out vec4 vFragColor;


vec3 getDir(vec2 pos_, vec3 field, vec3 field2){

/*
  int stepX = int(pos_.x *width);
  int stepY = int(pos_.y *width);

	float pctX = float(stepX % int(spacing))/spacing;
	float pctY = float(stepY % int(spacing))/spacing;
*/

  float topX = floor(pos_.x*width);
  float topY = floor(pos_.y*width);

  vec2 posBtm = vec2(topX, topY);

  vec2 pct = pos_ - posBtm/width;

  float newX =field2.x*pct.x + field.x*(1-pct.x);
  float newY =field2.y*pct.y + field.y*(1-pct.y);
  float newZ =field2.z * length(pct) + field.z*(1-length(pct));

  //return mix(field, field2, a);
  return vec3(newX, newY, newZ);
}

void main(void){
    // Get the position and velocity from the pixel color.
    //int w = 266;

    vec2 pos = texture( prevPosData, vTexCoord ).xy;

    float btmX = floor(pos.x*width);
    float topX = ceil(pos.x*width);
    float btmY = floor(pos.y*width);
    float topY = ceil(pos.y*width);

    vec2 posBtm = vec2(btmX, btmY);
    vec2 posTop = vec2(topX, topY);

    vec3 vel = texture( velData, posBtm).xyz;

    if(vel.x!=0){
      vel.x -= 0.5;
    }
    if(vel.y !=0){
      vel.y -= 0.5;
    }

    //pos += vel. * timestep;
    //interpolate
    if(pos.x < 1 && pos.y < 1){
      vec3 vel2 = texture( velData, posTop).xyz;
      if(vel2.x!=0){
        vel2.x -= 0.5;
      }
      if(vel2.y !=0){
        vel2.y -= 0.5;
      }

      vel = getDir(pos, vel, vel2);
    }

//    vel -= 0.5;
    pos += vel.xy * timestep;

    // And finally store it on the position FBO.
    vFragColor = vec4(pos.x,pos.y,1.0,1.0);
}

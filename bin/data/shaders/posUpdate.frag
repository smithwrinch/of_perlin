#version 150

uniform sampler2DRect prevPosData;  // previous position texture
uniform sampler2DRect velData;      // velocity texture
//uniform sampler2DRect field;      // velocity texture

uniform float timestep;

in vec2 vTexCoord;

out vec4 vFragColor;

void main(void){
    // Get the position and velocity from the pixel color.
    vec2 pos = texture( prevPosData, vTexCoord ).xy;
    vec3 vel = texture( velData, pos*800).xyz;
    //vec2 fieldVel = texture(field, pos.xy).xy;

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

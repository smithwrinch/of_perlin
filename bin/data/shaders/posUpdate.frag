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
    vec2 vel = texture( velData, pos*800).xy;
    //vec2 fieldVel = texture(field, pos.xy).xy;

    // Update the position.
    pos += vel*timestep;
    //pos += (fieldVel/255);

    // And finally store it on the position FBO.
    vFragColor = vec4(pos.x,pos.y,1.0,1.0);
}

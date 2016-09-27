#pragma once
attribute vec4 position;
attribute vec2 texCoord;

varying vec2 varyingTexCoord;

uniform vec2 modelPosition;

void main(){
	varyingTexCoord = texCoord;
	gl_Position = vec4(modelPosition.x,modelPosition.y,0.0,0.0) + position;
}

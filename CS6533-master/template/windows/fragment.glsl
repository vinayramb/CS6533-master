#pragma once
varying vec2 varyingTexCoord;
uniform sampler2D texture;

uniform float time;

uniform float anger;

void main(){
	vec2 texCoord = vec2(varyingTexCoord.x, varyingTexCoord.y + time);
	vec4 colTex = texture2D(texture, texCoord);
	 gl_FragColor = vec4(colTex.r + anger,colTex.g,colTex.b,colTex.a);
}
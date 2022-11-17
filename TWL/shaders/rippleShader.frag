#version 110

// attributes from vertShader.vert
varying vec4 vColor;
varying vec2 vTexCoord;

// uniforms
uniform sampler2D uTexture;
uniform float uTime;

void main() {
	float coef = sin(gl_FragCoord.y * 0.1 + 1.0 * uTime);
	vec2 texCoord = vTexCoord;
	texCoord.y +=  coef * 0.03;
	gl_FragColor = vColor * texture2D(uTexture, texCoord);
}

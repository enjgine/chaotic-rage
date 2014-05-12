#version 130

in vec2 fTexUV;
uniform sampler2D uTex;

void main()
{
	gl_FragColor = texture2D(uTex, fTexUV);
}

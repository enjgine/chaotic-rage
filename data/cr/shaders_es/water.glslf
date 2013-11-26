precision mediump float;

varying vec2 fTexUV;
uniform sampler2D uTex;

void main()
{
	gl_FragColor.rgb = texture2D(uTex, fTexUV).rgb;
	gl_FragColor.a = 0.7 + sin(fTexUV.s * 20.0) * 0.2;
}

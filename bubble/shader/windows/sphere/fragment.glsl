#version 450 core
in vec3 Normal;
in vec3 Position;

uniform vec3 cameraPos;
uniform samplerCube skybox;

uniform float mRefractionRatio=1.02;
uniform float mFresnelBias=0.1;
uniform float mFresnelScale=1.0;
uniform float mFresnelPower=2.0;

void main(){    
    vec3 vReflect;
    vec3 vRefract[3];
    vec3 I;
    vec4 reflectedColor;
    vec4 refractedColor;
    float vReflectionFactor;

    I = normalize(Position - cameraPos);

    vReflect=reflect(I,Normal);
    vRefract[0] = refract( normalize( I ), Normal, mRefractionRatio );
	vRefract[1] = refract( normalize( I ), Normal, mRefractionRatio * 0.99 );
	vRefract[2] = refract( normalize( I ), Normal, mRefractionRatio * 0.98 );
    vReflectionFactor = mFresnelBias + mFresnelScale * pow( 1.0 + dot( normalize( I ), Normal ), mFresnelPower );
    reflectedColor = textureCube( skybox, vReflect );
    refractedColor = vec4( 1.0 );

    refractedColor.r = textureCube( skybox, vRefract[0]).r;
	refractedColor.g = textureCube( skybox, vRefract[1]).g;
	refractedColor.b = textureCube( skybox, vRefract[2]).b;

    gl_FragColor = mix( refractedColor, reflectedColor, clamp( vReflectionFactor, 0.0, 1.0 ) );
}
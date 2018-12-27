#version 320 es
precision highp float;
out vec4 FragColor;

in vec3 Normal;
in vec3 Position;

uniform vec3 cameraPos;
uniform samplerCube skybox;



void main(){    
    vec3 vReflect;
    vec3 vRefract[3];
    vec3 I;
    vec4 reflectedColor;
    vec4 refractedColor;
    float vReflectionFactor;

    float mRefractionRatio=1.02;
    float mFresnelBias=0.1;
    float mFresnelScale=1.0;
    float mFresnelPower=2.0;

    I = normalize(Position - cameraPos);

    vReflect=reflect(I,Normal);
    vRefract[0] = refract( normalize( I ), Normal, mRefractionRatio );
	vRefract[1] = refract( normalize( I ), Normal, mRefractionRatio * 0.99 );
	vRefract[2] = refract( normalize( I ), Normal, mRefractionRatio * 0.98 );
    vReflectionFactor = mFresnelBias + mFresnelScale * pow( 1.0 + dot( normalize( I ), Normal ), mFresnelPower );
    reflectedColor = textureCube( skybox, vec3( -vReflect.x, vReflect.yz ) );
    refractedColor = vec4( 1.0 );

    refractedColor.r = textureCube( skybox, vec3( -vRefract[0].x, vRefract[0].yz ) ).r;
	refractedColor.g = textureCube( skybox, vec3( -vRefract[1].x, vRefract[1].yz ) ).g;
	refractedColor.b = textureCube( skybox, vec3( -vRefract[2].x, vRefract[2].yz ) ).b;

    FragColor = mix( refractedColor, reflectedColor, clamp( vReflectionFactor, 0.0, 1.0 ) );
}
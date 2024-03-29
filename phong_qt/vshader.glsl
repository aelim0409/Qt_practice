#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

//uniform mat4 mvp_matrix;
uniform mat4 uProjMat;
uniform mat4 uModelMat;
//uniform vec4 uSpc;
//uniform float uShiness;

attribute vec4 vPosition;
attribute vec4 vColor;
attribute vec4 vNormal;

varying vec4 color;
varying vec3 N3;
varying vec3 L3;
varying vec3 V3;
//attribute vec2 a_texcoord;

//varying vec2 v_texcoord;

//! [0]
void main()
{
    // Calculate vertex position in screen space
    gl_Position = uProjMat * (uModelMat * vPosition);
    gl_Position *= vec4(1, 1, -1, 1);
    float uShininess=100;
    vec4 uSpc= vec4(0.7,0.7,0.7,0);

    vec4 N = uModelMat * vNormal;
            N3 = normalize(vec3(N.xyz));

            vec4 P = uModelMat * vPosition;

            vec4 Lpos = vec4(2, 2, 0, 1);
            vec4 L = Lpos - P;
            L3 = normalize(vec3(L.xyz));

            vec4 V = vec4(0, 0, 0, 1);
            V3 = normalize(vec3((V - P).xyz));


                    color = vColor;
    // Pass texture coordinate to fragment shader
    // Value will be automatically interpolated to fragments inside polygon faces
   // v_texcoord = a_texcoord;
}
//! [0]

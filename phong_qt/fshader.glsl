#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif
attribute vec4 color;
attribute vec3 N3;
attribute vec3 L3;
attribute vec3 R3;
attribute vec3 V3;

//uniform float uShininess;
//uniform vec4 uSpc;

varying vec4 fColor;

//! [0]
void main()
{
    // Set fragment color from texture
   // gl_FragColor = texture2D(texture, v_texcoord);
    float uShininess=100;
    vec4 uSpc= vec4(0.7,0.7,0.7,0);
    vec4 Il = vec4(1, 1, 1, 1);
            vec4 IAmb = vec4(0.5, 0.5, 0.5, 1);
            vec4 ka = vec4(0.3, 0.3, 0.5, 1);
            vec4 kd = color;
            vec4 ks = uSpc;

            vec3 N = normalize(N3);
                    vec3 L = normalize(L3);
                    vec3 V = normalize(V3);

                    float dif = max(dot(N, L), 0);

                    vec3 R = 2 * dot(N, L) * N - L;
                    float spec = pow(max(dot(V, R), 0), uShininess);

                    fColor = ka * IAmb + kd * Il * dif + ks * Il * spec;

    // gl_FragColor = vec4(1,0,0,1);
}
//! [0]


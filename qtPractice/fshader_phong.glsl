#version 330

in  vec4 color;
in  vec3 N3;
in  vec3 L3;
in  vec3 R3;
in  vec3 V3;

out vec4 fColor;

uniform float uShininess;
uniform vec4 uSpc;
void main()
{
        vec4 Il = vec4(1, 1, 1, 1);
        vec4 I_Amb = vec4(0.5, 0.5, 0.5, 1);
        vec4 ka = vec4(0.3, 0.3, 0.5, 1);
        vec4 kd = color;
        vec4 ks = uSpc;

        vec3 N = normalize(N3);
        vec3 L = normalize(L3);
        vec3 V = normalize(V3);

        float dif = max(dot(N, L), 0);

        vec3 R = 2 * dot(N, L) * N - L;
        float spec = pow(max(dot(V, R), 0), uShininess);

        fColor = ka * I_Amb + kd * Il * dif + ks * Il * spec;


}

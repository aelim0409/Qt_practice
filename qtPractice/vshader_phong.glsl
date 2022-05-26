#version 330

in  vec4 vPosition;
in  vec4 vColor;
in  vec3 vNormal;

out vec4 color;
out vec3 N3;
out vec3 L3;
out vec3 V3;

uniform mat4 uProjMat;
uniform mat4 uModelMat;
uniform vec4 uSpc;
uniform float uShininess;

void main()
{
        gl_Position = uProjMat * (uModelMat * vPosition);
        gl_Position *= vec4(1, 1, -1, 1);

        vec4 N = uModelMat * vec4(vNormal, 0);
        N3 = normalize(vec3(N.xyz));

        vec4 P = uModelMat * vPosition;

        vec4 Lpos = vec4(2, 2, 0, 1);
        vec4 L = Lpos - P;
        L3 = normalize(vec3(L.xyz));
        /*
        vec4 diffColor = vec4(0.8, 0.2, 0.2, 1);
        vec4 ambColor = vec4(0.2, 0.2, 0.2, 1);
        vec4 specColor = vec4(1, 1, 1, 1)*0.3f;
        vec4 LightIntencity = vec4(1, 1, 1, 1);
        */
        vec4 V = vec4(0, 0, 0, 1);
        V3 = normalize(vec3((V - P).xyz));

        /*
        float shineness = 20;
        color = ambColor + diffColor * LightIntencity * max(0,dot(L3, N3)) +  specColor* LightIntencity * pow(max(0,dot(R3, V3)), shineness);
        color.a = 1.0f;
        */

        color = vColor;

}

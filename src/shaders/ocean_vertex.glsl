#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 vertexColor;
layout(location = 2) in vec2 vertexUV;

out vec4 fragmentColor;
out vec2 UV;
out vec3 lightDirection_tangentSpace;
out vec3 eyeDirection_tangentSpace;

uniform mat4 MVP;
uniform mat4 V;
uniform mat4 M;
uniform mat3 MV;
uniform vec3 lightPosition;

uniform float time;
uniform vec4 waves[20];

void main() {
    float height = 0, xp = 0, yp = 0, k, g, t;
    for (int i = 0; i < 20; ++i) {
        k = 4.024322 * waves[i].z * waves[i].z;
        g = k * (position.x * cos(waves[i].y) + position.y * sin(waves[i].y))
            - 6.28318 * waves[i].z * time + waves[i].w;
        height += waves[i].x * cos(g);
        t = waves[i].x * -sin(g) * k;
        xp += t * cos(waves[i].y);
        yp += t * sin(waves[i].y);
    }
    vec3 vertexPosition = vec3(position.x, position.y, height);
    vec3 tangent = normalize(vec3(1, 0, xp));
    vec3 bitangent = normalize(vec3(0, 1, yp));
    vec3 normal = cross(tangent, bitangent);

    gl_Position = MVP * vec4(vertexPosition, 1);
    fragmentColor = vertexColor;
    UV = vertexUV;

    vec3 vertexPosition_cameraSpace = (V * M * vec4(vertexPosition, 1)).xyz;
    vec3 lightPosition_cameraSpace = (V * vec4(lightPosition, 1)).xyz;

    vec3 eyeDirection_cameraSpace = vec3(0, 0, 0) - vertexPosition_cameraSpace;
    vec3 lightDirection_cameraSpace = lightPosition_cameraSpace + eyeDirection_cameraSpace;

    vec3 normal_cameraSpace = (MV * normal);
    vec3 tangent_cameraSpace = (MV * tangent);
    vec3 bitangent_cameraSpace = (MV * bitangent);
    mat3 TBN = transpose(mat3(tangent_cameraSpace, bitangent_cameraSpace, normal_cameraSpace));

    lightDirection_tangentSpace = TBN * lightDirection_cameraSpace;
    eyeDirection_tangentSpace = TBN * eyeDirection_cameraSpace;
}

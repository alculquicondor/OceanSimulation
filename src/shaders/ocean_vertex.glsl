#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 vertexColor;
layout(location = 2) in vec2 vertexUV;

out vec4 fragmentColor;
out vec2 UV;

uniform mat4 mvp;
uniform float time;
uniform vec4 waves[20];

void main() {
    float height = 0, k;
    for (int i = 0; i < 20; ++i) {
        k = 4.024322 * waves[i].z * waves[i].z;
        height += waves[i].x * cos(k * (position.x * cos(waves[i].y)
                                   + position.y * sin(waves[i].y))
                                   -2 * 3.1416 * waves[i].z * time + waves[i].w);
    }
    gl_Position = mvp * vec4(position.x, position.y, height, 1);
    fragmentColor = vertexColor;
    UV = vertexUV;
}

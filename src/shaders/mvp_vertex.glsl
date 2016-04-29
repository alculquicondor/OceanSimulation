#version 330

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec4 vertexColor;
layout(location = 2) in vec2 vertexUV;

out vec4 fragmentColor;
out vec2 UV;

uniform mat4 mvp;

void main() {
    gl_Position = mvp * vec4(vertexPosition_modelspace, 1);
    fragmentColor = vertexColor;
    UV = vertexUV;
}

#version 330

in vec2 UV;
in vec4 fragmentColor;
in vec3 lightDirection_tangentSpace;
in vec3 eyeDirection_tangentSpace;

out vec3 color;

uniform sampler2D textureSampler;
uniform sampler2D normalTextureSampler;
uniform vec3 lightColor;
uniform vec3 ambientLight;

uniform float time;

void main() {
    //vec3 materialColor = texture(textureSampler, UV).rgb;
    vec3 materialColor = vec3(.2, .5, .7);
    vec3 ambientColor = ambientLight * materialColor;

    //vec3 n = vec3(0, 0, 1);
    vec3 n = normalize(texture(normalTextureSampler, UV + vec2(0, time * .04f)).rgb * 2.0 - 1.0);
    vec3 l = normalize(lightDirection_tangentSpace);
    float cosTheta = clamp(dot(n, l), 0, 1);
    vec3 diffuseColor = lightColor * cosTheta * materialColor;

    vec3 E = normalize(eyeDirection_tangentSpace);
    vec3 R = reflect(-l, n);
    float cosAlpha = clamp(dot(E, R), 0, 1);
    vec3 specularColor = fragmentColor.rgb * lightColor * pow(cosAlpha, 10);

    color = ambientColor + diffuseColor + specularColor;
}

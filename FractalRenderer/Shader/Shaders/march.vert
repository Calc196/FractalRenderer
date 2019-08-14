#version 410

in vec2 pos;

out vec3 rayDirection;

uniform vec3 rayOrigin;
uniform mat4 invMvp;

void main() {
    gl_Position = vec4(pos, 0.0f, 1.0f);
    
    rayDirection = (invMvp * gl_Position).xyz - rayOrigin;
}

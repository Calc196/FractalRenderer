#version 410

in vec3 rayDirection;

out vec4 outColour;

uniform vec3 cameraPos;
uniform vec3 lightDirection;
uniform float power;

float darkness = 70.0f;
float blackAndWhite = 0.0f;
vec3 colourAMix = vec3 (1.0f, 0.0f, 1.0f);
vec3 colourBMix = vec3(1.0f, 1.0f, 0.0f);

const float epsilon = 0.001f;
const float maxDst = 200.0f;
const int maxStepCount = 250;

struct Ray {
    vec3 origin;
    vec3 direction;
};

Ray CreateCameraRay() {
    Ray ray;
    ray.direction = normalize(rayDirection);
    ray.origin = cameraPos;
    return ray;
}

// Mandelbulb distance estimation:
// http://blog.hvidtfeldts.net/index.php/2011/09/distance-estimated-3d-fractals-v-the-mandelbulb-different-de-approximations/
vec2 Mandlebulb(vec3 pos) {
    vec3 z = pos;
    float dr = 1.0;
    float r = 0.0;
    int i = 0;
    for (i = 0; i < 7 ; i++) {
        r = length(z);
        if (r>2) break;
        
        // convert to polar coordinates
        float theta = acos(z.z/r);
        float phi = atan(z.y,z.x);
        dr =  pow( r, power-1.0)*power*dr + 1.0;
        
        // scale and rotate the point
        float zr = pow( r,power);
        theta = theta*power;
        phi = phi*power;
        
        // convert back to cartesian coordinates
        z = zr*vec3(sin(theta)*cos(phi), sin(phi)*sin(theta), cos(theta));
        z+=pos;
    }
    return vec2(i, 0.5*log(r)*r/dr);
}

vec2 Sphere(vec3 pos) {
    return vec2(1.0f, distance(pos, vec3(0.0f)) - 2.0f);
}

vec3 EstimateNormal(vec3 p) {
    float x = Mandlebulb(vec3(p.x + epsilon, p.y, p.z)).y - Mandlebulb(vec3(p.x - epsilon, p.y, p.z)).y;
    float y = Mandlebulb(vec3(p.x, p.y + epsilon, p.z)).y - Mandlebulb(vec3(p.x, p.y - epsilon, p.z)).y;
    float z = Mandlebulb(vec3(p.x, p.y, p.z + epsilon)).y - Mandlebulb(vec3(p.x, p.y, p.z - epsilon)).y;
    return normalize(vec3(x,y,z));
}

void main() {

    // Background gradient
    vec4 result = vec4(mix(colourAMix, colourBMix, 0.5) * 0.1, 1.0); //mix(vec4(51, 3, 20, 1), vec4(16, 6, 28, 1), gl_FragCoord.y) / 255.0f;

    // Raymarching:
    Ray ray = CreateCameraRay();
    float rayDst = 0;
    int marchSteps = 0;
    float dst = 0;

    while (rayDst < maxDst && marchSteps < maxStepCount) {
        marchSteps++;
        vec2 sceneInfo = Mandlebulb(ray.origin);
        dst = sceneInfo.y;

        // Ray has hit a surface
        if (dst <= epsilon) {
            float escapeIterations = sceneInfo.x;
            vec3 normal = EstimateNormal(ray.origin - ray.direction * epsilon * 2);

            float colourA = clamp(dot(normal * 0.5f + 0.5f, -lightDirection), 0.0f, 1.0f);
            float colourB = clamp(escapeIterations / 16.0, 0.0f, 1.0f);
            vec3 colourMix = clamp(colourA * colourAMix + colourB * colourBMix, 0.0f, 1.0f);

            result = vec4(colourMix.xyz, 1);
            break;
        }
        ray.origin += ray.direction * dst;
        rayDst += dst;
    }

    float rim = marchSteps / darkness;
    //rim = (dst <= epsilon) ? rim : 1.0f - rim;
    outColour = result * rim;
}

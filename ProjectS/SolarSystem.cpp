#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace std;

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cmath>

// ---------------- Window ----------------
int WIDTH = 1024, HEIGHT = 768;

// ---------------- Camera ----------------
float camDistance = 700.0f;
float camYaw = 20.0f, camPitch = 28.0f;
float camTargetX = 0.0f, camTargetY = 0.0f, camTargetZ = 0.0f;
bool rightMousePressed = false;


// Random helper
static float frand01() { return (float)rand() / (float)RAND_MAX; }
static float frand(float a, float b) { return a + (b - a) * frand01(); }
// ---------------- Structures ----------------
struct Planet {
    string name;
    float radius;
    float distance;

};

void drawSphere(float radius, int slices = 20, int stacks = 20) {
    for (int i = 0; i < stacks; i++) {
        float lat0 = (float)M_PI * (-0.5f + (float)i / stacks);
        float lat1 = (float)M_PI * (-0.5f + (float)(i + 1) / stacks);

        float z0 = sinf(lat0) * radius;
        float zr0 = cosf(lat0) * radius;
        float z1 = sinf(lat1) * radius;
        float zr1 = cosf(lat1) * radius;

        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= slices; j++) {
            float lng = 2.0f * (float)M_PI * j / slices;
            float x = cosf(lng);
            float y = sinf(lng);

            glVertex3f(x * zr0, y * zr0, z0);
            glVertex3f(x * zr1, y * zr1, z1);
        }
        glEnd();
    }
}

int main() {
   
    return 0;
}

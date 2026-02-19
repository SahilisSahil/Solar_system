#include <GLFW/glfw3.h>
#include <GL/gl.h>   
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cmath>

#define M_PI 3.14159265359f

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

// ---------------- Callbacks ----------------
void scroll_callback(GLFWwindow*, double, double yoffset) {
    camDistance -= (float)yoffset * 25.0f;
    camDistance = std::max(160.0f, std::min(camDistance, 3400.0f));
}

void mouse_button_callback(GLFWwindow*, int button, int action, int) {
    if (button == GLFW_MOUSE_BUTTON_LEFT)  leftMousePressed = (action == GLFW_PRESS);
    if (button == GLFW_MOUSE_BUTTON_RIGHT) rightMousePressed = (action == GLFW_PRESS);
}

void cursor_position_callback(GLFWwindow*, double xpos, double ypos) {
    if (leftMousePressed) {
        camYaw += (float)(xpos - lastX) * 0.35f;
        camPitch -= (float)(ypos - lastY) * 0.35f;
        camPitch = std::max(-85.0f, std::min(camPitch, 85.0f));
    }
    if (rightMousePressed) {
        camTargetX -= (float)(xpos - lastX) * 0.12f;
        camTargetY += (float)(ypos - lastY) * 0.12f;
    }
    lastX = xpos;
    lastY = ypos;
}

void key_callback(GLFWwindow*, int key, int, int action, int) {
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        if (key == GLFW_KEY_UP)   timeSpeed += 0.1f;
        if (key == GLFW_KEY_DOWN) timeSpeed = std::max(0.0f, timeSpeed - 0.1f);
        if (key == GLFW_KEY_R)    timeDirection *= -1;
    }
}

// ---------------- Init Stars ----------------
void initStars() {
    stars.clear();
    for (int i = 0; i < 1600; i++) {
        Star s;
        float radius = frand(900.0f, 3400.0f);
        float theta = frand(0.0f, 2.0f * M_PI);
        float phi = frand(0.15f * M_PI, 0.95f * M_PI);

        s.x = radius * cos(theta) * sin(phi);
        s.y = radius * cos(phi);
        s.z = radius * sin(theta) * sin(phi);

        float c = frand(0.75f, 1.0f);
        s.color = glm::vec3(c, c, c);
        stars.push_back(s);
    }
}

// ---------------- Init Moons ----------------
void initMoons() {
    moons.clear();

    auto addMoon = [&](int planetIndex, float radiusMul, float distMul, float speedMul, glm::vec3 color) {
        Moon m;
        m.planetIndex = planetIndex;
        m.radius = planets[planetIndex].radius * radiusMul;
        m.distance = planets[planetIndex].radius * distMul;
        m.orbitSpeed = planets[planetIndex].orbitSpeed * speedMul;
        m.angle = frand(0.0f, 2.0f * M_PI);
        m.color = color;
        moons.push_back(m);
        };

    addMoon(2, 0.28f, 2.2f, 6.2f, glm::vec3(0.85f));
    addMoon(3, 0.18f, 1.8f, 8.0f, glm::vec3(0.80f));
    addMoon(3, 0.14f, 2.5f, 5.8f, glm::vec3(0.75f));

    addMoon(4, 0.20f, 1.9f, 5.0f, glm::vec3(0.90f));
    addMoon(4, 0.16f, 2.5f, 4.2f, glm::vec3(0.88f, 0.88f, 0.92f));
    addMoon(4, 0.14f, 3.2f, 3.6f, glm::vec3(0.90f, 0.86f, 0.82f));
    addMoon(4, 0.12f, 4.0f, 3.0f, glm::vec3(0.86f));

    addMoon(5, 0.16f, 2.4f, 4.2f, glm::vec3(0.90f, 0.90f, 0.85f));
    addMoon(5, 0.14f, 3.3f, 3.3f, glm::vec3(0.85f, 0.85f, 0.92f));
    addMoon(5, 0.12f, 4.6f, 2.6f, glm::vec3(0.90f, 0.85f, 0.80f));

    addMoon(6, 0.16f, 2.2f, 4.6f, glm::vec3(0.85f, 0.90f, 1.00f));
    addMoon(6, 0.13f, 3.1f, 3.4f, glm::vec3(0.86f));

    addMoon(7, 0.15f, 2.6f, 4.2f, glm::vec3(0.86f, 0.86f, 0.95f));
    addMoon(8, 0.22f, 2.2f, 5.2f, glm::vec3(0.82f));
}

// ---------------- Init Sun Meteors ----------------
void initSunMeteors() {
    sunMeteorsInner.clear();
    sunMeteorsOuter.clear();

    float marsDist = planets[3].distance;

    for (int i = 0; i < 260; i++) {
        SolarMeteor m;
        m.dist = frand(30.0f, marsDist);
        m.angle = frand(0.0f, 2.0f * M_PI);

        float t = (m.dist - 30.0f) / (marsDist - 30.0f + 0.001f);
        m.speed = frand(0.0025f, 0.0060f) * (1.15f - 0.55f * t);

        m.y = frand(-5.0f, 5.0f);
        float w = frand(0.85f, 1.0f);
        m.color = glm::vec3(w, w, w);
        sunMeteorsInner.push_back(m);
    }

    for (int i = 0; i < 450; i++) {
        SolarMeteor m;
        m.dist = frand(260.0f, 1700.0f);
        m.angle = frand(0.0f, 2.0f * M_PI);
        m.speed = frand(0.0006f, 0.0014f);
        m.y = frand(-12.0f, 12.0f);
        float w = frand(0.75f, 0.95f);
        m.color = glm::vec3(w, w, w);
        sunMeteorsOuter.push_back(m);
    }
}

// ---------------- Drawing ----------------
void drawSphere(float r, int slices, int stacks) {
    for (int i = 0; i <= stacks; i++) {
        float lat0 = M_PI * (-0.5f + (float)(i - 1) / stacks);
        float lat1 = M_PI * (-0.5f + (float)i / stacks);

        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= slices; j++) {
            float lng = 2.0f * M_PI * (float)(j - 1) / slices;

            float x0 = cos(lng) * cos(lat0);
            float y0 = sin(lat0);
            float z0 = sin(lng) * cos(lat0);

            float x1 = cos(lng) * cos(lat1);
            float y1 = sin(lat1);
            float z1 = sin(lng) * cos(lat1);

            glNormal3f(x0, y0, z0);
            glVertex3f(r * x0, r * y0, r * z0);

            glNormal3f(x1, y1, z1);
            glVertex3f(r * x1, r * y1, r * z1);
        }
        glEnd();
    }
}

void drawRing(float innerR, float outerR, int segments = 200) {
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= segments; i++) {
        float t = (float)i * 2.0f * M_PI / (float)segments;
        float x = cos(t), z = sin(t);
        glNormal3f(0, 1, 0);
        glVertex3f(innerR * x, 0.0f, innerR * z);
        glVertex3f(outerR * x, 0.0f, outerR * z);
    }
    glEnd();
}

void drawGrid() {
    glDisable(GL_LIGHTING);
    glColor3f(0.07f, 0.06f, 0.09f);
    glBegin(GL_LINES);
    float y = -110.0f;
    for (int i = -2500; i <= 2500; i += 60) {
        glVertex3f((float)i, y, -2500.0f); glVertex3f((float)i, y, 2500.0f);
        glVertex3f(-2500.0f, y, (float)i); glVertex3f(2500.0f, y, (float)i);
    }
    glEnd();
    glEnable(GL_LIGHTING);
}

void drawOrbits() {
    glDisable(GL_LIGHTING);
    glColor3f(0.45f, 0.45f, 0.45f);
    for (auto& p : planets) {
        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < 240; i++) {
            float t = (float)i * 2.0f * M_PI / 240.0f;
            glVertex3f(p.distance * cos(t), 0.0f, p.distance * sin(t));
        }
        glEnd();
    }
    glEnable(GL_LIGHTING);
}

void drawStars() {
    glDisable(GL_LIGHTING);
    glPointSize(2.0f);
    glBegin(GL_POINTS);
    for (auto& s : stars) {
        glColor3f(s.color.r, s.color.g, s.color.b);
        glVertex3f(s.x, s.y, s.z);
    }
    glEnd();
    glEnable(GL_LIGHTING);
}

void drawSunMeteors(const vector<SolarMeteor>& ms) {
    glDisable(GL_LIGHTING);
    glPointSize(2.0f);
    glBegin(GL_POINTS);
    for (auto& m : ms) {
        float x = m.dist * cos(m.angle);
        float z = m.dist * sin(m.angle);
        glColor3f(m.color.r, m.color.g, m.color.b);
        glVertex3f(x, m.y, z);
    }
    glEnd();
    glEnable(GL_LIGHTING);
}

// ---------------- Main ----------------
int main() {
    srand((unsigned)time(nullptr));
    initStars();
    initSunMeteors();
    initMoons();

    if (!glfwInit()) { cerr << "GLFW init failed\n"; return -1; }
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "3D Solar System (All This And We Still Mate) ", nullptr, nullptr);
    if (!window) { cerr << "Window creation failed\n"; glfwTerminate(); return -1; }

    glfwMakeContextCurrent(window);

    glfwSetScrollCallback(window, scroll_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetKeyCallback(window, key_callback);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glShadeModel(GL_SMOOTH);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.01f, 0.01f, 0.02f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 proj = glm::perspective(glm::radians(45.0f),
            (float)WIDTH / (float)HEIGHT, 0.1f, 9000.0f);

        glm::vec3 camPos(
            camTargetX + camDistance * cos(glm::radians(camPitch)) * sin(glm::radians(camYaw)),
            camTargetY + camDistance * sin(glm::radians(camPitch)),
            camTargetZ + camDistance * cos(glm::radians(camPitch)) * cos(glm::radians(camYaw))
        );

        glm::mat4 view = glm::lookAt(camPos,
            glm::vec3(camTargetX, camTargetY, camTargetZ),
            glm::vec3(0, 1, 0));

        glMatrixMode(GL_PROJECTION);
        glLoadMatrixf(glm::value_ptr(proj));
        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf(glm::value_ptr(view));

        drawStars();
        drawGrid();
        drawOrbits();

        GLfloat sunPos[] = { 0.0f, 0.0f, 0.0f, 1.0f };
        GLfloat sunDiffuse[] = { 1.0f, 0.98f, 0.88f, 1.0f };
        GLfloat sunAmbient[] = { 0.10f, 0.10f, 0.12f, 1.0f };
        GLfloat sunSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        glLightfv(GL_LIGHT0, GL_POSITION, sunPos);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, sunDiffuse);
        glLightfv(GL_LIGHT0, GL_AMBIENT, sunAmbient);
        glLightfv(GL_LIGHT0, GL_SPECULAR, sunSpecular);

        GLfloat matSpec[] = { 0.45f, 0.45f, 0.45f, 1.0f };
        glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
        glMaterialf(GL_FRONT, GL_SHININESS, 28.0f);

        for (auto& m : sunMeteorsInner) m.angle += m.speed * timeSpeed * (float)timeDirection;
        for (auto& m : sunMeteorsOuter) m.angle += m.speed * timeSpeed * (float)timeDirection;
        drawSunMeteors(sunMeteorsInner);
        drawSunMeteors(sunMeteorsOuter);

        glPushMatrix();
        glDisable(GL_LIGHTING);
        glColor3f(1.0f, 1.0f, 0.88f);
        drawSphere(14.0f * SUN_SCALE, 50, 50);
        glColor4f(1.0f, 1.0f, 0.80f, 0.25f);
        drawSphere(18.0f * SUN_SCALE, 50, 50);
        glEnable(GL_LIGHTING);
        glPopMatrix();

        vector<glm::vec3> planetPos(planets.size(), glm::vec3(0));
        for (size_t i = 0; i < planets.size(); i++) {
            Planet& p = planets[i];
            p.angle += p.orbitSpeed * timeSpeed * (float)timeDirection;
            planetPos[i] = glm::vec3(p.distance * cos(p.angle), 0.0f, p.distance * sin(p.angle));
        }

        for (size_t i = 0; i < planets.size(); i++) {
            Planet& p = planets[i];
            float px = planetPos[i].x;
            float pz = planetPos[i].z;

            glPushMatrix();
            glTranslatef(px, 0.0f, pz);

            glColor3f(p.color.r, p.color.g, p.color.b);
            drawSphere(p.radius, 36, 36);

            if (p.hasRing) {
                glDisable(GL_LIGHTING);
                glColor3f(0.75f, 0.72f, 0.55f);
                drawRing(p.radius * 1.5f, p.radius * 3.1f, 220);
                glEnable(GL_LIGHTING);
            }

            glPopMatrix();
        }

        for (auto& m : moons) {
            m.angle += m.orbitSpeed * timeSpeed * (float)timeDirection;
            glm::vec3 center = planetPos[m.planetIndex];

            float mx = center.x + m.distance * cos(m.angle);
            float mz = center.z + m.distance * sin(m.angle);

            glPushMatrix();
            glTranslatef(mx, 0.0f, mz);
            glColor3f(m.color.r, m.color.g, m.color.b);
            drawSphere(m.radius, 18, 18);
            glPopMatrix();
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

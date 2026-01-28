#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace std;

// ---------------- Window ----------------
int WIDTH = 1024, HEIGHT = 768;
float camDistance = 700.0f;
float camYaw = 20.0f, camPitch = 28.0f;
float camTargetX = 0.0f, camTargetY = 0.0f, camTargetZ = 0.0f;

struct Planet {
    string name;
    float radius;
    float distance;
    float orbitSpeed;
    float angle;
    }

int main() {
   
    return 0;
}

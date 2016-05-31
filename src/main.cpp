#include <iostream>

#include <glm/gtx/transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "scene.h"
#include "perspective_camera.h"
#include "gizmo.h"
#include "ocean.h"
#include "ocean_program.h"


using namespace std;


PerspectiveCamera *camera;
float cam_dist = 30;
OceanProgram *program = nullptr;

class Center : public Drawable {
public:
    Center() : Drawable(nullptr, nullptr, 0), position(0, 0, 0), angle_z(0) {}

    glm::vec3 position;
    float angle_z;
    virtual glm::mat4 get_model(float time) {
        return Drawable::get_model(time) *
                glm::rotate(-angle_z, glm::vec3(0, 0, 1)) * glm::translate(position);
    }

    void move_horizontal(float d) {
        position += glm::rotateZ(glm::vec3(d, 0, 0), angle_z);
    }

    void move_vertical(float d) {
        position += glm::rotateZ(glm::vec3(0, d, 0), angle_z);
    }
};


Center *center;


void scroll(GLFWwindow* window, double x_offset, double y_offset) {
    center->angle_z -= x_offset * .02;
    cam_dist -= y_offset * .4;
    camera->look_at(glm::vec3(0, -cam_dist, cam_dist), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1));
}


class OceanScene : public Scene {
private:
    Drawable *gizmo, *ocean;
public:
    OceanScene(Camera *camera) : Scene("Ocean", 1000, 700, camera),
                                 gizmo(nullptr), ocean(nullptr) { }

    void init() {
        gizmo = new Gizmo(new MvpProgram, center);
        ocean = new Ocean(200, 200, 1.5, ::program, center);
        add(gizmo);
        add(ocean);
        set_wheel_callback(scroll);
    }

    virtual ~OceanScene() {
        if (gizmo != nullptr)
            delete gizmo;
        if (ocean != nullptr)
            delete ocean;
    }

    virtual void process_events() {
        if (key_state(GLFW_KEY_LEFT))
            center->move_horizontal(.5f);
        if (key_state(GLFW_KEY_RIGHT))
            center->move_horizontal(-.5f);
        if (key_state(GLFW_KEY_UP))
            center->move_vertical(-.5f);
        if (key_state(GLFW_KEY_DOWN))
            center->move_vertical(.5f);
    }

    virtual void before_iteration(float time) {
        ::program->set_uniform("lightPosition",
                               glm::vec3(center->get_model(time) * glm::vec4(0, 0, 300, 1)));
        ::program->set_uniform("lightColor", {.85, .85, .85});
        ::program->set_uniform("ambientLight", {.25, .25, .25});

        ::program->set_uniform("time", time);
        ::program->set_waves();
    }
};


OceanScene *scene = nullptr;


int main() {
    camera = new PerspectiveCamera(1000, 700, 1.5, 1, 500);
    scene = new OceanScene(camera);
    center = new Center();
    program = new OceanProgram;
    camera->look_at(glm::vec3(0, -cam_dist, cam_dist), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1));
    scene->init();

    scene->run();

    delete center;
    delete scene;
    delete camera;
    delete program;
    return 0;
}
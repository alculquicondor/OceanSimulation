#ifndef HELLO_OPENGL_ORTHO_CAMERA_H
#define HELLO_OPENGL_ORTHO_CAMERA_H

#include <glm/gtc/matrix_transform.hpp>

#include "camera.h"


class OrthoCamera : public Camera {
private:
    glm::mat4 vp;

public:
    OrthoCamera(int width, int height, float zoom=1, float depth=1);
    glm::mat4 get_vp() const override;
    glm::mat4 get_v() const override;
};

#endif //HELLO_OPENGL_ORTHO_CAMERA_H

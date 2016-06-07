#ifndef HELLO_OPENGL_TEXTURE_H
#define HELLO_OPENGL_TEXTURE_H

#include <string>

#include <GLFW/glfw3.h>
#include <FreeImage.h>


class Texture {
public:
    Texture(const std::string &filename,
            GLenum image_format = GL_RGB,
            GLint internal_format = GL_RGB,
            GLint level = 0,
            GLint border = 0);

    void load(GLenum texture_unit=GL_TEXTURE0, int uniform=0) const;

private:
    GLuint texture_id;
};

#endif //HELLO_OPENGL_TEXTURE_H

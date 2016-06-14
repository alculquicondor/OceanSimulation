#ifndef HELLO_OPENGL_DRAWABLE_H
#define HELLO_OPENGL_DRAWABLE_H

#include "buffer.h"
#include "camera.h"
#include "mvp_program.h"
#include "texture.h"


class Drawable {
public:
    Drawable(MvpProgram *program, Buffer *geometry, GLenum draw_mode = GL_TRIANGLE_STRIP, Buffer *color = nullptr,
             Texture *texture = nullptr, Buffer *uv = nullptr, Drawable *parent = nullptr);

    void set_parent(Drawable *parent);
    void set_normal_texture(Texture *texture);

    virtual ~Drawable();
    virtual void draw(Camera *camera, float time=0);
    virtual void draw_geometry();
    virtual glm::mat4 get_model(float time);

protected:
    GLenum draw_mode;
    Buffer *geometry;

private:
    MvpProgram *program;
    Buffer *color;
    Drawable *parent;
    Texture *diffuse_texture, *normal_texture;
    Buffer *uv;
};


#endif //HELLO_OPENGL_DRAWABLE_H

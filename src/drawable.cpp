#include "drawable.h"


Drawable::Drawable(MvpProgram *program, Buffer *geometry, GLenum draw_mode, Buffer *color,
                   Texture *texture, Buffer *uv, Drawable *parent) :
        program(program), geometry(geometry), color(color), draw_mode(draw_mode), parent(parent),
        texture(texture), uv(uv) { }


Drawable::~Drawable() {
}


void Drawable::set_parent(Drawable *parent) {
    this->parent = parent;
}


void Drawable::draw(Camera *camera, float time) {
    if (geometry == nullptr)
        return;
    program->activate();
    geometry->activate();
    if (color != nullptr)
        color->activate();
    if (texture != nullptr)
        texture->load();
    if (uv != nullptr)
        uv->activate();

    glm::mat4 mvp = camera != nullptr ?
                    camera->get_vp() * get_model(time) :
                    get_model(time);
    program->set_mvp(mvp);
    draw_geometry();

    geometry->deactivate();
    if (color != nullptr)
        color->deactivate();
    if (uv != nullptr)
        uv->deactivate();
}


void Drawable::draw_geometry() {
    glDrawArrays(draw_mode, 0, geometry->size());
}


glm::mat4 Drawable::get_model(float time) {
    return parent != nullptr ? parent->get_model(time) : glm::mat4(1.0f);
}
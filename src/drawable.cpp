#include "drawable.h"


Drawable::Drawable(MvpProgram *program, Buffer *geometry, GLenum draw_mode, Buffer *color,
                   Texture *texture, Buffer *uv, Drawable *parent) :
        program(program), geometry(geometry), color(color), draw_mode(draw_mode), parent(parent),
        diffuse_texture(texture), uv(uv), normal_texture(nullptr) { }


Drawable::~Drawable() {
}


void Drawable::set_parent(Drawable *parent) {
    this->parent = parent;
}


void Drawable::set_normal_texture(Texture *texture) {
    this->normal_texture = texture;
}


void Drawable::draw(Camera *camera, float time) {
    if (geometry == nullptr)
        return;
    program->activate();
    geometry->activate();
    if (color != nullptr)
        color->activate();
    if (diffuse_texture != nullptr)
        diffuse_texture->load(GL_TEXTURE0, program->set_uniform("textureSampler"));
    if (normal_texture != nullptr)
        normal_texture->load(GL_TEXTURE1, program->set_uniform("normalTextureSampler"));
    if (uv != nullptr)
        uv->activate();

    glm::mat4 mvp, m = get_model(time), v;
    if (camera != nullptr) {
        mvp = camera->get_vp() * m;
        v = camera->get_v();
    } else {
        mvp = m;
        v = glm::mat4(1);
    }
    program->set_v(v);
    program->set_mvp(mvp);
    program->set_m(m);
    program->set_mv(glm::mat3(v * m));

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

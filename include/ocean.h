#ifndef HELLO_OPENGL_OCEAN_H
#define HELLO_OPENGL_OCEAN_H

#include "drawable.h"
#include "uniform_color.h"


class Ocean : public Buffer, public Drawable {
private:
    int nx, ny;
    std::vector<glm::vec3> mesh;
    virtual const void *data() const;
    virtual GLsizeiptr data_size() const;
    virtual void draw_geometry();
public:
    Ocean(int nx, int ny, float dist, MvpProgram *program, Drawable *parent);
    virtual GLsizei size() const;
};


class OceanUV : public Buffer {
private:
    std::vector<glm::vec2> uv;
    virtual const void *data() const;
    virtual GLsizeiptr data_size() const;
    virtual GLint dimension() const;
public:
    OceanUV(int nx, int ny, float dist);
    virtual GLsizei size() const;
};

#endif //HELLO_OPENGL_OCEAN_H

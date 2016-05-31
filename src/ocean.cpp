#include "ocean.h"


Ocean::Ocean(int nx, int ny, float dist, MvpProgram *program, Drawable *parent) :
        Buffer(), nx(nx), ny(ny), mesh(std::size_t(4 * ny * (2 * nx + 1))),
        Drawable(program, this, GL_TRIANGLE_STRIP,
                 new UniformColor(glm::vec4(.3f, .4f, .5f, 1.f), 4 * ny * (2 * nx + 1)),
                new Texture("ocean.tga", GL_BGR), new OceanUV(nx, ny, dist), parent) {
    std::size_t p = 0;
    for (int i = -ny; i < ny; ++i) {
        mesh[p++] = {-dist * nx, dist * i, 0};
        for (int j = -nx; j < nx; ++j) {
            mesh[p++] = {dist * j, dist * (i + 1), 0};
            mesh[p++] = {dist * (j + 1), dist * i, 0};
        }
        mesh[p++] = {dist * nx, dist * (i + 1), 0};
    }
}


const void *Ocean::data() const {
    return &mesh[0];
}


GLsizeiptr Ocean::data_size() const {
    return sizeof(mesh[0]) * mesh.size();
}


GLsizei Ocean::size() const {
    return (GLsizei) mesh.size();
}


void Ocean::draw_geometry() {
    for (int i = 0; i < 2 * ny; ++i)
        glDrawArrays(draw_mode, (4 * nx + 2) * i, 4 * nx + 2);
}


OceanUV::OceanUV(int nx, int ny, float dist) : Buffer(2), uv(std::size_t(4 * ny * (2 * nx + 1))) {
    std::size_t p = 0;
    dist /= 20;
    for (int i = 0; i < 2 * ny; ++i) {
        uv[p++] = {0, dist * i};
        for (int j = 0; j < 2 * ny; ++j) {
            uv[p++] = {dist * j, dist * (i + 1)};
            uv[p++] = {dist * (j + 1), dist * i};
        }
        uv[p++] = {dist * nx, dist * (i + 1)};
    }
}


const void *OceanUV::data() const {
    return &uv[0];
}


GLsizeiptr OceanUV::data_size() const {
    return sizeof(uv[0]) * uv.size();
}


GLsizei OceanUV::size() const {
    return (GLsizei) uv.size();
}


GLsizei OceanUV::dimension() const {
    return 2;
}

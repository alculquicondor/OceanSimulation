#include "mvp_program.h"


MvpProgram::MvpProgram(const char *vertex_shader, const char *fragment_shader) :
    Program(vertex_shader, fragment_shader) { }


void MvpProgram::set_mvp(glm::mat4 mvp) {
    set_uniform("mvp", mvp);
}

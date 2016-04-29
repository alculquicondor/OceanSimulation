#ifndef HELLO_OPENGL_OCEAN_PROGRAM_H
#define HELLO_OPENGL_OCEAN_PROGRAM_H

#include "mvp_program.h"


class OceanProgram : public MvpProgram {
public:
    OceanProgram();
    void set_time(float time);
    void set_waves();
private:
    static const std::vector<glm::vec4> waves;
};


#endif //HELLO_OPENGL_OCEAN_PROGRAM_H
